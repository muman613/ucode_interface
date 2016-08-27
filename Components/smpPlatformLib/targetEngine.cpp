#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>      // std::ostringstream
#include <iostream>
#include <iomanip>
#include <mutex>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "platformDB2/libplatformdb.h"
#include "fileresolver/fileresolver.h"
#include "symbolmgr/symbolmgr.h"
#include "ucode_utils.h"
#include "video_utils.h"
#include "targetEngine.h"
#include "file_utils.h"

#ifdef _DEBUG
    #define LOCALDBG ENABLE
#else
    #define LOCALDBG DISABLE
#endif // _DEBUG

#define PLATFORM_DATABASE_FILE      "tango_platform_config.xml"
#define PDB_FILE_PATH               "../../../xml/"

#define CONTROL_IF      dynamic_cast<controlInterface*>(this)

using namespace std;

std::ostream& operator<<(std::ostream& os, const engineFlags& flags) {
//    flags.flag_mutex.lock();

    os << hex << showbase << setw(4) << flags.value <<
          " ( valid=" << dec << flags.bits.bValid <<
          " conn=" << flags.bits.bConnected <<
          " loaded=" << flags.bits.bUcodeLoaded <<
          " state=";
    switch (flags.bits.eState) {
    case DSP_RUN:
        os << "DSP_RUN";
        break;
    case DSP_STOP:
        os << "DSP_STOP";
        break;
    case DSP_RESET:
        os << "DSP_RESET";
        break;
    }
    os << " )";

//    flags.flag_mutex.unlock();

    return os;
}


std::ostream& operator<<(std::ostream& os, const targetEngine& engine)
{
    auto flags = os.flags();

    std::lock_guard<std::mutex> lock(engine.m_flags.flag_mutex);

    os << std::string(80, '-') << "\n";
    os << "Engine : " << engine.m_sBlockID <<
          " block "   << engine.m_nEngineIndex <<
          " on "      << engine.m_sChipID <<
          " @ "       << (!engine.m_sTarget.empty()?engine.m_sTarget:"Not Connected") << "\n";
    os << std::hex <<
          std::uppercase <<
          std::internal <<
          std::setfill('0');
    os << "PM     : 0x" << std::setw(8) << engine.m_engine.get_pmBase() << "\n" <<
          "DM     : 0x" << std::setw(8) << engine.m_engine.get_dmBase() << "\n" <<
          "DRAM   : 0x" << std::setw(8) << engine.m_engine.get_dramBase() << "\n";
    os << "UCODE  : " <<  ((engine.m_flags.bits.bUcodeLoaded == true)?engine.m_sUcode:"Not Loaded") << "\n";
    os << "FLAGS  : " << engine.m_flags << "\n";

    os << std::string(80, '-') << std::endl;

    os.flags(flags);

    return os;
}

/**
 *  Constructor
 */

targetEngine::targetEngine(string sChipID, string sBlockID, uint32_t nEngineIndex, ucodeType type)
:   m_dramBase(DRAM_BASE),
    m_uiDRAMPtr(DRAM_BASE)
{
    // ctor
    m_flags.flag_mutex.lock();
    m_flags.bits.eState = DSP_STOP;
    m_flags.flag_mutex.unlock();

    open(sChipID, sBlockID, nEngineIndex, type);
}

/**
 *  Destructor
 */

targetEngine::~targetEngine()
{
    // dtor
}

/**
 *
 */

bool targetEngine::is_valid() const
{
    std::lock_guard<std::mutex> lock(m_flags.flag_mutex);

    bool bRes = m_flags.bits.bValid;

    return bRes;
}

/**
 *
 */

bool targetEngine::is_connected() const
{
    std::lock_guard<std::mutex> lock(m_flags.flag_mutex);

    bool bRes = m_flags.bits.bConnected;

    return bRes;
}

/**
 *
 */

bool targetEngine::is_ucode_loaded() const
{
    std::lock_guard<std::mutex> lock(m_flags.flag_mutex);

    bool bRes = m_flags.bits.bUcodeLoaded;

    return bRes;
}

/**
 *
 */

bool targetEngine::open(string sChipID, string sBlockID,
                        uint32_t nEngineIndex, ucodeType eType)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    PlatformDatabase            platDB;
    bool                        bRes = false;

    RMDBGLOG((LOCALDBG, "%s(%s, %s, %d, %s)\n", __PRETTY_FUNCTION__,
              sChipID.c_str(), sBlockID.c_str(), nEngineIndex,
              (eType == UCODE_DEBUG)?"Debug":"Release"));

    m_sChipID       = sChipID;
    m_sBlockID      = sBlockID;
    m_eType         = eType;
    m_nEngineIndex  = nEngineIndex;

    if (resolve_files()) {
        if (platDB.LoadDatabase(PLATFORM_DATABASE_FILE, PDB_FILE_PATH)) {
            PlatformChip chip;

#ifdef _DEBUG
            fprintf(stderr, "Database loaded!\n");
#endif // _DEBUG

            if (platDB.FindChip(chip, m_sChipID)) {
                PlatformBlock       block;
                size_t              engineCount;

                block       = (*chip[m_sBlockID]);
                engineCount = block.get_engine_count();

                if ((engineCount > 0) && (engineCount > m_nEngineIndex)) {
                    m_resetOff = block.get_resetReg();
                    m_engine   = (*block[m_nEngineIndex]);

                    if (m_dramBase != m_engine.get_dramBase()) {
                        RMDBGLOG((LOCALDBG, "-- setting dram base address to 0x%08X\n",
                                  (m_engine.get_dramBase() + DRAM_OFFSET)));
                        m_dramBase = m_uiDRAMPtr = (m_engine.get_dramBase() + DRAM_OFFSET);
                        m_engine.set_dramBase( m_dramBase );
                    }

#ifdef _DEBUG
                    m_engine.Dump(stderr);
#endif // _DEBUG

                    if (m_symMgr.LoadSymbols( m_filePack.sLabelFile )) {
                        RMDBGLOG((LOCALDBG, "%zu symbols loaded!\n", m_symMgr.size()));
                        if (m_structDB.open( m_filePack.sInterfaceFile.c_str() )) {
                            RMDBGLOG((LOCALDBG, "%zu structures loaded!\n", m_structDB.size()));
                            bRes = true;
                        }
                    }
                }

            } else {
                RMDBGLOG((LOCALDBG, "ERROR: Invalid chip ID [%s]\n", m_sChipID.c_str()));
            }

        }
    }

    m_flags.flag_mutex.lock();
    m_flags.bits.bValid = bRes;
    m_flags.flag_mutex.unlock();

    return bRes;
}

void targetEngine::close()
{
    std::lock_guard<std::mutex> guard(m_mutex);

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    m_filePack.clear();
    m_symMgr.Clear();

    close_gbus();

    m_sChipID.clear();
    m_sBlockID.clear();

    m_flags.flag_mutex.lock();
    m_flags.bits.bValid = false;
    m_flags.flag_mutex.unlock();
}

/**
 *  Find all relevant files.
 */

bool targetEngine::resolve_files()
{
    bool bRes = false;

    if (m_filePack.resolve_package(m_sChipID,
                                   m_nEngineIndex,
                                   (m_eType == UCODE_DEBUG)?true:false,
                                   UCODE_PREFIX))
    {
#ifdef _DEBUG
        m_filePack.dump( stderr );
#endif
        bRes = true;
    }

    return bRes;
}

std::string targetEngine::get_chipid() const {
    return m_sChipID;
}

std::string targetEngine::get_blockid() const {
    return m_sBlockID;
}

std::string targetEngine::get_targetid() const {
    return m_sTarget;
}

/**
 *  Connect to the device specified in the EM8XXX_SERVER environment.
 */

//bool targetEngine::connect()
//{
//    bool        bRes        = false;
//    const char* szEnvVar    = nullptr;
//
//    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));
//
//    if ((szEnvVar = getenv("EM8XXX_SERVER")) != nullptr) {
//        bRes = connect(szEnvVar);
//    }
//
//    return bRes;
//}

/**
 *  Connect to the device specified in the sHostSpec string.
 */

bool targetEngine::connect(std::string sHostSpec)
{
    bool            bRes = false;
    LLAD_PTR        pLlad;

    std::lock_guard<std::mutex> guard(m_mutex);

    RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__, sHostSpec.c_str()));

    if (sHostSpec.empty()) {
        const char* szEnvVar    = nullptr;
        if ((szEnvVar = getenv("EM8XXX_SERVER")) != nullptr) {
            sHostSpec = szEnvVar;
        } else {
            RMDBGLOG((LOCALDBG, "No host specified!\n"));
            return false;
        }
    }

    pLlad = std::make_shared<llad>(sHostSpec);
    if (pLlad && pLlad->is_valid()) {
        m_pGbus = std::make_shared<gbus>(pLlad);

        if (m_pGbus && m_pGbus->is_valid()) {
            RMDBGLOG((LOCALDBG, "Connected to %s\n", sHostSpec.c_str()));

            m_sTarget = sHostSpec;
            bRes = true;
        }
    }

    m_flags.flag_mutex.lock();
    m_flags.bits.bConnected = bRes;
    m_flags.flag_mutex.unlock();

    return bRes;
}

bool targetEngine::connect(GBUS_PTR pGbus)
{
    bool bRes = false;

    if (pGbus && pGbus->is_valid()) {
        m_pGbus = pGbus;
        bRes    = true;
    }

    return bRes;
}

void targetEngine::disconnect()
{
    std::lock_guard<std::mutex> guard(m_mutex);

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    close_gbus();
}

void targetEngine::lock_mutex()
{
    m_mutex.lock();
}

void targetEngine::unlock_mutex()
{
    m_mutex.unlock();
}

/**
 * Should be called with mutex locked.
 */

void targetEngine::close_gbus()
{
    m_flags.flag_mutex.lock();
    if (m_flags.bits.bConnected) {
        m_pGbus.reset();
        m_flags.bits.bConnected = false;
    }
    m_flags.flag_mutex.unlock();
}

/**
 *
 */

bool targetEngine::get_info(std::string& sChipID, std::string& sBlockID, uint32_t& nEngineID)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    bool                        bRes = false;

    if (is_valid()) {
        sChipID   = m_sChipID;
        sBlockID  = m_sBlockID;
        nEngineID = m_nEngineIndex;

        bRes      = true;
    }

    return bRes;
}

/**
 *
 */

bool targetEngine::get_connection_info(std::string& sHostSpec)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    bool                        bRes = false;
    std::ostringstream          os;
    std::string                 sHost;
    RMuint32                    nDevice;

    if (is_connected()) {
        LLAD_PTR llad = m_pGbus->get_llad();

        if (llad) {
            llad->get_host_device(sHost, nDevice);
            os << sHost << ":" << nDevice;
            sHostSpec = os.str();
            bRes = true;
        }
    }

    return bRes;
}

/**
 *
 */

bool targetEngine::load_ucode()
{
    return load_ucode( m_filePack.sBinFile );
}

/**
 *
 */

bool targetEngine::load_ucode(std::string sUcodeFilename)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    bool                        bRes = false;
    struct stat                 statBuf;
    size_t                      binSize = 0;
    unsigned char* 	            pBinData = nullptr;

    RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__, sUcodeFilename.c_str()));

    if (stat( sUcodeFilename.c_str(), &statBuf) == 0) {
        FILE*       ifp = nullptr;
        RMuint32    dram_low_offset = 0,
                    dram_high_offset = 0;

        binSize = statBuf.st_size;

        if ((ifp = fopen(sUcodeFilename.c_str(), "r")) != nullptr) {
            size_t bytesread __attribute__((unused));
//          assert(bytesread == binSize);

            pBinData = new unsigned char[binSize];
            assert(pBinData != nullptr);

            bytesread  = fread(pBinData, 1, binSize, ifp);

            stop();

            ucode_utils::ucode_get_microcode_size(pBinData, binSize,
                                                  &dram_low_offset,
                                                  &dram_high_offset);

            ucode_utils::ucode_load_microcode(m_pGbus,
                                              m_engine.get_pmBase(),
                                              m_engine.get_dmBase(),
                                              m_dramBase, 2,
                                              pBinData, binSize);

            video_utils::video_set_ucode_dram_offset(CONTROL_IF,
                                                     m_engine.get_pmBase(),
                                                     m_dramBase);

            start();

            m_binSize = binSize;
            m_dram_hi = dram_high_offset;
            m_dram_lo = dram_low_offset;

            m_uiDRAMPtr += dram_high_offset;

            RMDBGLOG((LOCALDBG, "binSize = %zu dram_hi = 0x%08X dram_lo = 0x%08X\n",
                      m_binSize, m_dram_hi, m_dram_lo));
            RMDBGLOG((LOCALDBG, "uiDRAMPtr = 0x%08X\n", m_uiDRAMPtr));

            delete [] pBinData;

            file_utils::get_absolute_path(sUcodeFilename, m_sUcode);
            bRes = true;
        }
    }

    /* Update the flags */
    m_flags.flag_mutex.lock();
    m_flags.bits.bUcodeLoaded = bRes;
    m_flags.flag_mutex.unlock();

    return bRes;
}

/**
 *
 */

void targetEngine::get_ucode_offset(RMuint32* lo, RMuint32* hi)
{
    if (lo != nullptr) {
        *lo = m_dram_lo;
    }

    if (hi != nullptr) {
        *hi = m_dram_hi;
    }

    return;
}

/**
 *
 */

GBUS_PTR            targetEngine::get_gbusptr()
{
    return m_pGbus;
}

/**
 *
 */

structure_database* targetEngine::get_structdb()
{
    return &m_structDB;
}

/**
 *
 */

UcodeSymbolMgr*     targetEngine::get_symmgr()
{
    return &m_symMgr;
}

/**
 *
 */

PlatformEngine*     targetEngine::get_engine()
{
    return &m_engine;
}

/**
 *
 */

std::mutex*         targetEngine::get_mutex()
{
    return &m_mutex;
}

/**
 *  Start the Engine running.
 */

bool targetEngine::start()
{
    RMuint32 reset_control_reg = m_engine.get_ioBase() + m_resetOff;

    RMDBGLOG((LOCALDBG, "%s() control=0x%08X\n", __PRETTY_FUNCTION__,
              reset_control_reg));

    m_pGbus->gbus_write_uint32( reset_control_reg, DSP_RUN );
    //while (((m_pGbus->gbus_read_uint32(reset_control_reg) & 0x0000ff00) >> 8)!= DSP_RUN);

    m_flags.flag_mutex.lock();
    m_flags.bits.eState = DSP_RUN;
    m_flags.flag_mutex.unlock();

    return true;
}

/**
 *  Reset and Stop the engine
 */

bool targetEngine::stop()
{
    RMuint32 reset_control_reg = m_engine.get_ioBase() + m_resetOff;

    RMDBGLOG((LOCALDBG, "%s() control=0x%08X\n", __PRETTY_FUNCTION__,
              reset_control_reg));

    m_pGbus->gbus_write_uint32( reset_control_reg, DSP_RESET );
    m_pGbus->gbus_write_uint32( reset_control_reg, DSP_STOP );

    //while (((m_pGbus->gbus_read_uint32(reset_control_reg) & 0x0000ff00) >> 8)!= DSP_STOP);
    m_flags.flag_mutex.lock();
    m_flags.bits.eState = DSP_STOP;
    m_flags.flag_mutex.unlock();

    return true;
}


//void targetEngine::test_function()
//{
//    RMuint32 start, size;
//
//    video_utils::video_get_scheduler_memory(CONTROL_IF, m_engine.get_pmBase(), &start, &size);
//}

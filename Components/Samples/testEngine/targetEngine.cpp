#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platformDB/PlatformDatabase.h"
#include "fileresolver/fileresolver.h"
#include "symbolmgr/symbolmgr.h"
#include "targetEngine.h"

#define PLATFORM_DATABASE_FILE      "tango_platform_config.xml"
#define PDB_FILE_PATH               "../../../xml/"

using namespace std;

/**
 *  Constructor
 */

targetEngine::targetEngine(string sChipID, string sBlockID, uint32_t nEngineIndex, ucodeType type)
:   m_bValid(false),
    m_bConnected(false)
{
    // ctor
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
    return m_bValid;
}

bool targetEngine::is_connected() const
{
    return m_bConnected;
}

bool targetEngine::open(string sChipID, string sBlockID, uint32_t nEngineIndex, ucodeType eType)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    PlatformDatabase            platDB;
    bool                        bRes = false;

    m_sChipID   = sChipID;
    m_sBlockID  = sBlockID;
    m_eType     = eType;

    if (resolve_files()) {
        if (platDB.LoadDatabase(PLATFORM_DATABASE_FILE, PDB_FILE_PATH)) {
            PlatformChip chip;

#ifdef _DEBUG
            fprintf(stderr, "Database loaded!\n");
#endif // _DEBUG

            if (platDB.FindChip(chip, m_sChipID)) {
                PlatformBlock       block;
                size_t              engineCount;

#ifdef _DEBUG
                fprintf(stderr, "Chip found!\n");
#endif // _DEBUG

                block       = chip[m_sBlockID];
                engineCount = block.get_engine_count();

                if ((engineCount > 0) && (engineCount > nEngineIndex)) {
#ifdef _DEBUG
                    fprintf(stderr, "Block found!\n");
#endif // _DEBUG

                    m_engine = block[m_nEngineIndex];

#ifdef _DEBUG
                    m_engine.Dump(stderr);
#endif // _DEBUG

                    if (m_symMgr.LoadSymbols( m_filePack.sLabelFile )) {
#ifdef _DEBUG
                        fprintf(stderr, "%zu symbols loaded!\n", m_symMgr.size());
#endif // _DEBUG
                        if (m_structDB.open( m_filePack.sInterfaceFile.c_str() )) {
#ifdef _DEBUG
                            fprintf(stderr, "%zu structures loaded!\n", m_structDB.size());
#endif // _DEBUG
                            bRes = true;
                        }
                    }
                }

            } else {
                fprintf(stderr, "ERROR: Invalid chip ID [%s]\n", m_sChipID.c_str());
            }

        }
    }

    m_bValid = bRes;

    return bRes;
}

void targetEngine::close()
{
    std::lock_guard<std::mutex> guard(m_mutex);

    m_filePack.clear();
    m_symMgr.Clear();

    close_gbus();

    m_sChipID.clear();
    m_sBlockID.clear();

    m_bValid = false;
}

bool targetEngine::resolve_files()
{
    bool bRes = false;

    if (m_filePack.resolve_package(m_sChipID,
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

/**
 *  Connect to the device specified in the EM8XXX_SERVER environment.
 */

bool targetEngine::connect()
{
    bool        bRes        = false;
    const char* szEnvVar    = nullptr;


    if ((szEnvVar = getenv("EM8XXX_SERVER")) != nullptr) {
        bRes = connect(szEnvVar);
    }

    return bRes;
}

bool targetEngine::connect(std::string sHostSpec)
{
    bool            bRes = false;
    LLAD_PTR        pLlad;

    std::lock_guard<std::mutex> guard(m_mutex);

    pLlad = std::make_shared<llad>(sHostSpec);
    if (pLlad && pLlad->is_valid()) {
        m_pGbus = std::make_shared<gbus>(pLlad);

        if (m_pGbus && m_pGbus->is_valid()) {
#ifdef _DEBUG
            fprintf(stderr, "Connected to %s\n", sHostSpec.c_str());
#endif // _DEBUG
            m_bConnected = true;
            bRes = true;
        }
    }

    return bRes;
}

bool targetEngine::connect(GBUS_PTR pGbus)
{
    bool bRes = false;

    if (pGbus && pGbus->is_valid()) {
        m_pGbus = pGbus;
        bRes = true;
    }

    return bRes;
}

void targetEngine::disconnect()
{
    std::lock_guard<std::mutex> guard(m_mutex);

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
    if (m_bConnected) {
        m_pGbus.reset();
        m_bConnected = false;
    }
}

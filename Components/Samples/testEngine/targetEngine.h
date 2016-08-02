#ifndef __TARGET_ENGINE_H__
#define __TARGET_ENGINE_H__

#include <mutex>
#include <string>
#include <memory>

#include "platformDB/PlatformDatabase.h"
#include "fileresolver/fileresolver.h"
#include "structure_control/structure_control.h"
#include "symbolmgr/symbolmgr.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

class controlInterface {
public:
    virtual GBUS_PTR            get_gbusptr()  = 0;
    virtual structure_database* get_structdb() = 0;
    virtual UcodeSymbolMgr*     get_symmgr()   = 0;
    virtual PlatformEngine*     get_engine()   = 0;
    virtual std::mutex*         get_mutex()    = 0;
};

/**
 *
 */

class targetEngine : public controlInterface {
public:

    enum ucodeType {
        UCODE_DEBUG,
        UCODE_RELEASE,
    };

    targetEngine(std::string sChipID,
                 std::string sBlockID,
                 uint32_t engineIndex = 0,
                 ucodeType eType = UCODE_RELEASE);
    virtual ~targetEngine();

    bool                is_valid() const;
    bool                is_connected() const;

    bool                open(std::string sChipID,
                             std::string sBlockID,
                             uint32_t engineIndex,
                             ucodeType eType = UCODE_RELEASE);
    void                close();

    bool                connect();
    bool                connect(std::string sHostSpec);
    bool                connect(GBUS_PTR pGbus);

    void                disconnect();

    bool                get_info(std::string& sChipID, std::string& sBlockID, uint32_t& engine);
    bool                get_connection_info(std::string& sHostSpec);

    /* Ucode functions */
    bool                load_ucode();
    bool                load_ucode(std::string sUcodeFilename);

    /* Engine control functions */

    bool                start();
    bool                stop();

    /* Control Interface functions */

    GBUS_PTR            get_gbusptr();
    structure_database* get_structdb();
    UcodeSymbolMgr*     get_symmgr();
    PlatformEngine*     get_engine();
    std::mutex*         get_mutex();

    void                test_function();

    void                get_ucode_offset(RMuint32* lo, RMuint32* hi);

    bool                set_dram_base(RMuint32 dram_base);

protected:

    bool                resolve_files();

    void                lock_mutex();
    void                unlock_mutex();

    bool                m_bValid;
    bool                m_bConnected;

    std::string         m_sChipID;
    std::string         m_sBlockID;
    uint32_t            m_nEngineIndex;
    ucodeType           m_eType;

    std::mutex          m_mutex;
    PlatformEngine      m_engine;
    FILE_PACK           m_filePack;
    UcodeSymbolMgr      m_symMgr;
    structure_database  m_structDB;
    GBUS_PTR            m_pGbus;

    RMuint32            m_dramBase;
    RMuint32            m_uiDRAMPtr;
    RMuint32            m_binSize;
    RMuint32            m_dram_lo;
    RMuint32            m_dram_hi;

    RMuint32            m_resetOff;

private:

    void                close_gbus();
};

#if (__cplusplus >= 201103L)
typedef std::shared_ptr<targetEngine>   TARGET_ENGINE_PTR;
#else
typedef targetEngine*                   TARGET_ENGINE_PTR;
#endif

#define UCODE_PREFIX "../../../"

#define DRAM_BASE       0xa8000000 // hardcoded value in a free Dram zone


#define DSP_RUN                 0x00
#define DSP_STOP                0x01
#define DSP_RESET               0x03

#endif // __TARGET_ENGINE_H__

#ifndef __TARGET_ENGINE_H__
#define __TARGET_ENGINE_H__

#include <mutex>
#include <string>
#include <memory>
#include <atomic>

#include "platformDB2/libplatformdb.h"
#include "fileresolver/fileresolver.h"
#include "structure_control/structure_control.h"
#include "symbolmgr/symbolmgr.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

struct engineFlags {
    mutable std::mutex flag_mutex;

    union {
        struct {
            uint32_t eState       :2;
            uint32_t bUcodeLoaded :1;
            uint32_t bConnected   :1;
            uint32_t bValid       :1;
        } bits;

        uint32_t  value = 0;
    };
};

class targetEngine;

/**
 *  controlInterface is a pure virtual interface providing utilities with
 *  objects including the gbus pointer, structure database object, symbol
 *  manager, current platform engine, and the mutex object.
 */

class controlInterface {
public:
    virtual GBUS_PTR            get_gbusptr()  = 0;
    virtual structure_database* get_structdb() = 0;
    virtual UcodeSymbolMgr*     get_symmgr()   = 0;
    virtual PlatformEngine*     get_engine()   = 0;
    virtual std::mutex*         get_mutex()    = 0;
    virtual targetEngine*       get_target()   = 0;
};

/**
 *  targetEngine encapsulates the target engine block on the remote system.
 */

class targetEngine : public controlInterface {
public:
    /*! Enumerated type indicating microcode type */
    enum ucodeType {
        UCODE_DEBUG,
        UCODE_RELEASE,
    };

    targetEngine(std::string sChipID,
                 std::string sBlockID,
                 uint32_t engineIndex = 0,
                 ucodeType eType = UCODE_RELEASE,
                 std::string sPathToUcode = "../../../",
                 std::string sPathToDatabase = "../../../xml/");
    virtual ~targetEngine();

    /*! Return true if the targetEngine is valid */
    bool                is_valid() const;
    /*! Return true if the targetEngine is connected to a remote system. */
    bool                is_connected() const;
    /*! Return true if the ucode is loaded on the targetEngine. */
    bool                is_ucode_loaded() const;

    /*! Open the targetEngine using Chip and Block ID, and engine index. */
    bool                open(std::string sChipID,
                             std::string sBlockID,
                             uint32_t engineIndex = 0,
                             ucodeType eType = UCODE_RELEASE);
    /*! Close the targetEngine. */
    void                close();
    /*! Connect to the remote system specified by the EM8XXX_SERVER environment. */
//  bool                connect();
    /*! Connect to the remote system specified by sHostSpec string. */
    bool                connect(std::string sHostSpec = "");
    /*! Connect the target to an existing GBUS_PTR object. */
    bool                connect(GBUS_PTR pGbus);
    /*! Disconnect the targetEngine from the remote system. */
    void                disconnect();

    bool                get_info(std::string& sChipID, std::string& sBlockID, uint32_t& engine);
    bool                get_connection_info(std::string& sHostSpec);

    /*! Load microcode from default location. */
    bool                load_ucode();
    /*! Load microcode from file specified in sUcodeFilename string. */
    bool                load_ucode(std::string sUcodeFilename);

    std::string         get_ucode_file(bool bFullPath = false);

    /* Engine control functions */

    bool                start();
    bool                stop();

    /* Control Interface functions */

    GBUS_PTR            get_gbusptr();
    structure_database* get_structdb();
    UcodeSymbolMgr*     get_symmgr();
    PlatformEngine*     get_engine();
    std::mutex*         get_mutex();
    targetEngine*       get_target();

//    void                test_function();

    void                get_ucode_offset(RMuint32* lo, RMuint32* hi);

    bool                set_dram_base(RMuint32 dram_base);

    std::string         get_chipid() const;
    std::string         get_blockid() const;
    std::string         get_targetid() const;


    friend std::ostream& operator<<(std::ostream& os,const targetEngine& engine);

protected:

    bool                resolve_files();

    void                lock_mutex();
    void                unlock_mutex();

//    std::atomic<bool>   m_bValid;
//    std::atomic<bool>   m_bConnected;
//    std::atomic<bool>   m_bUcodeLoaded;

    engineFlags         m_flags;

    std::string         m_sChipID;
    std::string         m_sBlockID;
    std::string         m_sTarget;
    std::string         m_sUcode;

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

    std::string         m_sPathToUcode;
    std::string         m_sPathToDatabase;

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
//#define DRAM_OFFSET     0x30000000
#define DRAM_OFFSET     0

#define DSP_RUN                 0x00
#define DSP_STOP                0x01
#define DSP_RESET               0x03

inline TARGET_ENGINE_PTR CREATE_NEW_ENGINE(std::string chip,
                                           std::string blockID,
                                           int engineNo = 0,
                                           targetEngine::ucodeType type = targetEngine::UCODE_RELEASE,
                                           std::string sPathToUcode = "../../../",
                                           std::string sPathToDatabase = "../../../xml/")
{
    return std::make_shared<targetEngine>(chip, blockID, engineNo, type, sPathToUcode, sPathToDatabase);
}

#endif // __TARGET_ENGINE_H__

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

/**
 *
 */

class targetEngine {
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

private:

    void                close_gbus();

};

#if (__cplusplus >= 201103L)
typedef std::shared_ptr<targetEngine>   TARGET_ENGINE_PTR;
#else
typedef targetEngine*                   TARGET_ENGINE_PTR;
#endif

#define UCODE_PREFIX "../../../"

#endif // __TARGET_ENGINE_H__

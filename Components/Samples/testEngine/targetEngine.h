#ifndef __TARGET_ENGINE_H__
#define __TARGET_ENGINE_H__

#include "platformDB/PlatformDatabase.h"
#include "fileresolver/fileresolver.h"
#include "structure_control/structure_control.h"
#include "symbolmgr/symbolmgr.h"

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

    bool                is_valid();

    bool                open(std::string sChipID,
                             std::string sBlockID,
                             uint32_t engineIndex,
                             ucodeType eType = UCODE_RELEASE);
    void                close();


protected:

    bool                resolve_files();

    bool                m_bValid;

    std::string         m_sChipID;
    std::string         m_sBlockID;
    uint32_t            m_nEngineIndex;
    ucodeType           m_eType;

    PlatformEngine      m_engine;
    FILE_PACK           m_filePack;
    UcodeSymbolMgr      m_symMgr;
    SYMBOL_MAP          m_symMap;
    structure_database  m_structDB;
};

#define UCODE_PREFIX "../../../"

#endif // __TARGET_ENGINE_H__

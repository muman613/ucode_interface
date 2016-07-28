#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platformDB/PlatformDatabase.h"
#include "fileresolver/fileresolver.h"
#include "symbolmgr/symbolmgr.h"
#include "targetEngine.h"

#define PLATFORM_DATABASE_FILE      "tango_platform_config.xml"

using namespace std;

targetEngine::targetEngine(string sChipID, string sBlockID, uint32_t nEngineIndex, ucodeType type)
:   m_bValid(false)
{
    // ctor

    open(sChipID, sBlockID, nEngineIndex, type);
}

targetEngine::~targetEngine()
{
    // dtor
}

bool targetEngine::open(string sChipID, string sBlockID, uint32_t nEngineIndex, ucodeType eType)
{
    PlatformDatabase    platDB;
    bool                bRes = false;

    m_sChipID   = sChipID;
    m_sBlockID  = sBlockID;
    m_eType     = eType;

    if (resolve_files()) {
        if (platDB.LoadDatabase(PLATFORM_DATABASE_FILE, "../../../xml/")) {
            PlatformChip chip;

            fprintf(stderr, "Database loaded!\n");

            if (platDB.FindChip(chip, m_sChipID)) {
                PlatformBlock       block;
                size_t              engineCount;

                fprintf(stderr, "Chip found!\n");

                block       = chip[m_sBlockID];
                engineCount = block.get_engine_count();

                if ((engineCount > 0) && (engineCount > nEngineIndex)) {
                    fprintf(stderr, "Block found!\n");

                    m_engine = block[m_nEngineIndex];

                    m_engine.Dump(stderr);

                    if (m_symMgr.LoadSymbols( m_filePack.sLabelFile )) {
                        fprintf(stderr, "%zu symbols loaded!\n", m_symMgr.size());

                        if (m_structDB.open( m_filePack.sInterfaceFile.c_str() )) {
                            fprintf(stderr, "%zu structures loaded!\n", m_structDB.size());
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
    m_filePack.clear();
    m_symMgr.Clear();
    m_bValid = false;
}

bool targetEngine::resolve_files()
{
    bool bRes = false;
    if (m_filePack.resolve_package(m_sChipID, (m_eType == UCODE_DEBUG)?true:false, UCODE_PREFIX)) {
        m_filePack.dump( stderr );
        bRes = true;
    }

    return bRes;
}

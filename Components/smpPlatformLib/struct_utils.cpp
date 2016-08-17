#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <assert.h>
#include <stdexcept>
#define ALLOW_OS_CODE
#include "targetInterfaceBase.h"
#include "structure_control/structure_control.h"
#include "struct_utils.h"
#include "string_utils.h"

#ifdef _DEBUG
#define LOCALDBG DISABLE
#else
#define LOCALDBG DISABLE
#endif // _DEBUG

namespace struct_utils {

RMuint32 resolve_offset(controlInterface* pIF, RMuint32 memBase,
                        std::string sStructure, std::string sMembers)
{
    return resolve_offset(pIF->get_structdb(), memBase, sStructure, sMembers);
}

RMuint32 resolve_offset(structure_database* pDB, RMuint32 memBase,
                        std::string sStructure, std::string sMembers)
{
    const structure_definition*     pStruct = nullptr;
    RMuint32                        gBusAddress = memBase;

    pStruct = pDB->get_structure( (const char*)sStructure.c_str() );
    if (pStruct != nullptr) {
        std::vector<std::string> sMembVec;

        if (string_utils::split( sMembers, '.', sMembVec )) {
            const structure_definition *pSub = pStruct;
            RMuint32  offset = 0;

            for (auto member : sMembVec) {
                assert(pSub != nullptr);
                if (pSub == nullptr) {
                    throw std::runtime_error("Undefined type");
                }

                const member_definition* pMemb = pSub->member( (const char*)member.c_str() );
                if (pMemb != nullptr) {
                    std::string sType = pMemb->type();

                    offset += pMemb->offset();

                    pSub = pDB->get_structure( (const char*)sType.c_str() );
                }
            }

            gBusAddress += offset;
        } else {
            RMDBGLOG((LOCALDBG, "No members specified!\n"));
        }
    } else {
        /* Error */
        RMDBGLOG((LOCALDBG, "ERROR: Unable to find structure '%s'!\n",
                  sStructure.c_str()));
        throw std::runtime_error("Unable to find structure");
    }

    RMDBGLOG((LOCALDBG, "Resolved %s->%s @ 0x%08x\n", sStructure.c_str(), sMembers.c_str(), gBusAddress));

    return gBusAddress;
}

/**
 *
 */

bool write_structure_member(controlInterface* pIF,
                            RMuint32 memBase,
                            std::string sStructure,
                            std::string sMembers,
                            RMuint32 value)
{
try {
    RMuint32 gBusAddress = resolve_offset( pIF->get_structdb(), memBase, sStructure, sMembers);

    pIF->get_gbusptr()->gbus_write_uint32( gBusAddress, value );

    return true;
}
catch (std::runtime_error& except) {
    RMDBGLOG((LOCALDBG, "Caught exception %s!\n", except.what()));
    return false;
}
}

/**
 *
 */

bool read_structure_member(controlInterface* pIF,
                            RMuint32 memBase,
                            std::string sStructure,
                            std::string sMembers,
                            RMuint32* value)
{
try {
    RMuint32 gBusAddress = resolve_offset( pIF->get_structdb(), memBase, sStructure, sMembers);

    *value = pIF->get_gbusptr()->gbus_read_uint32( gBusAddress );

    return true;
}
catch (std::runtime_error& except) {
    RMDBGLOG((LOCALDBG, "Caught exception %s!\n", except.what()));
    return false;
}
}

/**
 *
 */

RMuint32 get_structure_size(controlInterface* pIF, std::string sStructure) {
    RMuint32 structSize = 0L;
    assert(pIF != nullptr);

    RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__, sStructure.c_str()));

    structSize = (RMuint32)pIF->get_structdb()->get_structure( sStructure.c_str() )->size();

    return structSize;
}
};

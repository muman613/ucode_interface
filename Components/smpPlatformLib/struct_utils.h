#ifndef __STRUCT_UTILS_H__
#define __STRUCT_UTILS_H__

#include <string>
#include "rmdef/rmdef.h"

class structure_database;

namespace struct_utils {

    RMuint32 resolve_offset(structure_database* pDB, RMuint32 memBase,
                            std::string sStructure, std::string sMembers);
    RMuint32 resolve_offset(controlInterface* pIF, RMuint32 memBase,
                            std::string sStructure, std::string sMembers);
    bool write_structure_member(controlInterface* pIF,
                                RMuint32 memBase,
                                std::string sStructure,
                                std::string sMembers,
                                RMuint32 value);
    bool read_structure_member(controlInterface* pIF,
                               RMuint32 memBase,
                               std::string sStructure,
                               std::string sMembers,
                               RMuint32* value);

    RMuint32 get_structure_size(controlInterface* pIF, std::string sStructure);
};

#endif // __STRUCT_UTILS_H__


#ifndef __FILERESOLVER_H__
#define __FILERESOLVER_H__

#include <string>

class FILE_PACK {
public:
    void            dump(FILE* oFP);

    std::string     sBinFile;
    std::string     sLabelFile;
    std::string     sMapFile;
    std::string     sListFile;

    bool            resolve_package(std::string sChildID,
                                    bool bDebug,
                                    std::string sPrefix = "");

    bool            isvalid();
};

bool resolve_package(std::string sChipId, bool bDebug,
                     FILE_PACK& pack, std::string sPrefix = "");

#endif // __FILERESOLVER_H__


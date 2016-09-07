#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "fileresolver.h"

/* Handy macros used by module */

#define RESET_STREAM(x)                                                         \
    (x).str("");                                                                \
    (x).clear();

#define VERIFY_FILE_EXISTS( fileVar )                                           \
    {                                                                           \
        struct stat     st;                                                     \
        if (stat( (fileVar).c_str(), &st ) != 0) {                              \
            return false;                                                       \
        } else if (S_ISDIR(st.st_mode))                                                 \
            return false;                                                       \
    }


bool resolve_package(std::string sChipId, int engineId, bool bDebug,
                     FILE_PACK& pack, std::string sPrefix)
{
    std::ostringstream os;

    if (sPrefix.empty())
        sPrefix = "./";
    else {
        if (sPrefix[sPrefix.size() - 1] != '/')
            sPrefix += "/";
    }

    if (((sChipId == "8758") || (sChipId == "8756")) &&
        (engineId == 1))
    {
        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << "_h265.bin";
        pack.sBinFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << "_h265.lst";
        pack.sListFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << "_h265.map";
        pack.sMapFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << "_h265_labels.h";
        pack.sLabelFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)"/video_interface.hh";
        pack.sInterfaceFile = os.str();
        RESET_STREAM(os);
    } else {
        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << ".bin";
        pack.sBinFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << ".lst";
        pack.sListFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << ".map";
        pack.sMapFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)((bDebug == false)?"/release/":"/debug/") << (std::string)"video_microcode_SMP" << sChipId << "_labels.h";
        pack.sLabelFile = os.str();
        RESET_STREAM(os);

        os << sPrefix + (std::string)"ucode/" << sChipId << (std::string)"/video_interface.hh";
        pack.sInterfaceFile = os.str();
        RESET_STREAM(os);
    }

    return true;
}

/**
 *  Dump the file pack values.
 */

void FILE_PACK::dump(FILE* oFP) {
    fprintf(oFP, "---------------------------------------------------------\n");
    fprintf(oFP, "File Pack Dump:\n");
    fprintf(oFP, "---------------------------------------------------------\n");
    fprintf(oFP, "BinFile   = %s\n", sBinFile.c_str());
    fprintf(oFP, "ListFile  = %s\n", sListFile.c_str());
    fprintf(oFP, "LabelFile = %s\n", sLabelFile.c_str());
    fprintf(oFP, "MapFile   = %s\n", sMapFile.c_str());
    fprintf(oFP, "Interface = %s\n", sInterfaceFile.c_str());
    fprintf(oFP, "---------------------------------------------------------\n");

    return;
}

bool FILE_PACK::resolve_package(std::string sChipId, int engineId, bool bDebug, std::string sPrefix)
{
    return ::resolve_package(sChipId, engineId, bDebug, *this, sPrefix);
}

bool FILE_PACK::isvalid()
{
    VERIFY_FILE_EXISTS( sBinFile );
    VERIFY_FILE_EXISTS( sListFile );
    VERIFY_FILE_EXISTS( sLabelFile );
    VERIFY_FILE_EXISTS( sMapFile );

    return true;
}

void FILE_PACK::clear()
{
    sBinFile.clear();
    sListFile.clear();
    sLabelFile.clear();
    sMapFile.clear();
    sInterfaceFile.clear();
}

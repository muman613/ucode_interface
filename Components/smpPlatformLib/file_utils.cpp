#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define ALLOW_OS_CODE 1
#include "rmdef/rmdef.h"
#include "file_utils.h"

#ifdef _DEBUG
#define LOCALDBG        DISABLE
#else
#define LOCALDBG        DISABLE
#endif // _DEBUG

namespace file_utils {

    RMstatus file_exists(std::string sFilename) {
        return file_exists(sFilename.c_str());
    }

    /**
     *  Check if a file exists.
     *
     *  Return RM_OK if file exists, otherwise return RM_ERROR.
     */

    RMstatus file_exists(const char* szFilename) {
        RMstatus        result = RM_ERROR;
        struct stat     statbuf;

        RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__, szFilename));

        if (stat( szFilename, &statbuf ) == 0) {
            RMDBGLOG((LOCALDBG, "-- file %s exists!\n", szFilename));
            result = RM_OK;
        } else {
            RMDBGLOG((LOCALDBG, "-- file %s does not exist!\n", szFilename));
        }

        return result;
    }

    bool can_write_file(std::string sFilename) {
        return can_write_file(sFilename.c_str());
    }

    /**
     *  Attempt to open file for writing, if no error return true.
     */

    bool can_write_file(const char* szFilename) {
        bool        bRes    = false;
        FILE*       fp      = nullptr;

        RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__, szFilename));
        assert(szFilename != nullptr);

        if (strlen(szFilename) > 0) {
            if ((fp = fopen(szFilename, "w")) != nullptr) {
                RMDBGLOG((LOCALDBG, "-- can write file!\n"));
                fclose(fp);
                unlink(szFilename);
                bRes = true;
            } else {
                RMDBGLOG((LOCALDBG, "Unable to open file %s!\n", strerror(errno)));
            }
        } else {
            RMDBGLOG((LOCALDBG, "No filename specified!\n"));
        }

        return bRes;
    }

    bool get_absolute_path(const std::string& filePath, std::string& absolutePath) {
        bool bRes = false;
        char* szTmp = nullptr;

        if ((szTmp = realpath(filePath.c_str(), nullptr)) != nullptr) {
            absolutePath = szTmp;
            free(szTmp);
            bRes = true;
        } else {
            RMDBGLOG((LOCALDBG, "get_absolute_path failed %s\n", strerror(errno)));
        }

        return bRes;
    }
}

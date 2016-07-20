/**
 *	Utility functions
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/select.h>
#include <termios.h>
#include <assert.h>
#include <sys/ioctl.h>

#define ALLOW_OS_CODE 1

#include "llad/include/llad.h"
#include "llad/include/gbus.h"
#include "utils.h"

/**
 *
 */

int parse_numeric(const char* str, RMuint32 *pValue) {
    if ((pValue != 0) && (str != 0)) {
        if (strlen(str) > 2) {
            if ((str[0] == '0') && (str[1] == 'x')) {
                sscanf(str, "0x%lx", pValue);
            } else {
                sscanf(str, "%ld", pValue);
            }
        } else {
            sscanf(str, "%ld", pValue);
        }
    }
}

/**
 *	Query file size, allocate buffer, read data, return pointer to buffer and length
 */

int load_buffer_from_file(const char* szFilename, RMuint8** pBuffer, RMuint32* pLength)
{
    int res = 0;
    struct stat st;
    size_t len = 0L;

    assert(( pBuffer != 0L ) && ( pLength != 0 ));

    /* Stat file to determine file size */
    if (stat(szFilename, &st) == 0) {
        FILE* fp = 0L;

        len = st.st_size;
        *pBuffer = (RMuint8*)malloc(len);

        assert(pBuffer != NULL);
        
        if ((fp = fopen(szFilename, "r")) != 0L) {
            if (fread(*pBuffer, 1, len, fp) != len) {
                fprintf(stderr, "ERROR: Unable to read file!\n");
            }
            fclose(fp);
            *pLength = len;
            res = 1;
        }
    }

    return res;
}

/**
 *
 */

int allocate_buffer(RMuint8** pBuffer, RMuint32 len)
{
    assert( pBuffer != 0L );

    *pBuffer = (RMuint8*)malloc(len);

    return (*pBuffer != 0)?1:0;
}

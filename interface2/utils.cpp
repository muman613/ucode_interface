#include <stdio.h>
#include <stdlib.h>
//#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/select.h>
#include <termios.h>
#include <libgen.h>
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <spawn.h>
#include <errno.h>
#include <assert.h>
#include <sys/ioctl.h>

#define ALLOW_OS_CODE 1

#include "llad/include/llad.h"
#include "llad/include/gbus.h"
//#include "emhwlib/src/emhwlib_internal.h"
//#include "ucode_api/include/ucode_interface.h"
#include "test_interface.h"
#include "video_interface.h"
#include "utils.h"

#define FRAMEINSPECTOR_EXE      "/usr/local/bin/frameInspector"

RMstatus file_exists(std::string sFilename) {
    return file_exists(sFilename.c_str());
}
/**
 *  Check if a file exists.
 *
 *  Return RM_OK if file exists, otherwise return RM_ERROR.
 */

RMstatus file_exists(const char* szFilename)
{
    RMstatus        result = RM_ERROR;
    struct stat     statbuf;

//  fprintf(stderr, "file_exists(%s)\n", szFilename);

    if (stat( szFilename, &statbuf ) == 0)
    {
//      fprintf(stderr, "-- file %s exists!\n", szFilename);
        result = RM_OK;
    }
    else
    {
        //fprintf(stderr, "-- FILE DOES NOT EXIST!\n");
    }

//  fprintf(stderr, "result = %d\n", result);

    return result;
}

/**
 *  Caseless string compare function.
 */

int stricmp(char const *a, char const *b)
{
    for (;; a++, b++)
    {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

#ifndef ENABLE_CURSES
int _kbhit(void)
{
    static const int STDIN = 0;
    static int initialized = 0;
    int bytesWaiting;

    if (initialized == 0)
    {
        // Use termios to turn off line buffering
        struct termios term;

        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }

    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

static struct termios orig_term_attr;

void set_terminal_mode()
{
    struct termios new_term_attr;

    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    return;
}

void reset_terminal_mode()
{
    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);
}

int getkey()
{
    int character;

    character = fgetc(stdin);

    return character;
}

#endif // ENABLE_CURSES

struct profileEntry {
    const char*     szIdent;
    int             nProfile;
};

struct timespec difftimespec(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

double get_ts_seconds(struct timespec spec) {
    double secs = 0.0;

    secs = (double)(((RMuint64)spec.tv_sec * 1000000000) + (RMuint64)spec.tv_nsec)/ (double)1000000000;

    return secs;
}

/**
 *  Table which relates abbreviation string to codec ID.
 */

static struct profileEntry profileTable[] = {
    { "mpeg2",  VideoProfileMPEG2, },
    { "mpeg4",  VideoProfileMPEG4, },
    { "h264",   VideoProfileH264, },
    { "h265",   VideoProfileH265, },
    { "hevc",   VideoProfileH265, },
    { 0L, 0, },
};

/**
 *
 */

RMint32 get_profile_id_from_string(const char* szCodecID) {
//  RMuint32            codec_id = -1;
    struct profileEntry *pCurEntry = profileTable;

    while (pCurEntry->szIdent != NULL) {
        if (stricmp(pCurEntry->szIdent, szCodecID) == 0) {
            return pCurEntry->nProfile;
        }
        pCurEntry++;    // Advance to next profile entry...
    }

    return -1;
}

/**
 *
 */

const char* get_profile_string_from_id(RMint32 codec_id) {
//  const char* szCodecID = 0L;
    struct profileEntry *pCurEntry = profileTable;

    while (pCurEntry->szIdent != NULL) {
        if (pCurEntry->nProfile == codec_id) {
            return pCurEntry->szIdent;
        }
        pCurEntry++;    // Advance to next profile entry...
    }

    return NULL;
}

/** standard c version **/
char* generate_output_yuv(const char* szPath, const char* szInputName) {
    char*   szResult = 0L;
    char*   szBaseName = 0L;
    char*   szInputDup = 0L;
    char*   szExt = 0L;
    size_t  len = 0;

    assert((szPath != 0L) && (szInputName != 0L));

    szInputDup = strdup(szInputName);

    szBaseName = basename( (char*)szInputDup );

    /* Remove dot extension from filename */
    if ((szExt = strrchr(szBaseName, '.')) != NULL) {
        *szExt = 0;
    }

    len = strlen(szPath) + 1 + strlen(szBaseName) + 4;

    szResult = (char *)malloc(len);
    *szResult = 0;
    strcpy(szResult, szPath);
    if (szPath[strlen(szPath) - 1] != '/')
        strcat(szResult, "/");
    strcat(szResult, szBaseName);
    strcat(szResult, ".yuv");

    return szResult;
}

/** c++ version */
std::string generate_output_yuv(std::string sPath, std::string sInputName) {
    std::string sYUVFile;
    std::string sBaseName;
    std::string sInputDup = sInputName;
    std::ostringstream os;
    std::size_t pos;

    sBaseName = basename( (char *)sInputDup.c_str() );

    if ((pos = sBaseName.find_last_of('.')) != std::string::npos) {
        sBaseName = sBaseName.substr(0, pos);
    }

    if (sPath[sPath.size()-1] != '/')
        sPath += "/";

    os << sPath << sBaseName << ".yuv";

    sYUVFile = os.str();

    return sYUVFile;
}

void set_tile_dimensions(CONTEXT* ctx, RMuint32 tsw, RMuint32 tsh)
{
    ctx->tile_width_l2       = tsw;
    ctx->tile_height_l2      = tsh;
    ctx->pvc_tw              = (1 << tsw);
    ctx->pvc_th              = (1 << tsh);
    ctx->pvc_ts              = ctx->pvc_tw * ctx->pvc_th;

    return;
}

typedef struct {
    std::string sID;
    RMuint32    tileW;
    RMuint32    tileH;
} tileDef;

static tileDef  chipTileSizes[] = {
    { "8758", 8, 5, },
    { "8760", 9, 5, },
};

bool set_tile_dimensions(CONTEXT* ctx, std::string sChipId)
{
    for (size_t i = 0 ; i < sizeof(chipTileSizes)/sizeof(tileDef) ; i++) {
        if (sChipId == chipTileSizes[i].sID) {
            set_tile_dimensions( ctx, chipTileSizes[i].tileW, chipTileSizes[i].tileH);
            return true;
        }
    }

    set_tile_dimensions( ctx, 8, 5 );

    return false;
}

/**
 *  Run the frameInspector to view the capture file.
 */

// arg0 /usr/local/bin/frameInspector
// arg1 -f
// arg2 filename
// arg3 -s
// arg4 WxH
// arg5 -c
// arg6 1

#ifdef ENABLE_CURSES
void launch_viewer(CONTEXT* pCtx)
{
    const char*         argv[8] = { FRAMEINSPECTOR_EXE,
                                    "-f",
                                    0,
                                    "-s",
                                    0,
                                    "-c",
                                    0,
                                    NULL };
    char                szFilename[1024];
    char                szDimensions[32];
    char                szFrame[8];
    pid_t               pid;

    if (pCtx->viewPid != 0) {
        kill(pCtx->viewPid, SIGKILL);
        pCtx->viewPid = 0;
    }

    if (pCtx->picture_count > 0) {
        snprintf(szFilename, 1024, "%s", pCtx->file.sYUVFilename.c_str());
        snprintf(szDimensions, 32, "%ldx%ld", pCtx->picture_w, pCtx->picture_h);
        snprintf(szFrame, 8, "%ld", pCtx->picture_count - 1);

        argv[2] = szFilename;
        argv[4] = szDimensions;
        argv[6] = szFrame;

        if (posix_spawn(&pid, FRAMEINSPECTOR_EXE, NULL, NULL,
                        (char* const*)argv, environ) == 0)
        {
            pCtx->viewPid = pid;
        } else {
            fprintf(stderr, "ERROR: Unable to spawn (%s)\n", strerror(errno));
        }
    }
}
#endif // ENABLE_CURSES
#ifdef _DEBUG

/* This debug stub is used for static libraries which use muman style debug */
extern FILE* NORMALMSG;

void debug(char const* sFmt, ...) {
    va_list list;

    va_start(list, sFmt);
    vfprintf( NORMALMSG, sFmt, list );
    va_end(list);

    return;
}

#endif // _DEBUG

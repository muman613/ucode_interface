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
//#include <stropts.h>
#include <assert.h>
#include <sys/ioctl.h>

#define ALLOW_OS_CODE 1

#include "llad/include/llad.h"
#include "llad/include/gbus.h"
//#include "emhwlib/src/emhwlib_internal.h"
//#include "ucode_api/include/ucode_interface.h"
#include "video_interface.h"
#include "utils.h"

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

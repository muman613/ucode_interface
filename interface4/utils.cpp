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
#include "utils.h"
//#include <unistd.h>
#include <fcntl.h>

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
//    new_term_attr.c_lflag &= ~(ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    fcntl(fileno(stdin), F_SETFL, O_NONBLOCK);
    printf("\e[?25l"); /* hide the cursor */

    return;
}

void reset_terminal_mode()
{
    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);
    fcntl(fileno(stdin), F_SETFL, ~O_NONBLOCK);
    printf("\e[?25h"); /* show the cursor */
}

int getkey()
{
    int character;

    character = fgetc(stdin);

    return character;
}

#endif // ENABLE_CURSES

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

#if 0
struct profileEntry {
    const char*     szIdent;
    int             nProfile;
};

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
    struct profileEntry *pCurEntry = profileTable;

    while (pCurEntry->szIdent != NULL) {
        if (pCurEntry->nProfile == codec_id) {
            return pCurEntry->szIdent;
        }
        pCurEntry++;    // Advance to next profile entry...
    }

    return NULL;
}
#endif // 0

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
        snprintf(szDimensions, 32, "%ldx%ld", (unsigned long)pCtx->picture_w, (unsigned long)pCtx->picture_h);
        snprintf(szFrame, 8, "%ld", (unsigned long)pCtx->picture_count - 1);

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

bool get_environment_string(const std::string sVarName, std::string& sValue) {
    const char* szValue = nullptr;

    if ((szValue = getenv(sVarName.c_str())) != 0) {
        sValue = szValue;
    } else {
        sValue.clear();
    }

    return (sValue.empty()?false:true);
}

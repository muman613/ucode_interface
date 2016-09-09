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
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sys/types.h>
#include <signal.h>

#include "utils.h"
//#include <unistd.h>
#include <fcntl.h>


#define FRAMEINSPECTOR_EXE      "/usr/local/bin/frameInspector"


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

void launch_viewer(const std::string sYUVFilename, int w, int h, int frame)
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
    static pid_t        viewPid = 0;
    pid_t               pid = 0;

    if (viewPid != 0) {
        kill(viewPid, SIGKILL);
        viewPid = 0;
    }

    if (frame > 0) {
        snprintf(szFilename, 1024, "%s", sYUVFilename.c_str());
        snprintf(szDimensions, 32, "%ldx%ld", (unsigned long)w, (unsigned long)h);
        snprintf(szFrame, 8, "%ld", (unsigned long)frame - 1);

        argv[2] = szFilename;
        argv[4] = szDimensions;
        argv[6] = szFrame;

        if (posix_spawn(&pid, FRAMEINSPECTOR_EXE, NULL, NULL,
                        (char* const*)argv, environ) == 0)
        {
            viewPid = pid;
        } else {
            fprintf(stderr, "ERROR: Unable to spawn (%s)\n", strerror(errno));
        }
    }
}

/**
 *
 */

bool get_environment_string(const std::string sVarName, std::string& sValue) {
    const char* szValue = nullptr;

    if ((szValue = getenv(sVarName.c_str())) != 0) {
        sValue = szValue;
    } else {
        sValue.clear();
    }

    return (sValue.empty()?false:true);
}

/**
 *
 */

std::string diffTime(const std::chrono::system_clock::time_point& start,
                     const std::chrono::system_clock::time_point& now)
{
    using namespace std::chrono;

//    steady_clock::time_point start = /* Some point in time */;
//    steady_clock::time_point now = steady_clock::now();

    int hhh = duration_cast<hours>(now - start).count();
    int mm = duration_cast<minutes>(now - start).count() % 60;
    int ss = duration_cast<seconds>(now - start).count() % 60;

    std::ostringstream stream;
    stream << std::setfill('0') << std::setw(2) << hhh << "h " <<
        std::setfill('0') << std::setw(2) << mm << "m " <<
        std::setfill('0') << std::setw(2) << ss << "s";
    std::string result = stream.str();

    return result;
}

/**
 *
 */

std::string asString(const std::chrono::system_clock::time_point& now) {
    char        sTimeBuffer[256];
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm     tm = *std::localtime(&t);
    std::strftime(sTimeBuffer, 256, "%r", &tm);
    return std::string(sTimeBuffer);
}



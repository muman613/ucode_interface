#ifndef	__UTILS_H__
#define __UTILS_H__

#include <time.h>
#include <string>
#include <chrono>

#ifndef ALLOW_OS_CODE
    #define ALLOW_OS_CODE
#endif
#include "rmdef/rmdef.h"


struct timespec difftimespec(struct timespec start, struct timespec end);
double get_ts_seconds(struct timespec spec);

std::string generate_output_yuv(std::string szPath, std::string szInputName);

void launch_viewer(const std::string sYUVFilename, int w, int h, int frame);

std::string diffTime(const std::chrono::system_clock::time_point& start,
                     const std::chrono::system_clock::time_point& now);
std::string asString(const std::chrono::system_clock::time_point& now);

#endif


#ifndef	__UTILS_H__
#define __UTILS_H__

#include <time.h>
#include <string>
#ifndef ALLOW_OS_CODE
    #define ALLOW_OS_CODE
#endif
#include "rmdef/rmdef.h"

#ifndef ENABLE_CURSES
int         _kbhit(void);
int         getkey();
void        set_terminal_mode();
void        reset_terminal_mode();
#endif // ENABLE_CURSES

struct timespec difftimespec(struct timespec start, struct timespec end);
double get_ts_seconds(struct timespec spec);

std::string generate_output_yuv(std::string szPath, std::string szInputName);

#ifdef ENABLE_CURSES
void launch_viewer(CONTEXT* pCtx);
#endif

#endif


#ifndef __MISC_UTILS_H__
#define __MISC_UTILS_H__

#include <time.h>
#include <string>

struct timespec     difftimespec(struct timespec start, struct timespec end);
double              get_ts_seconds(struct timespec spec);

#endif // __MISC_UTILS_H__

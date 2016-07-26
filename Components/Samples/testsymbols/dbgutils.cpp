#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <semaphore.h>
#include <pthread.h>
//#include "misc_utils.h"
#include "dbgutils.h"

/**
    MODULE      :   dbgutils.cpp
    PROJECT     :   Probe V2.0
    PROGRAMMER  :   Michael A. Uman
    COPYRIGHT   :   (C) 2009 Sigma Designs, Inc.
    DATE        :   December 23, 2013
 **/

#ifdef  _DEBUG

static pthread_mutex_t __dbg_mutex = PTHREAD_MUTEX_INITIALIZER;
static bool            __dbg_enable    = true;

/**
 *  Send debug message to standard error.
 */

void debug(const char* sFmt, ...) {
    va_list args;

    if (__dbg_enable == true) {
        pthread_mutex_lock (&__dbg_mutex);
        va_start(args, sFmt);
        vfprintf(stderr, sFmt, args );
        va_end(args);
        fflush(stderr);
        pthread_mutex_unlock (&__dbg_mutex);
    }

    return;
}

#endif  // __DEBUG

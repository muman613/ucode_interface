#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <semaphore.h>
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

static pthread_mutex_t __dbg_mutex;
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

#endif

/**
 *
 */

dbgMgr::dbgMgr(bool bLog) {
#ifdef  _DEBUG
    pthread_mutexattr_t mAttr;

    if (bLog == true) {
        freopen("/tmp/smpProbe.log", "w", stderr);
    }

    fprintf(stderr, "dbgMgr initialized!\n");

    pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP);      // setup recursive mutex for mutex attribute
    pthread_mutex_init(&__dbg_mutex, &mAttr);                                     // Use the mutex attribute to create the mutex
    pthread_mutexattr_destroy(&mAttr);                                  // Mutex attribute can be destroy after initializing the mutex variable
#else
    (void)bLog;
#endif  // _DEBUG
}

/**
 *
 */

dbgMgr::~dbgMgr() {
#ifdef _DEBUG
    pthread_mutex_destroy(&__dbg_mutex);
#endif
}

#ifdef  _DEBUG
/**
 *  Enable debug output.
 */

void dbgMgr::enable_dbg_out() {
    pthread_mutex_lock (&__dbg_mutex);
    __dbg_enable = true;
    debug("%s\n", "Debugging output enabled!");
    pthread_mutex_unlock (&__dbg_mutex);
}

/**
 *  Disable debug output.
 */

void dbgMgr::disable_dbg_out() {
    pthread_mutex_lock (&__dbg_mutex);
    __dbg_enable = true;
    debug("%s\n", "Debugging output disabled!");
    __dbg_enable = false;
    pthread_mutex_unlock (&__dbg_mutex);
}

/**
 *  Toggle debug output.
 */

void dbgMgr::toggle_dbg_out() {
    pthread_mutex_lock (&__dbg_mutex);
    if (__dbg_enable == true) {
        debug("%s\n", "Debugging output disabled!");
        __dbg_enable = false;
    } else {
        __dbg_enable = true;
        debug("%s\n", "Debugging output enabled!");
    }
    pthread_mutex_unlock (&__dbg_mutex);
}

#endif  // __DEBUG

/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmlibcw.h
  @brief  

  Describes a collection of libraries that abstracts some core OS functions.

  @author Emmanuel Michon
  @date   2002-12-06
  @ingroup libcapi
*/

/**
   @defgroup libcapi rmlibcw
   For portability purposes, all the OS-dependent functions. You will find specific 
   documentation for each kind of functions.
*/

#ifndef __RMLIBCW_H__
#define __RMLIBCW_H__

#include "rmdef/rmdef.h"

// we do implement RMDBGLOG_implementation as a function at this level
#undef RMDBGLOG_implementation

#include "rmnonascii.h"

#ifndef WITHOUT_THREADS
#include "rmsemaphores.h"
#include "rmcriticalsections.h"
#include "rmtimeoutsemaphore.h"
#include "rmthreads.h"
#endif // WITHOUT_THREADS

#include "rmrandom.h"
#include "rmtime.h"
#include "rmsprintf.h"
#include "rmfile.h"
#include "rmenv.h"
#include "rmsocket.h"
#include "rmpacketcommandioctl.h"
#include "rmdynamicloader.h"
#include "rmstrcmp.h"
#include "rmstrstr.h"
#include "rmrecordfile.h"
#include "rmfilecache.h"

#endif // __RMLIBCW_H__

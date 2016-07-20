/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmcore.h
  @brief  

  The following code only does basic pointer arithmetics,
  does not link to any libc call.

  Nevertheless, when used in a multithreaded environment, some
  require at initialization an array of callbacks to critical
  sections primitives. If this array is NULL the code will work
  properly, but is not thread-safe.

  @author Emmanuel Michon
  @date   2002-11-04
  @ingroup rmcoreapi
*/

/**
  @defgroup rmcoreapi rmcore
  @brief This API abstracts some core types and operations.
*/

#ifndef __RMCORE_H__
#define __RMCORE_H__

#include "rmdef/rmdef.h"

#include "rmascii.h"

#include "rmcorelist.h"
#include "rmcorequeue.h"
#include "rmcorepool.h"

#include "rmgrep.h"
#include "rmstatustostring.h"
#include "rmwrrd.h"

/* unlike the previous ones, it does not make sense to use the following without giving
   appropriate ops:
*/
#include "rmlist.h"
#include "rmqueue.h"
#include "rmtimeoutqueue.h"
#include "rmpool.h"

#include "rmparser.h"
#include "rmfifo.h"
 
#endif // __RMCORE_H__

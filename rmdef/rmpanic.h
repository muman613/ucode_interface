/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmpanic.h
  @brief  

  USERS SUMMARY
  -------------
  Some errors cannot be recovered; it's useless to propagate them thru
  the stack of calling functions. Instead, user should use: RMPanic()
  with the apppropriate status, causing the application:

  - to break in a debugger, (rmdef.h level behavior)
  - exit immediately, (all the threads should exit as well)
  - call longjmp() if a mechanism of setjmp/longjmp exists on the platform

  LIBRARY IMPLEMENTATION DETAILS
  ------------------------------
  Depending on the available functions, implementation of RMPanic()
  can be more or less complex. 

  At rmdef.h level, implementation forces an int 3
  which should drop the user to a debugger.

  @author Emmanuel Michon
  @date   2002-11-05
*/

#ifndef __RMPANIC_H__
#define __RMPANIC_H__

RM_EXTERN_C_BLOCKSTART

#ifdef _DEBUG

// this is not the default, but RMPANIC_GOON is useful when trap interrupt freezes (code in kernel mode)
#ifdef RMPANIC_GOON
#define RMPanic(error)					\
do {							\
        RMDBGLOG((ENABLE,"RMPanic on RMstatus %d\n",error)); \
} while (0)
#else
#define RMPanic(error)					\
do {							\
        RMDBGLOG((ENABLE,"RMPanic on RMstatus %d\n",error)); \
	STACKREVIEW; \
} while (0)
#endif // RMPANIC_GOON

#else

#define RMPanic(error) do {} while (0)

#endif // _DEBUG

RM_EXTERN_C_BLOCKEND

#endif // __RMPANIC_H__

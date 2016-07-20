/*****************************************
 Copyright � 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmthreads.h
  @brief  defines the API to manipulate threads.

  A thread is much like a process, but shares the memory with the
  caller of RMCreateThread.

  Father/Child terminology may be used, but:

  UNIX users: forget about the classic fork()/wait() functions, threads
  are handled by a specific library and specific system calls.

  @author Emmanuel Michon
  @date   2001-01-26
  @ingroup libcapi
*/

/*
  @page portability How to port CARIBBEAN to another system

   The target system must provide the following features: 
     - 32 bits processor;
     - operating system with user threads 
       (or processes with shared memory but more tricky)
     - a C++ (or embedded C++) compiler;
     
   A new system is composed of a new OS, and possibly a new compiler. This two characteristics are
   completely uncorrelated and  so are the corresponding porting processes.

   @subsection compilerPort Port to a new compiler

   Normally each compiler defines a macro that identifies itself (for instance __GNUC__). 
   This macro then can be used to write
   compiler dependent code. In CARIBBEAN the only part which is compiler dependent is the declaration of some
   common types. This is the case for the 64 bits long integer which is defined as a long long with gcc
   and __int64 under visual C. So you will have to find the way your compiler is defining such types and
   include the good declaration in the file basictypes.h.

   @subsection osPort Port to a new OS

   To port to a new OS, the only thing to do is to write the OS dependent part of the Library.
   You create a new directory with the name of your OS, and you rewrite all OS dependent modules. 

   Some concepts such as: events, critical sections can suffer subtle difference when switching platform
   because there is no real algorithmic definition of them. Details about what we call a 
   ``critical section'' in CARIBBEAN can be found in include/canonical/rmcriticalsections.h 
   (for instance, it has to enable recursion).

   Implementation for a new OS of rmevents.c should begin like this:

   @code
   include "caribbean_plainc.h"

   include <stdlib.h>
   include <semaphore.h>
   include <errno.h>
   
   begin coding...
   @endcode

   All library functions have to be extremely robust and thread-safe.

   They cannot fail.
   When a call to a library function fails, it is considered non-recoverable: you have to
   test the return value of your target OS system calls and run RMPanic(RM_ERRORTHEAPPROPRIATEERROR)
   that triggers an unconditional and immediate exit.

   The library is is only part that can be os dependent, so when it is done, everything should work fine.
   In order to be sure that the library works fine there is a stresstest program that checks that the 
   library has the good behaviour. The stresstest is not OS dependent excepted the time test which is
   not included in the main stresstest. If you want to test your time library you will have to rewrite it
   to fit your needs.

   @subsection linking Linking issues

   Operating systems provide three kinds of final linking:
   -# static linking, where all generated objects are gathered in a large binary executable (Montserrat works this way)
   -# dynamic linking at beginning of execution (also known as: implicit dynamic linking,
   static load-time dynamic linking), where you get at the end of the compilation 
   process one small executable (.exe (Windows)) and dynamically loadable libraries (.dll (Windows) 
   or .so (Linux)) for each logical unit. Linking is completed implicitely just before execution 
   begins you cannot open a dll after the program has begun to run (Barbados works this way).
   -# dynamic loader (also known as: explicit dynamic linking, or run-time dynamic linking), 
   where you can decide during the program execution to open a dll, get pointers
   to symbols by calling them explicitely by their name (GetProcAddress (Windows), dlsym (Linux)), and
   jump to new functions.

   Easiest way to go is 3rd kind if your operating system allows it, since you will only have to rewrite 
   rmdynamicloader.c.

   @subsection managingCompilation Managing compilation, Makefiles, and standard include paths

   Whatever operating system you use, you must have some kind of batch processing technique to automate
   the compilation process (an integrated development environment with projects and workspaces or make).

   Compiler options: excepted the library that calls and links with operating system libc functions, for
   all the remaining files, you should discard the standard include paths to avoid unwanted .h 
   (include <stdio.h> must fail). Be careful about appropriate options concerning:
   - optimization level,
   - debug hooks in object files,
   - multithreading,
   - be aware of any structure member alignment (to avoid surprises when dumping memory in a debugger)

   The easiest way to go is, if the directory structure is like this:
   
   @code
   X---Y
     |-Z
   @endcode

   Compile .c files in Y and output .o files in Y. Gather the .o files in Y in a larger binary object
   archive Y.o in the Y directory (unlike what Visual C++ does).

   Do the same for Z.

   X must have a rule to compile X/\*.c and gather this with Y/Y.o and Z/Z.o to output X/X.o.
   
   [Of course, in $CARIBBEAN_DIR/Library, compiling your operating system's library is enough.]

   Make it recursive until production of a binary or dll. Final dll have to be copied to $CARIBBEAN_DIR/lib.

   Having also a recursive cleaning rule is handy.

   Hint: do not call your makefiles simply Makefile. On WizzOS, call them Makefile.WizzOS
*/

#ifndef __RMTHREADS_H__
#define __RMTHREADS_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/** If the program is run as root, threads will be spawned in round robin mode (set to any value) */
#define CARIBBEAN_ENV_SCHED_RR "CARIBBEAN_ENV_SCHED_RR"

/** type used to manipulate threads */
typedef struct _RMthread *RMthread;

/** basic function pointer */
typedef void * (*RMfunc)(void * pData);

/**
   Creates a new thread that inherit's caller's scheduling parameters (scheduling policy and priority).

   This call is usually asynchronous; don't rely on the new thread being
   up and running when this call returns.

   @param name  
   @param StartAddress  
   @param Parameter     
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMthread RMCreateThread(const RMascii *name,
						 RMfunc StartAddress,
						 void * Parameter);


/**
   Creates a new thread with specific scheduling parameters (scheduling policy and priority).

   This call is usually asynchronous; don't rely on the new thread being
   up and running when this call returns.

   @param name  
   @param StartAddress  
   @param Parameter     
   @param realTime If TRUE, the thread will use real time SCHED_RR scheduling policy,
   	   	  otherwise it will use SCHED_OTHER scheduling policy.
   @param priorityDelta priority boost/handicap. For real time threads, it is a value between -50 (least priority)
   	   	  and +49 (most priority), otherwise a -20 (least priority) to +19 (most priority) value.
   	   	  In all cases, the value is relative to the default (medium) priority.
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMthread RMCreateThreadWithPriority(const RMascii *name,
							     RMfunc StartAddress,
							     void * Parameter,
							     RMbool realTime,
							     int priorityDelta);

/**
   @return The calling thread's name. Should not be freed.
*/
RM_LIBRARY_IMPORT_EXPORT const RMascii *RMGetCurrentThreadName(void);


/**

   @param void  
   @return the current thread pointer.
*/
RM_LIBRARY_IMPORT_EXPORT RMthread RMGetCurrentThread(void);


/**
   Suspends the execution of the calling thread
   until hThread terminates.
   This function CAN be called on a dead thread. (that is,
   a thread which already return'ed)

   @param hThread       
*/
RM_LIBRARY_IMPORT_EXPORT void RMWaitForThreadToFinish(RMthread hThread);

/**
   Cancels (Stops) the execution of thread hThread.

   Unix:
	By default threads can only be stopped at a cancellation point.

	Unless the specified thread was implicitely declared as asynchronously
	cancellable, execution will not stop right away you have to reach a
	cancellation point. Cancellation points include calls to sleep, printf,
	read, etc ...

	Some very specific calls, such as NFS reads cannot be stopped until they
	return. In general any thread in D state (deep sleep, cannot be
	interrupted). Won't exit as long as the I/O they wish to perform is not
	complete.

	See bug #31960

   Windows:
	Not implemented

   @param hThread
*/
RM_LIBRARY_IMPORT_EXPORT RMint32 RMCancelThread(RMthread hThread);


/**
   Check hThread for completion (non blocking)

   Will return 0 is hThread has completed execution.
   -1 in case of an error
   Any other value otherwise.

   This function CAN be called on a dead thread. (that is,
   a thread which already return'ed)

   @param hThread
*/
RM_LIBRARY_IMPORT_EXPORT RMint32 RMGetThreadCompletion(RMthread hThread);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMTHREADS_H__

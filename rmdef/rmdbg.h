/*****************************************
 Copyright © 2001-2003
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmdbg.h
  @brief

  USERS SUMMARY
  -------------
  The global switch ``-D_DEBUG=1'' is the official toggle between
  debug and release mode (this fits the default behavior of
  VisualC++).

  When compiling without _DEBUG, all debugging output disappears.

  When compiling with _DEBUG, the file rmdef_project/test/main.c shows
  how the debug facilities RMDBGLOG and RMDBGPRINT are supposed to be
  used.

  Toggle the `\#if 1' to `\#if 0' at top of file allows the user to
  quickly enable or disable all the debugging messages within a .c file.

  If a message is very important, the logic is to not use
  RMDBGLOG((MYMODULEDBG,...)) but rather: RMDBGLOG((ENABLE,...)) so that it
  always appears in debug mode.

  Note1: when using RMDBGLOG the message should be \n terminated.

  Note2: since RMDBGLOG outputs file name and line number, it is not suitable to
  output an array. This is the purpose of RMDBGPRINT (see rmdef_project/test/main.c)

  LIBRARY IMPLEMENTATION DETAILS
  ------------------------------
  The debug facility supposes some access to a `printf' like
  function, and some available output stream. The file name may also
  have UNICODE characters.

  Such features are not available at rmdef.h level. So, in the
  proposed implementation:

  - (default) the user is supposed to implement the two functions
  RMDBGLOG_implementation and and RMDBGPRINT_implementation according to
  the prototypes below. A sample implementation can be found in
  rmdef_project/test/dbgimplementation.c

  - if the project is compiled with global switch ``DISCARDDBG=1'', these functions are
  replaced by empty macros (and thus completely discarded), even in debug mode.

  - RMNOTIFY is NOT discarded, ever. It is always present.

  @author Emmanuel Michon
  @date   2002-11-05
*/

#ifndef __RMDBG_H__
#define __RMDBG_H__

/* This debug level enum can be used by libraries to set the level of verbosity, 0..5, e.g. at runtime */
enum RMdebuglevel {         // Verbosity meaning:              | Message meaning and default occurence:
	RMdebuglevel_none = 0,  //   No debug output               |   Always printed
	RMdebuglevel_error,     //   Only error messages           |   Error message, printed in release mode
	RMdebuglevel_warning,   //   Also warning messages         |   Warning message, not printed in release mode
	RMdebuglevel_info,      //   Also informational messages   |   Informational message, printed in debug mode
	RMdebuglevel_verbose,   //   Even more verbose             |   Additional info, printed in debug mode
	RMdebuglevel_all        //   Every information available   |   High frequency messages and explicit info, not printed in debug mode
};

RM_EXTERN_C_BLOCKSTART

#define ENABLE_IF(x) x, __FILE__, __LINE__
#define ENABLE TRUE, __FILE__, __LINE__
#define DISABLE FALSE, __FILE__, __LINE__

/* Per conclusion (11/16/2007 rmdef review) bug #8566 */
#define RMENABLE TRUE, __FILE__, __LINE__
#define RMDISABLE FALSE, __FILE__, __LINE__
#define RMDBGLEVEL(cookie, threshold, level) cookie, threshold, RMdebuglevel_ ## level, __FILE__, __LINE__

void RMDBGLOG_implementation(RMbool active, const RMascii *filename, RMint32 line, const RMascii *text,...);
void RMDBGPRINT_implementation(RMbool active, const RMascii *filename, RMint32 line, const RMascii *text,...);
void RMNOTIFY_implementation(void *cookie, RMstatus status, const RMascii *filename, RMint32 line, const RMascii *text,...);
void RMPRINT_implementation(void *cookie, enum RMdebuglevel threshold, enum RMdebuglevel level, const RMascii *filename, RMint32 line, const RMascii *text,...);
int open_log_files(const RMascii* szNormalFile, const RMascii* szErrorFile);
void close_log_files();

/*
******************************
  RMNOTIFY and RMPRINT are *ALWAYS* present
  ******************************
*/
#define RMPRINT(x) RMPRINT_implementation x

#if (RMCOMPILERID==RMCOMPILERID_VISUALC)

// variadic macros do not exist with Visual
#define RMNOTIFY(x) RMNOTIFY_implementation x

#else

#define RMNOTIFY(x) RMNOTIFY_implementation_ x

#define RMNOTIFY_implementation_(cookie, statusCode, text...)		\
	do { RMNOTIFY_implementation(cookie, statusCode, __FILE__, __LINE__, text); } while (0)

#endif




#ifdef _DEBUG

#undef NDEBUG

#if (RMCOMPILERID==RMCOMPILERID_VISUALC)

// variadic macros do not exist with Visual
#define RMDBGLOG(x) RMDBGLOG_implementation x
#define RMDBGPRINT(x) RMDBGPRINT_implementation x

#else

#define RMDBGLOG(x) RMDBGLOG_implementation_ x
#define RMDBGPRINT(x) RMDBGPRINT_implementation_ x

#define RMDBGLOG_implementation_(active, filename, line, text...) \
        do { if (active) RMDBGLOG_implementation(active, filename, line, text); } while (0)
#define RMDBGPRINT_implementation_(active, filename, line, text...) \
        do { if (active) RMDBGPRINT_implementation(active, filename, line, text); } while (0)

#endif

#else

#define NDEBUG 1

#define RMDBGLOG(x) do {} while (0)
#define RMDBGPRINT(x) do {} while (0)
#endif // _DEBUG

///
/**
   Tests if the argument is not zero.
   If it's zero prints a message telling what expression failed.
*/
#define RMASSERT(x) 						\
do {								\
	if (!(x)) 						\
		RMDBGLOG((ENABLE, "ASSERT: %s fails\n", # x));	\
} while (0)

#ifdef DISCARDDBG

#if (RMCOMPILERID==RMCOMPILERID_VISUALC)
// variadic macros do not exist with Visual
#define RMDBGLOG_implementation(x) do {} while (0)
#define RMDBGPRINT_implementation(x) do {} while (0)
#else
#define RMDBGLOG_implementation(x...) do {} while (0)
#define RMDBGPRINT_implementation(x...) do {} while (0)
#endif

#endif // DISCARDDBG

RM_EXTERN_C_BLOCKEND

#endif // __RMDBG_H__


#ifndef	__TEST_INTERFACE_H__
#define __TEST_INTERFACE_H__

#ifdef ENABLE_THREADS
    #include <pthread.h>
#endif // ENABLE_THREADS


/**
 *  Context structure used to pass to all top level functions.
 */

typedef struct _ifcontext {
    /* User supplied options */
	struct llad*	pllad;
	struct gbus*	pgbus;
	RMuint32        address;
	RMuint32        length;
	RMuint32        quantum;
	const char*     szReadToFilename;
	const char*     szWriteFromFilename;
	RMuint8*        buffer;
} CONTEXT;


#endif // __TEST_INTERFACE_H__

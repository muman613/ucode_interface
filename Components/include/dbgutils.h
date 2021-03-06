#ifndef	__DBGUTILS_H__
#define	__DBGUTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef	_WIN32
	#include <windows.h>
	#define vsnprintf _vsnprintf
#endif

//#undef _DEBUG

////////////////////////////////////////////////////////////////////////////////
//	If _DEBUG is defined then debugging commands are enabled.
//
//	DEBUG_LEVEL can be set to 1, 2, or 3. Each level enables another Dx macro.
//
////////////////////////////////////////////////////////////////////////////////


#ifdef _DEBUG

#define UNUSED(x) (x)
#define D(x) (x)

#if (DEBUG_LEVEL == 1)
#define D1(x) (x)
#define D2(x) /* (x) */
#define D3(x) /* (x) */
#elif (DEBUG_LEVEL == 2)
#define D1(x) (x)
#define D2(x) (x)
#define D3(x) /* (x) */
#elif (DEBUG_LEVEL == 3)
#define D1(x) (x)
#define D2(x) (x)
#define D3(x) (x)
#else
#define D1(x) /* (x) */
#define D2(x) /* (x) */
#define D3(x) /* (x) */
#endif

extern void debug(const char* sFmt, ...);

#define BREAKPOINT	__asm__("int $3")

#else	// _DEBUG

#define D(x) /* (x) */
#define D1(x) /* (x) */
#define D2(x) /* (x) */
#define D3(x) /* (x) */
#define UNUSED(x) /* (x) */

inline void debug(const char* /* sFmt */, ...) {

#define BREAKPOINT

}

#endif	// _DEBUG

#endif	// __DBGUTILS_H__

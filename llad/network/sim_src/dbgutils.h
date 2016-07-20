#ifndef	__DBGUTILS_H__
#define	__DBGUTILS_H__

#ifdef	_WIN32
	#include <windows.h>
#else
	#include <stdarg.h>
#endif

inline static void debug(char* sFmt, ...);

#ifdef	_DEBUG

inline static void debug(char* sFmt, ...) {
	static char	dbgBuffer[256];
	va_list		valist;
	va_start(valist,sFmt);
#ifdef	_WIN32
	_vsnprintf(dbgBuffer, 256, sFmt, valist);
	OutputDebugStringA(dbgBuffer);
#else	// _WIN32
	vsnprintf(dbgBuffer, 256, sFmt, valist);
	fprintf(stderr, dbgBuffer);
#endif	// _WIN32
}

#else

inline static void debug(char* sFmt, ...) {
}

#endif

#endif	// __DBGUTILS_H__

#ifndef	__LIBPLATFORMDB_H__
#define __LIBPLATFORMDB_H__

#ifdef _WIN32
#include <windows.h>
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif

#include "PlatformTypes.h"

#include "PlatformDatabase.h"
#include "PlatformChip.h"
#include "PlatformBlock.h"
#include "PlatformEngine.h"

#ifdef	_WIN32
#pragma warning( pop )
#endif

#ifdef	_DEBUG
#define D(x)  (x)
#ifdef _WIN32
inline void debug(const char* sFmt, ...) {
	static char dbgBuffer[256];
	va_list vargs;
	va_start(sFmt, vargs);
	vsnprintf(dbgBuffer, 256, sFmt, vargs);
	OutputDebugStringA(dbgBuffer);
	va_end(vargs);
}
#else
extern void debug(const char*, ...);
#endif
#else	// _DEBUG
#define D(x) /* x */
#endif	// _DEBUG

#endif // __LIBPLATFORMDB_H__

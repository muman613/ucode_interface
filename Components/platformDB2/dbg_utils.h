#ifndef __PLATFORM_DBG_UTILS__
#define __PLATFORM_DBG_UTILS__

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

#endif // __PLATFORM_DBG_UTILS__


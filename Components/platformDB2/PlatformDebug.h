#ifndef __PLATFORMDEBUG_H__
#define __PLATFORMDEBUG_H__

#ifdef _WIN32
#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )
#else
#define DllImport
#define DllExport
#endif // _WIN32_C_LIB

#ifdef  _DEBUG
#define D(x) (x)
#ifdef _WIN32
inline void debug(const char* sFmt, ...) {
//  static char buffer[512];
    va_list args;
    va_start(args, sFmt);
//    vsnprintf(buffer, 512, sFmt, args);
//    OutputDebugString(buffer);
    vfprintf(stderr, sFmt, args);
    va_end(args);
}
#else
extern void debug(const char* sFmt, ...);
#endif // _WIN32
#else
#define D(x) /* x */
#endif // _DEBUG

#endif // __PLATFORMDEBUG_H__


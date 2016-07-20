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

#else	// _ENABLE_DEBUG

#define D(x) /* (x) */
#define D1(x) /* (x) */
#define D2(x) /* (x) */
#define D3(x) /* (x) */
#define UNUSED(x) /* (x) */

inline void debug(const char* /* sFmt */, ...) {

}

#endif	// _ENABLE_DEBUG


class dbgMgr {
public:
    dbgMgr(bool bLog);
    virtual ~dbgMgr();

#ifdef  _DEBUG
    void        enable_dbg_out();
    void        disable_dbg_out();
    void        toggle_dbg_out();
#endif
};

#endif	// __DBGUTILS_H__

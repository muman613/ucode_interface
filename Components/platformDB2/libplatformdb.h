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

/* Version information */

#define LIBPLATFORMDB_MAJOR_VERSION         2       ///< Library major version #.
#define LIBPLATFORMDB_MINOR_VERSION         0       ///< Library minor version #.

#endif // __LIBPLATFORMDB_H__

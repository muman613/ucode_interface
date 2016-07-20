#ifndef	__UTILS_H__
#define __UTILS_H__

#include <time.h>

int 		parse_numeric(const char* str, RMuint32 *pValue);
int 		load_buffer_from_file(const char* szFilename, RMuint8** pBuffer,
                                  RMuint32* pLength);
int 		allocate_buffer(RMuint8** pBuffer, RMuint32 len);

#endif


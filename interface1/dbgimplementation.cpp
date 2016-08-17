/*****************************************
 Copyright (c) 2001-2010
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
	@file dbgimplementation.c
	@brief User mode test application, debugging print implementation.
*/

#ifndef ALLOW_OS_CODE
#define ALLOW_OS_CODE
#endif

#include <stdio.h>
#include <stdarg.h>
#include "rmdef/rmdef.h"
#include "rmdef/rmbtypes.h"

#define ENABLE_TIMESTAMPS 1

#ifdef _DEBUG
int verbose_stdout = 1;
int verbose_stderr = 1;
#else
int verbose_stdout = 0;
int verbose_stderr = 0;
#endif

//#define NORMALMSG stdout
//#define ERRORMSG  stderr

FILE* NORMALMSG = 0;
FILE* ERRORMSG  = 0;

int console_output(const char *format, ...);
int file_output(FILE *fptr, const char *format, ...);
int DebugLevel = 1;

int open_log_files(const RMascii* szNormalFile, const RMascii* szErrorFile)
{
    if (NORMALMSG != 0L)
        fclose(NORMALMSG);
    if (ERRORMSG != 0L)
        fclose(ERRORMSG);

    NORMALMSG = fopen(szNormalFile, "w");
    ERRORMSG = fopen(szErrorFile, "w");

    return ((NORMALMSG != 0L) && (ERRORMSG != 0L))?1:0;
}

void close_log_files()
{
    if (NORMALMSG != 0L)
        fclose(NORMALMSG);
    if (ERRORMSG != 0L)
        fclose(ERRORMSG);
}

int console_output(const char *format, ...)
{
	va_list ap;
	int res;

	if (verbose_stdout != 0) {
		va_start(ap, format);
		res = vprintf(format, ap);
		va_end(ap);
		return(res);
	}
	return(0);
}

int file_output(FILE *fptr, const char *format, ...)
{
	va_list ap;
	int res;

	if (
		((fptr != stderr) && (verbose_stdout != 0)) ||
		((fptr == stderr) && (verbose_stderr != 0))
	) {
		va_start(ap, format);
		res = vfprintf(fptr, format, ap);
		va_end(ap);
		return(res);
	}
	return(0);
}


#include "rmdef/rmdef.h"
#include "rmcore/include/rmcore.h"
#include "rmlibcw/include/rmlibcw.h"

static inline void print_timestamp(FILE *stream)
{
#if ENABLE_TIMESTAMPS
	RMuint32 time_ms = (RMuint32) (RMGetTimeInMicroSeconds()/ (RMuint64)1000);
	RMuint32 h, m, s, ms;
	h = time_ms / (1000*3600);
	m = time_ms / (1000*60) - 60*h;
	s = time_ms / 1000 - 60*m - 3600*h;
	ms = time_ms - 1000*s- (60*1000)*m - (3600*1000)*h;
	fprintf(stream, "%02lu:%02lu:%02lu.%03lu ", (unsigned long)h, (unsigned long)m, (unsigned long)s, (unsigned long)ms);
	fflush(stream);
#endif
	return;
}

#define RMDBG_MAX_STRING 1024

static char str[RMDBG_MAX_STRING];

#if ((RMCOMPILERID==RMCOMPILERID_GCC) || (RMCOMPILERID==RMCOMPILERID_ARMELF_GCC) || (RMCOMPILERID==RMCOMPILERID_MIPSEL_GCC))

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef RMDBGLOG_implementation
void RMDBGLOG_implementation(RMbool active,const RMascii *filename,RMint32 line,const RMascii *text,...)
{
	if (active && (verbose_stderr != 0)) {
		va_list ap;

		snprintf((char *)str,RMDBG_MAX_STRING,"[%s:%ld] ", (char *)filename, (unsigned long)line);

		va_start(ap, text);
		vsnprintf((char *)(str+strlen(str)), RMDBG_MAX_STRING-strlen(str), text, ap);
		va_end(ap);

		print_timestamp(NORMALMSG);
		fprintf(NORMALMSG,"%s", str);
		fflush(NORMALMSG);
	}
}
#endif // RMDBGLOG_implementation

#ifndef RMDBGPRINT_implementation
void RMDBGPRINT_implementation(RMbool active,const RMascii *filename,RMint32 line,const RMascii *text,...)
{
	if (active && (verbose_stderr != 0)) {
		va_list ap;

		va_start(ap, text);
		vfprintf(NORMALMSG, text, ap);
		va_end(ap);
		fflush(NORMALMSG);
	}
}
#endif // RMDBGPRINT_implementation

#ifndef RMPRINT_implementation
void RMPRINT_implementation(void *cookie, enum RMdebuglevel threshold, enum RMdebuglevel level, const RMascii *filename, RMint32 line, const RMascii *text,...)
{
	if (level <= threshold) {
		va_list ap;

		va_start(ap, text);
		vsnprintf((char *)str, RMDBG_MAX_STRING, text, ap);
		va_end(ap);

		fprintf(NORMALMSG, "%s", str);
		fflush(NORMALMSG);
	}
}
#endif // RMPRINT_implementation

#ifdef RMNOTIFY_WITHOUT_COLORS

const char SET_ERROR[] = "";
const char SET_INFO[]  = "";
const char SET_STD[]   = "";

#else //RMNOTIFY_WITHOUT_COLORS

const char SET_ERROR[] = "\033[31;1m";  // bold / red
const char SET_INFO[]  = "\033[32;1m";  // bold / green
const char SET_STD[]   = "\033[0m";     // clear attributes

#endif

#ifndef RMNOTIFY_implementation
void RMNOTIFY_implementation(void *cookie, RMstatus status, const RMascii *filename, RMint32 line, const RMascii *text,...)
{
	va_list ap;

	if (RMFAILED(status)) {
		snprintf((char *)str, RMDBG_MAX_STRING, "%s[%s:%ld] ERROR(%s): ", SET_ERROR, (char *)filename, (unsigned long)line, RMstatusToString(status));
	} else {
		snprintf((char *)str, RMDBG_MAX_STRING, "[%s:%ld] ", (char *)filename, (unsigned long)line);
	}

	va_start(ap, text);
	vsnprintf((char *)str+strlen(str), RMDBG_MAX_STRING, text, ap);
	va_end(ap);

	snprintf((char *)str+strlen(str), RMDBG_MAX_STRING, "%s", SET_STD);

	print_timestamp(ERRORMSG);
	fprintf(ERRORMSG, "%s", str);
	fflush(ERRORMSG);
}
#endif // RMNOTIFY_implementation


#elif (RMCOMPILERID==RMCOMPILERID_VISUALC)

#include <windows.h>
#include <stdio.h>

#ifndef RMDBGLOG_implementation
void RMDBGLOG_implementation(RMbool active,const RMascii *filename,RMint32 line,const RMascii *text,...)
{
	if (active && (verbose_stdout != 0)) {
		va_list ap;

#ifdef UNICODE
		sprintf((char *)str, (char *)"[%ls:%ld] ", filename, line);
#else
		sprintf((char *)str, (char *)"[%s:%ld] ", filename, line);
#endif

		va_start(ap, text);
		vsprintf((char *)(str+strlen(str)), (const char *)text, ap);
		va_end(ap);

		OutputDebugString(str);
	}
}
#endif // RMDBGLOG_implementation

#ifndef RMDBGPRINT_implementation
void RMDBGPRINT_implementation(RMbool active,const RMascii *filename,RMint32 line,const RMascii *text,...)
{
	if (active && (verbose_stdout != 0)) {
		va_list ap;

		va_start(ap, text);
		vsprintf((char *)str, (const char *)text, ap);
		va_end(ap);

		OutputDebugString(str);
	}
}
#endif // RMDBGPRINT_implementation

#ifndef RMPRINT_implementation
void RMPRINT_implementation(void *cookie, enum RMdebuglevel threshold, enum RMdebuglevel level, const RMascii *filename, RMint32 line, const RMascii *text,...)
{
	if (level <= threshold) {
		va_list ap;

		va_start(ap, text);
		vsprintf((char *)str, (const char *)text, ap);
		va_end(ap);

		OutputDebugString(str);
	}
}
#endif // RMPRINT_implementation

#ifndef RMNOTIFY_implementation
void RMNOTIFY_implementation(void *cookie, RMstatus status, const RMascii *filename, RMint32 line, const RMascii *text,...)
{
	va_list ap;

	if (RMFAILED(status)) {
		sprintf((char *)str, (char *)"[%s:%ld] ERROR (%s) : ", filename, line, RMstatusToString(status));
	} else {
		sprintf((char *)str, (char *)"[%s:%ld] ", filename, line);
	}

	va_start(ap, text);
	vsprintf((char *)str+strlen(str), (const char *)text, ap);
	va_end(ap);

	OutputDebugString(str);
}
#endif // RMNOTIFY_implementation

#else

NOTCOMPILABLE

#endif

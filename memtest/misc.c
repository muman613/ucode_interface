#define ALLOW_OS_CODE
#include "include/rmlibcw.h"

#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include "rmcore/include/rmcore.h"

static RMascii *errorArray [] = {
#undef RM_DEFINE_ERROR
#define RM_DEFINE_ERROR(x,v) "RM_" # x,
#include "rmdef/rmstatus.inc"
#undef RM_DEFINE_ERROR
};

const RMascii *RMstatusToString (RMstatus error)
{
	RMuint32 index = (RMuint32)error;


	if ((index <= (RMuint32)RM_ERROR_FIRST__) ||
	    (index >= (RMuint32)RM_ERROR_LAST__)) {
		RMDBGLOG((ENABLE, "\nError code %lu out of range!\n", index));
		return errorArray[RM_ERROR-RM_ERROR_FIRST__-1];
	}

	return errorArray[index-RM_ERROR_FIRST__-1];
}

RMuint64 RMGetTimeInMicroSeconds()
{
	RMuint64 t;
	static RMbool firstTimeHere=TRUE;
	static struct timeb timeOrigine;
	struct timeb now;

	if(firstTimeHere)
	{
		ftime( &timeOrigine );
		firstTimeHere = FALSE;
	}

	ftime( &now );
   
	t = (RMuint64)( 
					((RMuint64)now.time - (RMuint64)timeOrigine.time) * 1000000L + 
					((RMuint64)now.millitm - (RMuint64)timeOrigine.millitm)* 1000 
					);

	return t;
}

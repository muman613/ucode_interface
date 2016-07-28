#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "targetEngine.h"

#ifdef _DEBUG
void debug(const char* sFmt, ...) {
	va_list vargs;
	va_start(vargs, sFmt);

	vfprintf(stderr, sFmt, vargs);

	va_end(vargs);
}
#endif // _DEBUG


int main(int argc, char * argv[])
{
    targetEngine*       pTarget = 0L;

    pTarget = new targetEngine("8758", "Video");

    delete pTarget;

    return 0;
}

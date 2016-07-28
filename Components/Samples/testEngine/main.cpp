#include <iostream>
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

/**
 *  Main entry point
 */

int main(int argc, char * argv[])
{
    TARGET_ENGINE_PTR   pTarget;

#ifdef _DEBUG
    open_log_files("messages.txt", "errors.txt");
#endif // _DEBUG

    pTarget = std::make_shared<targetEngine>("8758", "Video");

    if (pTarget && pTarget->is_valid()) {

        std::cout << "Target is opened!" << std::endl;

        if (pTarget->connect()) {
            std::cout << "Target is connected!" << std::endl;
        }

        pTarget.reset();
    }

    return 0;
}

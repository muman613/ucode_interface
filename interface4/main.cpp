#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include "dbgutils.h"
#include "interfaceUI.h"

using namespace std;

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
    interfaceUI     ui;

    D(open_log_files("messages.txt", "errors.txt"));

    if (ui.open(argc, argv)) {
        ui.run();
        ui.close();
    } else {
        cerr << "ERROR: Unable to open interface..." << endl;
    }

    return 0;
}

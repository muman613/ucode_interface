#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include "dbgutils.h"
#include "interfaceUI.h"
#include "libOptions.h"

using namespace std;

#ifdef _DEBUG
void debug(const char* sFmt, ...) {
	va_list vargs;
	va_start(vargs, sFmt);

	vfprintf(stderr, sFmt, vargs);

	va_end(vargs);
}
#endif // _DEBUG

void helpFunc(const char* sCmd) {
    cout << sCmd << " --chip|-c chipid --stream|-s mediastream --decoder|-d codecid --yuv|-y yuvoutname --engine|-e 0|1 --mode|-m (d)ebug|(r)elease --remote|-r remotespec" << std::endl;

    return;
}

/**
 *  Main entry point
 */

int main(int argc, char * argv[])
{
    interfaceUI     ui;

    globalOptions.set_xml_path("../xml/");
    globalOptions.set_ucode_path("../");

    D(open_log_files("messages.txt", "errors.txt"));

    if (ui.open(argc, argv, helpFunc)) {
        ui.run();
        ui.close();
    } else {
        cerr << "ERROR: Unable to open interface..." << endl;
    }

    return 0;
}

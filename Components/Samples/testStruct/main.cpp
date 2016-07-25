#include <stdio.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include "structure_control.h"

using namespace std;

string  sHeaderName;

#ifdef _DEBUG

void debug(const char* sFmt, ...) {
    va_list list;

    va_start(list, sFmt);
    vfprintf( stderr, sFmt, list );
    va_end(list);
}

#endif // _DEBUG

int main(int argc, char* argv[])
{
    structure_database  structDB;

    if (argc != 2) {
        fprintf(stderr, "ERROR: Must specify header file!\n");
        return -1;
    }

    sHeaderName = argv[1];

    printf("Opening file %s...\n", sHeaderName.c_str());


    if (structDB.open(sHeaderName.c_str())) {
#ifdef  _ENABLE_DUMP
        structDB.dump("output/log.txt");
#endif
#ifdef	_ENABLE_HTML_OUTPUT
        structDB.dump_html_table("output/structures.html", sHeaderName.c_str());
#endif
#ifdef  _ENABLE_EXCEL
        structDB.dump_xls("output/structures.xls", "t");
#endif
    } else {
        fprintf(stderr, "ERROR: Unable to open header %s...\n", sHeaderName.c_str());
    }

    return 0;
}

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include "symbolmgr.h"

using namespace std;


STRING          sHeaderFilename;
Uint32          memBase = 0x100000;
STRING          sLookup;

int main(int argc, const char* argv[])
{
    int opt;
    UcodeSymbolMgr  mgr;

    printf("Welcome!\n");

    while ((opt = getopt(argc, (char * const *)argv, "l:b:s:")) != -1) {
        switch (opt) {
        case 'l':
            sHeaderFilename = optarg;
            break;
        case 'b':
            sscanf(optarg, "%x", &memBase);
            break;
        case 's':
            sLookup = optarg;
            break;
        }
    }

    if (!sHeaderFilename.empty()) {
        mgr.SetMemBase(memBase);

        if (mgr.LoadSymbols( sHeaderFilename )) {
            printf("Loaded %zu symbols!\n", mgr.size());
            if (sLookup.empty()) {
                mgr.DumpSymbols(stdout);
            } else {
                Uint32 address = mgr[sLookup];

                printf("Symbol %s Value 0x%08X\n", sLookup.c_str(), address);
            }
        }
    }

    return 0;
}

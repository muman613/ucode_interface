#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define ALLOW_OS_CODE
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

#include "gbusfifolib/gbus_fifo.h"

using namespace std;

int main()
{
    LLAD_PTR pLlad;
    GBUS_PTR pGbus;
    string   hostSpec;

    cout << "Hello world!" << endl;

    if (getenv("EM8XXX_SERVER") != 0L) {
        hostSpec = getenv("EM8XXX_SERVER");
    } else {
        fprintf(stderr, "EM8XXX_SERVER environment must be set first!\n");
        return -1;
    }

#if (__cplusplus >= 201103L)
    pLlad = std::make_shared<llad>(hostSpec);
#else
    pLlad = new llad(hostSpec);
#endif


    if (pLlad->is_valid()) {
        RMuint32 base, size, rd, wr;

        pGbus = std::make_shared<gbus>(pLlad);

        gbus_fifo_get_pointer(pGbus, (gbus_fifo *)0xbd3b8000, &base, &size, &rd, &wr);

        printf("FIFO Start @ %08lX\n", base);
        printf("FIFO Size @ %08lX\n", size);

        pGbus.reset();
    }

    pLlad.reset();

    return 0;
}

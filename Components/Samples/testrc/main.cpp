#define ALLOW_OS_CODE
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "llad.h"
#include "gbus.h"

enum OPER {
    OP_UNKNOWN,
    OP_READ,
    OP_WRITE,
};

enum QUANT {
    QUANT_UINT8,
    QUANT_UINT16,
    QUANT_UINT32,
};

struct appParms {
    OPER                oper;
    RMuint32            address;
    RMuint32            count;
    RMuint32            value;
    QUANT               quantum;
};


using namespace std;

#define HOST        "10.10.10.12:0"

void init_parms(appParms* parms)
{
    memset(parms, 0, sizeof(appParms));

    parms->oper     = OP_UNKNOWN;
    parms->count    = 1;
    parms->quantum  = QUANT_UINT32;

    return;
}

bool parse_arguments(int argc,  char* argv[], appParms* parms)
{
    bool bRes = false;
    int opt;

    assert( parms != 0L );

    while ((opt = getopt(argc, argv, "rwa:c:v:q:")) != -1) {
        switch (opt) {
        case 'r':
            if (parms->oper == OP_UNKNOWN) {
                parms->oper = OP_READ;
            } else {
                fprintf(stderr, "ERROR: Must specify read OR write but not both!\n");
                return false;
            }
            break;

        case 'w':
            if (parms->oper == OP_UNKNOWN) {
                parms->oper = OP_WRITE;
            } else {
                fprintf(stderr, "ERROR: Must specify read OR write but not both!\n");
                return false;
            }
            break;

        case 'a':
            sscanf(optarg, "0x%08X", &parms->address);
            break;

        case 'c':
            sscanf(optarg, "%d", &parms->count);
            break;

        case 'v':
            sscanf(optarg, "0x%08X", &parms->value);
            break;

        case 'q':
            if (strcmp(optarg, "8") == 0) {
                parms->quantum = QUANT_UINT8;
            } else if (strcmp(optarg, "16") == 0) {
                parms->quantum = QUANT_UINT16;
            } else if (strcmp(optarg, "32") == 0) {
                parms->quantum = QUANT_UINT32;
            } else {
                fprintf(stderr, "ERROR: Invalid quantum must be 8, 16, or 32!\n");
                return false;
            }
            break;

        default:
            break;
        }
    }

    if ((parms->oper == OP_READ) || (parms->oper == OP_WRITE)) {
        bRes = true;
    }

    return bRes;
}

void do_read(GBUS_PTR pGbus, appParms* pParms)
{
    RMuint32 address, count, value, incr = 0;
    const char* sFmt = 0L;

    assert((pGbus != 0) && (pParms != 0));

    address = pParms->address;
    count   = pParms->count;

    for (RMuint32 i = 0 ; i < count ; i++) {
        switch (pParms->quantum) {
        case QUANT_UINT8:
            value = pGbus->gbus_read_uint8( address );
            incr = 1;
            sFmt = "%02lX";
            break;

        case QUANT_UINT16:
            value = pGbus->gbus_read_uint16( address );
            incr = 2;
            sFmt = "%04lX";
            break;

        case QUANT_UINT32:
            value = pGbus->gbus_read_uint32( address );
            incr = 4;
            sFmt = "%08lX";
            break;
        }

        printf("%08X : ", address);
        printf(sFmt, value);
        printf("%s", "\n");

        address += incr;
    }

}

void do_write(GBUS_PTR pGbus, appParms* pParms)
{
    RMuint32 address, count, value, incr = 0;

    assert((pGbus != 0) && (pParms != 0));

    address = pParms->address;
    count   = pParms->count;
    value   = pParms->value;

    for (RMuint32 i = 0 ; i < count ; i++) {
        switch (pParms->quantum) {
        case QUANT_UINT8:
            pGbus->gbus_write_uint8( address, value );
            incr = 1;
            break;

        case QUANT_UINT16:
            pGbus->gbus_write_uint16( address, value );
            incr = 2;
            break;

        case QUANT_UINT32:
            pGbus->gbus_write_uint32( address, value );
            incr = 4;
            break;
        }

        address += incr;
    }
}

int main(int argc, char* argv[])
{
    appParms parms;
    LLAD_PTR pLlad;
    GBUS_PTR pGbus;
    string   hostSpec;

    cout << "Hello world!" << endl;

    init_parms(&parms);
    if (getenv("EM8XXX_SERVER") != 0L) {
        hostSpec = getenv("EM8XXX_SERVER");
    } else {
        fprintf(stderr, "EM8XXX_SERVER environment must be set first!\n");
        return -1;
    }

    if (!parse_arguments(argc, argv, &parms)) {
        fprintf(stderr, "Invalid parameters!\n");
        return -1;
    }
#if (__cplusplus >= 201103L)
    pLlad = std::make_shared<llad>(hostSpec);
#else
    pLlad = new llad(hostSpec);
#endif


    if (pLlad->is_valid()) {
#if (__cplusplus >= 201103L)
        pGbus = std::make_shared<gbus>(pLlad);
#else
        pGbus = new gbus(pLlad);
#endif

        if (pGbus->is_valid()) {
            cout << "Connected to " << HOST << std::endl;

            switch (parms.oper) {
            case OP_READ:
                do_read(pGbus, &parms);
                break;
            case OP_WRITE:
                do_write(pGbus, &parms);
                break;
            default:
                break;
            }


            pGbus->close();
        }

#if (__cplusplus >= 201103L)
        pGbus.reset();
#else
        delete pGbus;
#endif
        pLlad->close();
    }
#if (__cplusplus >= 201103L)
    pLlad.reset();
#else
    delete pLlad;
#endif

    return 0;
}

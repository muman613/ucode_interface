/**
	@file		test_interface.c
	@author		Michael A. Uman & Aurelia Popa Radu
	@date		May 16, 2013
	@date       June 30, 2016
	@copyright	(C) 2013-2016 Sigma Designs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <libgen.h>
#include <signal.h>
#include <time.h>
#ifdef ENABLE_THREADS
    #include <pthread.h>
#endif // ENABLE_THREADS

#define ALLOW_OS_CODE 1
//#define DUMP_BUFFERS 1

#include "llad/include/llad.h"
#include "llad/include/gbus.h"
#include "utils.h"
#include "memtest.h"


static void print_usage(const char* sAppName) {
//    struct profileEntry *pCurEntry = profileTable;
//    char *sAppCopy = strdup(sAppName);
//
//    fprintf(stderr, "Usage: %s [-b binfile] [-c binfile] [-s streamfile] [-p (codec profile)] [-o YUVFile.yuv]\n", basename(sAppCopy));
//    fprintf(stderr, "Supported codec profiles:\n");
//    free(sAppCopy);
//
//    while (pCurEntry->szIdent != NULL) {
//        fprintf(stderr, "    %s\n", pCurEntry->szIdent);
//        pCurEntry++;
//    }

    exit( 0 );
}

/**
 *  Parse commandline options.
 *  -a address
 *  -l length
 *  -w file to write data from
 *  -r file to read data to
 *  -q quantum (8,16,32)
 */

static RMstatus parse_options(CONTEXT* pCtx, const char* szAppName, int argc, char* argv[])
{
    int         opt;
    RMstatus    result = RM_ERROR;
    char*       opts = "a:l:w:r:q:";

    while ((opt = getopt(argc, argv, opts)) != -1)
    {
        switch (opt)
        {
        case 'a':
            parse_numeric(optarg, &pCtx->address);
            break;
        case 'l':
            parse_numeric(optarg, &pCtx->length);
            break;
        case 'r':
            pCtx->szReadToFilename = strdup(optarg);
            break;
        case 'w':
            pCtx->szWriteFromFilename = strdup(optarg);
            break;
        case 'q':
            parse_numeric(optarg, &pCtx->quantum);
            break;
        }
    }

exitParse:

    //printf("Sending file %s to address 0x%08lx\n", pCtx->szFilename, pCtx->address);

    if (pCtx->address != 0) {
        if ((pCtx->szReadToFilename == 0) && (pCtx->szWriteFromFilename == 0)) {
            fprintf(stderr, "ERROR: Must specify either -r (read) or -w (write) file!\n");
        } else if (!((pCtx->szReadToFilename != 0) && (pCtx->szWriteFromFilename != 0))) {
            RMuint32 q = pCtx->quantum;
            if ((q == 8) || (q == 16) || (q == 32)) {
                if ((pCtx->szReadToFilename != 0) && (pCtx->length == 0)) {
                    fprintf(stderr, "ERROR: Must specify length for read!\n");
                } else
                    result = RM_OK;
            } else {
                fprintf(stderr, "ERROR: quantum must be 8, 16, or 32!\n");
            }
        } else {
            fprintf(stderr, "ERROR: Cannot read & write at same time!\n");
        }
    } else {
        fprintf(stderr, "ERROR: Must specify the address to read or write!\n");
    }

    return result;
}

/**
 *  Open llad/gbus interface.
 */

static RMstatus open_gbus(CONTEXT* pCtx, int chipNum)
{
    char	chipspec[32];

	strcpy(chipspec, getenv("EM8XXX_SERVER"));

    if ((pCtx->pllad = llad_open(chipspec)) == 0)
    {
        fprintf(stderr, "ERROR: llad_open failed!\n");
        return RM_ERROR;
    }

    if ((pCtx->pgbus = gbus_open(pCtx->pllad)) == 0)
    {
        fprintf(stderr, "ERROR: gbus_open failed!\n");
        return RM_ERROR;
    }

    return RM_OK;
}

/**
 *  Close llad/gbus interface.
 */

static void close_gbus(CONTEXT* pCtx)
{
    if (pCtx->pgbus)
    {
        gbus_close(pCtx->pgbus);
        pCtx->pgbus = 0L;
    }

    if (pCtx->pllad)
    {
        llad_close(pCtx->pllad);
        pCtx->pllad = 0L;
    }
}

/**
 * Free string parameter memory.
 */

static void release_memory(CONTEXT* pCtx)
{
    if (pCtx->szReadToFilename != 0) {
        free((void*)pCtx->szReadToFilename);
        pCtx->szReadToFilename = 0L;
    }
    if (pCtx->szWriteFromFilename != 0) {
        free((void*)pCtx->szWriteFromFilename);
        pCtx->szWriteFromFilename = 0L;
    }
    if (pCtx->buffer != 0) {
        free((void*)pCtx->buffer);
        pCtx->buffer = 0L;
    }

    return;
}


static void display_context_info(CONTEXT* ctx)
{
	/* Display context user options */
    fflush(stdout);

    return;
}

/**
 *  Initialize application context structure...
 */

void init_context(CONTEXT* ctx) {
    memset(ctx, 0, sizeof(CONTEXT));	// clear the context

    ctx->quantum = 8; // default to using gbus_xxx_data8

    return;
}

static void write_buffer_to_file(CONTEXT* pCtx)
{
    FILE* fp = 0L;

    assert(pCtx->buffer != NULL);
    
    if ((fp = fopen(pCtx->szReadToFilename, "w")) != 0L) {
        fwrite(pCtx->buffer, 1, pCtx->length, fp);
        fclose(fp);
    }

    return;
}

static void do_read_to_file8(CONTEXT* pCtx)
{
    printf("READING %ld BYTES TO FILE %s FROM 0x%08lX USING GBUS_READ_DATA8\n",
           pCtx->length, pCtx->szReadToFilename, pCtx->address);

    gbus_read_data8(pCtx->pgbus, pCtx->address, pCtx->buffer, pCtx->length);
}

static void do_read_to_file16(CONTEXT* pCtx)
{
    printf("READING %ld BYTES TO FILE %s FROM 0x%08lX USING GBUS_READ_DATA16\n",
           pCtx->length, pCtx->szReadToFilename, pCtx->address);

    gbus_read_data16(pCtx->pgbus, pCtx->address, (RMuint16*)pCtx->buffer, pCtx->length >> 1);
}

static void do_read_to_file32(CONTEXT* pCtx)
{
    printf("READING %ld BYTES TO FILE %s FROM 0x%08lX USING GBUS_READ_DATA32\n",
           pCtx->length, pCtx->szReadToFilename, pCtx->address);

    gbus_read_data32(pCtx->pgbus, pCtx->address, (RMuint32*)pCtx->buffer, pCtx->length >> 2);
}

static void do_read_to_file(CONTEXT* pCtx)
{
    assert(pCtx != NULL);

    if (allocate_buffer(&pCtx->buffer, pCtx->length)) {
        switch (pCtx->quantum) {
        case 8:
            do_read_to_file8( pCtx );
            break;
        case 16:
            do_read_to_file16( pCtx );
            break;
        case 32:
            do_read_to_file32( pCtx );
            break;
        }

        write_buffer_to_file(pCtx);
    } else {
        fprintf(stderr, "ERROR: Unable to allocate buffer!\n");
    }
}

static void do_write_from_file8(CONTEXT* pCtx)
{
    printf("WRITING %ld BYTES FROM FILE %s TO 0x%08lX USING GBUS_WRITE_DATA8\n",
           pCtx->length, pCtx->szWriteFromFilename, pCtx->address);

    gbus_write_data8(pCtx->pgbus, pCtx->address, pCtx->buffer, pCtx->length);
}

static void do_write_from_file16(CONTEXT* pCtx)
{
    printf("WRITING %ld BYTES FROM FILE %s TO 0x%08lX USING GBUS_WRITE_DATA16\n",
           pCtx->length, pCtx->szWriteFromFilename, pCtx->address);

    gbus_write_data16(pCtx->pgbus, pCtx->address, (RMuint16*)pCtx->buffer, pCtx->length >> 1);
}

static void do_write_from_file32(CONTEXT* pCtx)
{
    printf("WRITING %ld BYTES FROM FILE %s TO 0x%08lX USING GBUS_WRITE_DATA32\n",
           pCtx->length, pCtx->szWriteFromFilename, pCtx->address);

    gbus_write_data32(pCtx->pgbus, pCtx->address, (RMuint32*)pCtx->buffer, pCtx->length >> 2);

}

static void do_write_from_file(CONTEXT* pCtx)
{
    assert(pCtx != NULL);

    if (load_buffer_from_file(pCtx->szWriteFromFilename,
                              &pCtx->buffer,
                              &pCtx->length))
    {
        switch (pCtx->quantum) {
        case 8:
            do_write_from_file8( pCtx );
            break;
        case 16:
            do_write_from_file16( pCtx );
            break;
        case 32:
            do_write_from_file32( pCtx );
            break;
        }
    } else {
        fprintf(stderr, "ERROR: Unable to load buffer!\n");
    }
}

/**
 *  Main entry point.
 */

int main(int argc, char *argv[])
{
    CONTEXT ctx;
    int chipnum = 0;

    memset(&ctx, 0, sizeof(CONTEXT));

    open_log_files("messages.txt", "errors.txt");

    init_context( &ctx );

    /* parse commandline arguments */
    if (parse_options(&ctx, "test_interface", argc, argv) != RM_OK)
    {
        fprintf(stderr, "ERROR: Incorrect parameters!\n");
        return -1;
    }

    if (open_gbus(&ctx, chipnum) == RM_ERROR)
    {
        fprintf(stderr, "ERROR: Unable to obtain gbus pointer!\n");
        return -1;
    }

    if (ctx.szReadToFilename != 0) {
        do_read_to_file(&ctx);
    } else if (ctx.szWriteFromFilename != 0) {
        do_write_from_file(&ctx);
    } else {
    	/* Parm checking in option parsing should prevent this */
        fprintf(stderr, "Nothing to do, quitting...");
    }

clean_exit:

    release_memory(&ctx);
    close_gbus(&ctx);

    close_log_files();

    return 0;
}


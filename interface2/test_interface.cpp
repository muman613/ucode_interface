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

#include "llad/include/llad.h"
#include "llad/include/gbus.h"
#include "ucode_load_microcode.h"
//#include "video_t4/src/video_microcode_labels.h"
#include "video_interface.h"
#include "utils.h"
#include "fileresolver.h"
#include "symbolmgr/symbolmgr.h"
#include "test_interface.h"

#ifdef ENABLE_CURSES
    #include "curses-mgr.h"
#endif // ENABLE_CURSES

#if 1
#define LOCALDBG ENABLE
#else
#define LOCALDBG DISABLE
#endif // 1

#define DISPLAY_PICTURE_INFO    1
#define VERBOSE_MESSAGES        1

#define ARCH SOC_CALYPSO

struct profileEntry {
    const char*     szIdent;
    int             nProfile;
};

/**
 *  Table which relates abbreviation string to codec ID.
 */

struct profileEntry profileTable[] = {
    { "mpeg2",  VideoProfileMPEG2, },
    { "mpeg4",  VideoProfileMPEG4, },
    { "h264",   VideoProfileH264, },
    { "h265",   VideoProfileH265, },
    { "hevc",   VideoProfileH265, },
    { 0L, 0, },
};

using namespace video_interface;

/**
 *  Parse profile option (which decoder to open).
 */

static RMstatus parse_profile_option(CONTEXT_PTR ctx, const char* profile)
{
    RMuint32 codec_id;

    codec_id = get_profile_id_from_string(profile);

    if ((int)codec_id != -1) {
        ctx->decoderProfile = codec_id;
    }

    return ((int)codec_id != -1)?RM_OK:RM_ERROR;
}

static void print_usage(const char* sAppName) {
    struct profileEntry *pCurEntry = profileTable;
    char *sAppCopy = strdup(sAppName);

    fprintf(stderr, "Usage: %s [-b binfile] [-c binfile] [-s streamfile] [-p (codec profile)] [-o YUVFile.yuv]\n", basename(sAppCopy));
    fprintf(stderr, "Supported codec profiles:\n");
    free(sAppCopy);

    while (pCurEntry->szIdent != NULL) {
        fprintf(stderr, "    %s\n", pCurEntry->szIdent);
        pCurEntry++;
    }

    exit( 0 );
}

/**
 *  Parse commandline options.
 */

static RMstatus parse_options(CONTEXT_PTR pCtx, const char* szAppName, int argc, char* argv[])
{
    int         opt;
    RMstatus    result = RM_ERROR;
    std::string sChipID, sChipMode;
    const char* opts="Dc:m:s:p:o:O:h";
    FILE_PACK   fPack;

    while ((opt = getopt(argc, argv, opts)) != -1)
    {
        switch (opt)
        {
        case 'D':
            pCtx->dump_y_uv = TRUE;
            break;

        case 'c':
            sChipID = optarg;
            break;

        case 'm':
            sChipMode = optarg;
            break;

        case 's':
            pCtx->file.sStrFilename = optarg;
            break;

        case 'p':
            if (parse_profile_option(pCtx, optarg) == RM_ERROR)
                goto exitParse;
            break;

        case 'o':
            pCtx->file.sYUVFilename = optarg;
            break;

        case 'O':
            pCtx->file.sYUVPath = optarg;
            break;

//        case 'e':
//            if (strcmp(optarg, "1") == 0) {
//                pCtx->pmBaseAddress       = PMEM_BASE_mpeg_engine_1;
//                pCtx->dmBaseAddress       = DMEM_BASE_mpeg_engine_1;
//                pCtx->regBaseAddress      = REG_BASE_mpeg_engine_1;
//            }
//            break;

        case 'h':
        default:
            print_usage( argv[0] );
        }
    }

    /* Make sure chip and mode specified! */
    if ((sChipID == "8758") ||
        (sChipID == "8760"))
    {
        if ((sChipMode == "d") ||
            (sChipMode == "r"))
        {
            /* Obtain the proper file paths... */
            fPack.resolve_package( sChipID, (sChipMode == "d")?true:false, "..");
            if (fPack.isvalid()) {
                pCtx->file.sBinFilename = fPack.sBinFile;

                if (!pCtx->symMgr.LoadSymbols(fPack.sLabelFile)) {
                    fprintf(stderr, "ERROR: Unable to load labels file!\n");
                    return RM_ERROR;
                }
#ifdef _DEBUG
                fprintf(stderr, "loaded %zu symbols!\n", pCtx->symMgr.size());
#endif // _DEBUG
            } else {
                fprintf(stderr, "ERROR: Unable to locate required files!\n");
                return RM_ERROR;
            }
        }
        else
        {
            fprintf(stderr, "ERROR: Must specify debug or release -mr or -md\n");
            return RM_ERROR;
        }

    } else {
        fprintf(stderr, "ERROR: Chip ID (-c) not specified or invalid!\n");
        return RM_ERROR;
    }

    /* verify that files exist */
    if ((!pCtx->file.sBinFilename.empty()) && (!pCtx->file.sStrFilename.empty()))
    {
        if ((file_exists( pCtx->file.sBinFilename ) == RM_OK) &&
            (file_exists( pCtx->file.sStrFilename ) == RM_OK))
        {
//            if (pCtx->szBinFilename[1] != 0) {
//                if (file_exists(pCtx->szBinFilename[1]) == RM_OK) {
//                result = RM_OK;
//                }
//            } else {
                set_tile_dimensions( pCtx.get(), sChipID );
                result = RM_OK;
//            }
        }
    } else {
        fprintf(stderr, "ERROR: Must at least specify microcode (-b) and input stream (-s)!\n");
    }


    if (result == RM_OK) {
        if ((!pCtx->file.sYUVFilename.empty()) && (!pCtx->file.sYUVPath.empty())) {
            fprintf(stderr, "ERROR: Cannot specify -o & -O together!\n");
            result = RM_ERROR;
        } else if (!pCtx->file.sYUVPath.empty()) {
            pCtx->file.sYUVFilename = generate_output_yuv( pCtx->file.sYUVPath,
                                                           pCtx->file.sStrFilename);
        }

        /* if user specified output yuv file, open it for writing... */
        if (!pCtx->file.sYUVFilename.empty())
        {
            pCtx->yuvfp = fopen( pCtx->file.sYUVFilename.c_str(), "w");

            if (pCtx->yuvfp == 0) {
                fprintf(stderr, "WARNING: Unable to open output YUV file %s.\n"
                        "Not saving decoded pictures...\n", pCtx->file.sYUVFilename.c_str());

                /* free and zero the YUV filename */
//                free((void*)pCtx->szYUVFilename);
//                pCtx->szYUVFilename = 0L;
            } else {
#ifdef ENABLE_CURSES
                SET_FLAG(pCtx, FLAG_SAVING_YUV);
#endif // ENABLE_CURSES
            }
        }

        pCtx->sChip     = sChipID;
#ifdef ENABLE_CURSES
        pCtx->pUIContext->szChip = pCtx->sChip.c_str(); //getenv("EM8XXX_SERVER");
#endif // ENABLE_CURSES
        pCtx->serverStr = getenv("EM8XXX_SERVER");

        if (pCtx->serverStr.empty()) {
            fprintf(stderr, "EM8XXX_SERVER environment is not defined!\n");
            result = RM_ERROR;
        } else {
#ifdef ENABLE_CURSES
            pCtx->pUIContext->szConn = pCtx->serverStr.c_str(); //getenv("EM8XXX_SERVER");
#endif // ENABLE_CURSES
        }

    }

exitParse:

    return result;
}



/**
 *  Open llad/gbus interface.
 */

static RMstatus open_gbus(CONTEXT_PTR pCtx /* , int chipNum */)
{
    if ((pCtx->pllad = llad_open((RMascii*)pCtx->serverStr.c_str())) == 0)
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

static void close_gbus(CONTEXT_PTR pCtx)
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

static void release_context(CONTEXT_PTR pCtx)
{

    if (!pCtx->file.sYUVFilename.empty())
    {
        if (pCtx->yuvfp != 0)
        {
            fclose(pCtx->yuvfp);
            pCtx->yuvfp = 0L;
        }

        if (pCtx->pLuma) {
            free((void*)pCtx->pLuma);
            pCtx->pLuma = 0L;
        }

        if (pCtx->pChroma) {
            free((void*)pCtx->pChroma);
            pCtx->pChroma = 0L;
        }
    }

#ifdef ENABLE_CURSES
    if (pCtx->pUIContext != 0L) {
        delete pCtx->pUIContext;
        pCtx->pUIContext=0L;
    }
#endif // ENABLE_CURSES

//    if (pCtx.symMgr != 0L) {
//        delete pCtx.symMgr;
//        pCtx.symMgr = 0L;
//    }

    return;
}

/**
 *  Load video microcode into memory.
 *
 *  Determine the size of the binary image file and allocate a buffer in memory,
 *  open the file and read the contents into the buffer. Pass buffer to
 *  ucode_load_microcode() function which parses buffer and writes the image
 *  to the correct memory (pm/dm/dram).
 */

static RMstatus load_video_ucode(CONTEXT_PTR pCtx /*, RMuint32 engineID */)
{
    RMstatus nRes = RM_ERROR;
    std::string     sBinName;
    unsigned char* 	pBinData = 0;
    size_t			binSize = 0;
    struct stat		statbuf;
    FILE*			ifp = 0L;
    RMuint32        pmBase   = 0L,
                    dmBase   = 0L;

    using namespace ucode_utils;

#ifdef ENABLE_CURSES
    APP_STATE       appState = APP_LOADING_MICROCODE_0;
#endif // ENABLE_CURSES

//    switch (engineID) {
//    case 0:
        pmBase      = PMEM_BASE_mpeg_engine_0;
        dmBase      = DMEM_BASE_mpeg_engine_0;
//        dramBase    = DRAM_BASE;
        sBinName   = pCtx->file.sBinFilename;
//        break;
//    case 1:
//        pmBase      = PMEM_BASE_mpeg_engine_1;
//        dmBase      = DMEM_BASE_mpeg_engine_1;
////        dramBase    = DRAM_BASE;
//        sBinName    = pCtx->sBinFilename[1];
//#ifdef ENABLE_CURSES
//        appState    = APP_LOADING_MICROCODE_1;
//#endif // ENABLE_CURSES
//        break;
//    default:
//        fprintf(stderr, "ERROR: Invalid engine specified!\n");
//        return RM_ERROR;
//    }

#ifdef ENABLE_CURSES
    ((UI_CONTEXT *)pCtx->pUIContext)->state = appState;
    update_user_interface((UI_CONTEXT*)pCtx->pUIContext);
#endif // ENABLE_CURSES

    if (stat(sBinName.c_str(), &statbuf) == 0) {
        RMuint32 dram_low_offset = 0, dram_high_offset = 0;

        binSize = statbuf.st_size;

        /* allocate buffer */
        pBinData = (unsigned char*)malloc(binSize);
        assert(pBinData != 0L);

#ifndef ENABLE_CURSES
        printf("Loading microcode '%s' (%d bytes) on engine %ld...\n",
               sBinName.c_str(), binSize, (RMuint32)0);
        fflush(stdout);
#endif // ENABLE_CURSES

        /* open file */
        ifp = fopen(sBinName.c_str(), "r");
        if (ifp) {
            size_t bytesread __attribute__((unused)) = fread(pBinData, 1, binSize, ifp);

            ucode_get_microcode_size(pBinData, binSize, &dram_low_offset, &dram_high_offset);

#ifndef ENABLE_CURSES
            printf("dram_low_offset = 0x%08lX dram_high_offset = 0x%08lX\n", dram_low_offset, dram_high_offset);
            fflush(stdout);
#endif // ENABLE_CURSES

            ucode_load_microcode(pCtx->pgbus, pmBase,dmBase,
                                 pCtx->dramBaseAddress, 2, pBinData, binSize);

            video_set_ucode_dram_offset(pCtx->pgbus, pmBase,
                                        pCtx->dramBaseAddress);

            fclose(ifp);

            pCtx->binSize = binSize;
            pCtx->dram_lo = dram_low_offset;
            pCtx->dram_hi = dram_high_offset;
        }

        free( pBinData );
        nRes = RM_OK;

        // advance in allocator
        pCtx->uiDRAMPtr += dram_high_offset;
    } else {
        fprintf(stderr, "ERROR: Invalid microcode file specified!\n");
    }

    return nRes;
}

/**
 *  Stop the DSP (sends RESET & STOP)
 */

static void do_stop_engine(CONTEXT_PTR pContext) {
    RMuint32    reset_control_reg = 0L;

    assert(pContext != 0L);
    reset_control_reg = pContext->memBaseAddress + pContext->reset_control;

#ifndef ENABLE_CURSES
    printf("Stopping DSP engine %ld...\n", (RMuint32)0);
    fflush(stdout);
#endif // ENABLE_CURSES

    gbus_write_uint32( pContext->pgbus, reset_control_reg, DSP_RESET); // reset
    gbus_write_uint32( pContext->pgbus, reset_control_reg, DSP_STOP); // stop

#ifdef WAIT_CONTROL
    while (((gbus_read_uint32( pContext->pgbus, reset_control_reg) & 0x0000ff00) >> 8)!= DSP_STOP);
#endif // WAIT_CONTROL

    return;

}

/**
 *  Start the DSP (Send RUN)
 */

static void do_start_engine(CONTEXT_PTR pContext) {
    RMuint32    reset_control_reg = 0L;

    assert(pContext != 0L);
    reset_control_reg = pContext->memBaseAddress + pContext->reset_control;

#ifndef ENABLE_CURSES
    printf("Starting DSP engine %ld...\n", (RMuint32)0);
    fflush(stdout);
#endif // ENABLE_CURSES

    gbus_write_uint32( pContext->pgbus, reset_control_reg, DSP_RUN); // start
    while (((gbus_read_uint32( pContext->pgbus, reset_control_reg) & 0x0000ff00) >> 8)!= DSP_RUN);

    return;

}

/**
 *
 */

static RMstatus init_video_engine (CONTEXT_PTR pContext)
{
    RMuint32 memBase = pContext->memBaseAddress;
    RMuint32 Address, Size;

    video_get_scheduler_memory(pContext->pgbus, memBase, &Address, &Size);

    if ((Address == 0) && Size) {
        Address = (pContext->uiDRAMPtr & 0xfffffffc) + 4; // align by 4
        video_set_scheduler_memory(pContext->pgbus, memBase, Address, Size);
        Size += 4;
        pContext->uiDRAMPtr += Size;
    }

    return RM_OK;
}

/**
 *  Initialize the DRAM interface.
 *
 *  Allocates and initializes several structures in DRAM used by the micrcode.
 */


static RMstatus open_video_decoder(CONTEXT_PTR pContext)
{
    RMuint32		unprotected_ptr = 0;
    RMuint32		i;
    RMstatus 		err;
    RMuint32 		video_bts_fifo;
    RMuint32		video_pts_fifo;

    unprotected_ptr = (pContext->uiDRAMPtr & 0xfffffffc) + 4;

    /* init video_task_data_base*/
    pContext->pvtdb = unprotected_ptr;
    for (i=0; i< sizeof(struct video_task_data_base)/4; i++)
        gbus_write_uint32(pContext->pgbus, unprotected_ptr+(4*i), 0);
    unprotected_ptr += sizeof(struct video_task_data_base);

#ifndef ENABLE_CURSES
//    printf("video_task_data_base @ 0x%08lx\n", pContext->pvtdb);
//    fflush(stdout);
#endif // ENABLE_CURSES

    /*init video_task_interface*/
    pContext->pvti = unprotected_ptr;
    for (i=0; i< sizeof(struct video_task_interface)/4; i++)
        gbus_write_uint32(pContext->pgbus, unprotected_ptr+(4*i), 0);
    unprotected_ptr += sizeof(struct video_task_interface);

#ifndef ENABLE_CURSES
//    printf("video_task_interface @ 0x%08lx\n", pContext->pvti);
//    fflush(stdout);
#endif // ENABLE_CURSES

    video_set_display_error_threshold(pContext->pgbus, (struct video_task_interface *)pContext->pvti, 0);
    video_set_anchor_propagation_parms(pContext->pgbus, (struct video_task_interface *)pContext->pvti, 500, 13);

    /* Set pvti pointer in DRAM */
    video_set_vti_pointer(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, pContext->pvti);
    /* Set pvtb in DMEM */
    video_set_vtdb_pointer(pContext->pgbus, MEM_BASE_mpeg_engine_0, 0, pContext->pvtdb);

#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
    /* Implement picture buffer variables here */
    err = video_set_data_context_buffer(pContext->pgbus, (struct video_task_interface *)pContext->pvti,
                                        RM_NEXT_TILE_ALIGN(unprotected_ptr), pContext->DecoderDataSize, pContext->DecoderContextSize);
    unprotected_ptr = RM_NEXT_TILE_ALIGN(unprotected_ptr) + pContext->DecoderDataSize;

    if (RMFAILED(err))
    {
        RMDBGLOG((ENABLE, "video_set_data_context_buffer failed!\n"));
        goto over;
    }
#else
    err = video_set_data_context_buffer(pContext->pgbus, (struct video_task_interface *)pContext->pvti,
                                        RM_NEXT_TILE_ALIGN(unprotected_ptr), pContext->DecoderDataSize, pContext->DecoderContextSize);
    unprotected_ptr = RM_NEXT_TILE_ALIGN(unprotected_ptr) + pContext->DecoderDataSize;

    if (RMFAILED(err))
    {
        RMDBGLOG((ENABLE, "video_set_data_context_buffer failed!\n"));
        goto over;
    }
#endif

    gbus_write_uint32(pContext->pgbus, (RMuint32)&((struct video_task_interface *)pContext->pvti)->MiscFlags, 1);

    /* use the inside allocated dram output fifo, we don't have to connect to a demux output or program */
    video_bts_fifo = unprotected_ptr;
    unprotected_ptr += sizeof(struct gbus_fifo_eraser);

    gbus_fifo_eraser_open(pContext->pgbus, RM_NEXT_PAGE_ALIGN(unprotected_ptr), pContext->BitstreamFIFOSize, video_bts_fifo);
    err = video_set_bts_fifo_pointer(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, video_bts_fifo);
    pContext->bts_fifo = video_bts_fifo;
    unprotected_ptr = RM_NEXT_PAGE_ALIGN(unprotected_ptr) + pContext->BitstreamFIFOSize;

    /* video pts fifo container is in video_task_data_base structure and data is allocated in DRAM */
    err = video_get_pts_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, &video_pts_fifo);
    err = video_open_pts_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, unprotected_ptr, pContext->PtsFIFOCount);
    unprotected_ptr += pContext->PtsFIFOCount * VPTS_FIFO_ENTRY_SIZE;

#if 1	// inband fifo
    /* video inband fifo container is in video_task_data_base structure and data is allocated in DRAM */
    video_open_inband_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, unprotected_ptr, pContext->InbandFIFOCount);
    unprotected_ptr += pContext->InbandFIFOCount * sizeof(struct MicrocodeInbandCommand);
    pContext->inband_params_address = unprotected_ptr;
    unprotected_ptr += pContext->InbandFIFOCount * sizeof(struct MicrocodeInbandParams);
    /* allocate and clear inband_params */
    {
        RMuint32 i;
        // clear params memory
        for (i=0; i<pContext->InbandFIFOCount * sizeof(struct MicrocodeInbandParams)/sizeof(RMuint32); i++)
        {
            gbus_write_uint32(pContext->pgbus, pContext->inband_params_address + 4*i, 0);
        }
    }
    gbus_write_uint32(pContext->pgbus, (RMuint32) &(((struct video_task_data_base *)pContext->pvtdb)->Inband_Params_Address), pContext->inband_params_address);
#endif
    // the display fifo container is in video decoder interface
    err = video_get_display_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, &pContext->display_fifo);

    gbus_entry_fifo_open(pContext->pgbus, unprotected_ptr, pContext->NumOfPictures + 1, pContext->display_fifo);

    //clear the pointers to picture buffers
    for ( i =0; i < pContext->NumOfPictures + 1; i++)
    {
        gbus_write_uint32(pContext->pgbus, unprotected_ptr + (4* i), 0);
    }

    unprotected_ptr += sizeof(RMuint32) * (pContext->NumOfPictures + 1);


    video_get_irq_info(pContext->pgbus, (struct video_task_interface *)pContext->pvti, &pContext->event_table_pointer);


    /* initialize user data fifo - the container and data are in DRAM */
    err = video_get_user_data_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, &pContext->user_data_fifo);
    err = video_open_user_data_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, unprotected_ptr, pContext->UserDataSize);
    unprotected_ptr += pContext->UserDataSize;
    if (pContext->UserDataSize)
    {
        /* initialize the internal user_data input and helper fifo  */
        gbus_fifo_eraser_open(pContext->pgbus, unprotected_ptr, pContext->UserDataSize, (RMuint32) &(((struct video_task_data_base *)pContext->pvtdb)->user_data_in_fifo));
        unprotected_ptr += pContext->UserDataSize;
        gbus_entry_fifo_eraser_open(pContext->pgbus, unprotected_ptr, pContext->UserDataSize / 16, (RMuint32) &(((struct video_task_data_base *)pContext->pvtdb)->user_data_info_fifo));
        unprotected_ptr += (pContext->UserDataSize / 16)  * (2*sizeof(RMuint32));
    }
    else
    {
        /* if user data is not required initialize the start address to 0 for the internal user_data input and helper fifo  */
        gbus_fifo_eraser_open(pContext->pgbus, 0, 0, (RMuint32) &(((struct video_task_data_base *)pContext->pvtdb)->user_data_in_fifo));
        gbus_entry_fifo_eraser_open(pContext->pgbus, 0, 0, (RMuint32) &(((struct video_task_data_base *)pContext->pvtdb)->user_data_info_fifo));
    }

    err = video_open_error_code_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, unprotected_ptr, DECODE_ERROR_ENTRIES);//pValueIn->ErrorCodeCount);
    unprotected_ptr += DECODE_ERROR_ENTRIES * sizeof(struct EMhwlibVideoDecoder_DecodeError);

    video_set_extra_pictures(pContext->pgbus, (struct video_task_interface *)pContext->pvti, pContext->ExtraPictureBufferCount);
    /* commands sent by application or microcode (from outside) */

    pContext->uiDRAMPtr = unprotected_ptr;


over:

    return err;
}

/**
 *  Send a command to the microcode interface.
 *
 *  Sends a command to the microcode and waits for the command to be accepted by
 *  the microcode. If the status is not updated before COMMAND_TIMEOUT usecs
 *  return error RM_PENDING.
 */

static RMstatus send_video_command(CONTEXT_PTR ctx, enum VideoCommand cmd, enum VideoStatus stat)
{
    RMstatus            result = RM_ERROR;
    enum VideoStatus    VideoDecoderStatus;
    RMuint32            started;

#ifdef  ENABLE_CURSES
    APP_STATE appState;

    switch (cmd) {
    case VideoCommandUninit:
        appState = APP_SENDING_UNINIT;
        break;
    case VideoCommandInit:
        appState = APP_SENDING_INIT;
        break;
    case VideoCommandPlayFwd:
        appState = APP_SENDING_PLAY;
        break;
    case VideoCommandStop:
        appState = APP_SENDING_STOP;
        break;
    default:
        appState = APP_STATE_UNKNOWN;
        break;
    }
    ((UI_CONTEXT*)ctx->pUIContext)->state = appState;
    update_user_interface( (UI_CONTEXT*)ctx->pUIContext );
#else
    printf("send_video_command %d\n", (int) cmd);
    fflush(stdout);
#endif // ENABLE_CURSES

    video_set_command( ctx->pgbus, (struct video_task_interface*)ctx->pvti, cmd );

    started = gbus_time_us( ctx->pgbus );

    while (1)
    {
        video_get_status(ctx->pgbus, (struct video_task_interface *)ctx->pvti,
                         &VideoDecoderStatus);

        //printf("-- status %d\n", (int) VideoDecoderStatus);

        if (VideoDecoderStatus == stat) {
            result = RM_OK;
            break;
        }

        if (gbus_time_delta(started, gbus_time_us(ctx->pgbus)) > COMMAND_TIMEOUT) {
            printf("-- TIMEOUT (command not received) --\n");
            result = RM_PENDING;
            break;
        }
        //usleep(1000);
    }

    return result;
}

/**
 *  Set the profile for the video decoder.
 *
 *  Sends uninit command, sets the profile, and sends the init command.
 */

static RMstatus set_video_codec(CONTEXT_PTR ctx)
{
    send_video_command( ctx, VideoCommandUninit,  VideoStatusUninit );

    video_set_profile( ctx->pgbus, (struct video_task_interface*)ctx->pvti, ctx->decoderProfile );

    send_video_command( ctx, VideoCommandInit,    VideoStatusStop );

    return RM_OK;
}

/**
, *  Write data into the bitstream FIFO.
 *
 *  Function to write data into a circular FIFO including wrap-around condition.
 */

static RMuint32 write_data_in_circular_bts_fifo(CONTEXT* ctx, RMuint8 *pBuf, RMuint32 sizeToSend)
{
    struct gbus*        pgbus = ctx->pgbus;
	struct gbus_fifo*   fifo;
	RMuint32            rd, wr, fifo_base, fifo_size;
	RMuint32            size, sizeLeft;

	fifo = (struct gbus_fifo *)ctx->bts_fifo;
	fifo_base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
	fifo_size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
	rd = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	wr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));

#ifdef ENABLE_CURSES
    lock_context( (UI_CONTEXT*)ctx->pUIContext );

    SET_DISPLAY_CONTEXT( ctx, BtsFifo.uiFifoCont, (RMuint32)fifo );
    SET_DISPLAY_CONTEXT( ctx, BtsFifo.uiFifoPtr, fifo_base);
    SET_DISPLAY_CONTEXT( ctx, BtsFifo.uiFifoSize, fifo_size);
    SET_DISPLAY_CONTEXT( ctx, BtsFifo.uiFifoRdPtr, rd);
    SET_DISPLAY_CONTEXT( ctx, BtsFifo.uiFifoWrPtr, wr);

    unlock_context( ctx->pUIContext );
#else
    printf("FIFO @ 0x%08lX START 0x%08lX SIZE 0x%08lX RD = 0x%08lX WR = 0x%08lX\n",
            (unsigned long)fifo, fifo_base, fifo_size, rd, wr);
    fflush(stdout);
#endif // ENABLE_CURSES

	if ( rd > wr ) {
		/* emptiness in one chunk */
		RMuint32 empty;
		empty = rd - wr - 1;
		if (empty < sizeToSend)
			return sizeToSend;

		gbus_write_data8(pgbus, fifo_base + wr, pBuf, sizeToSend);
	}
	else { // rd <= wr
		/* emptiness in two chunks because of circular fifo. */
		RMuint32 empty;
		empty = fifo_size - wr + rd - 1;
		if (empty < sizeToSend)
			return sizeToSend;
		//first chunk
		size = RMmin(fifo_size - wr, sizeToSend);
		gbus_write_data8(pgbus, fifo_base + wr, pBuf, size);

		//second chunk
		sizeLeft = sizeToSend - size;
		if (sizeLeft)
			gbus_write_data8(pgbus, fifo_base, pBuf+size, sizeLeft);
	}
	sizeLeft = 0;
	wr = (wr + sizeToSend) % fifo_size;
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), wr);

#ifndef ENABLE_CURSES
#ifdef BTS_FIFO_DEBUG
	printf("%s %s: fifo=%p st=0x%08lx sz=0x%08lx rd=0x%08lx wr=0x%08lx bc=0x%08lx toSend=0x%lx left=0x%lx\n",
		__FUNCTION__, send_data ?"play":"pause", fifo, fifo_base, fifo_size, rd, wr, pCtx->dt_byte_counter, sizeToSend, sizeLeft);
    fflush(stdout);
#endif // BTS_FIFO_DEBUG
#endif // ENABLE_CURSES

    return sizeLeft;
}

static RMuint32 get_la_from_ta(RMuint32 ta)
{
    return ((ta >> 12) << 12) | (((ta >> 8) & 1) << 11) | (((ta >> 9) & 7) << 8) | (ta & 0xff);
}

static RMuint32 offset_address_calypso(RMuint32 tile_width_l2, RMuint32 tile_height_l2,
                        RMuint32 x, RMuint32 y, RMuint32 stride, RMuint32 nb_comp)
{
    return    (((x * nb_comp) &~ ((1 << tile_width_l2) - 1)) * (12 * stride + 2))
                + (y << tile_width_l2)
                + ((x * nb_comp) & ((1 << tile_width_l2) - 1));
}

static RMuint32 offset_address_tango(RMuint32 tile_width_l2, RMuint32 tile_height_l2,
                               RMuint32 x, RMuint32 y, RMuint32 tiled_buffer_width, RMuint32 nb_comp)
{
    return    (y >> tile_height_l2) * (tiled_buffer_width << (tile_width_l2 + tile_height_l2))
              + ((y & ((1 << tile_height_l2) - 1)) << tile_width_l2)
              + (((x * nb_comp) >> tile_width_l2) << (tile_width_l2 + tile_height_l2))
              + ((x * nb_comp) & ((1 << tile_width_l2) - 1));
}

static RMuint32 offset_address(SOC_ARCH soc_arch, RMuint32 tile_width_l2, RMuint32 tile_height_l2,
                               RMuint32 x, RMuint32 y, RMuint32 geometry, RMuint32 nb_comp, RMuint32 ta2la_switch)
{
    if (soc_arch == SOC_TANGO)  // tango chip, geometry is tiled buffer width here
        return offset_address_tango(tile_width_l2, tile_height_l2, x, y, geometry, nb_comp);
    else if (soc_arch == SOC_PMAN) {
        return y * geometry + x * nb_comp;
    } else { // calypso chip, geometry is stride here
        RMuint32 offset_tiled_address;
        offset_tiled_address = offset_address_calypso(tile_width_l2, tile_height_l2, x, y, geometry, nb_comp);
        if (ta2la_switch == 1)
            return get_la_from_ta(offset_tiled_address);
        else
            return offset_tiled_address;
    }
}

/**
 *  Save picture buffer in YUV output file.
 */

static void save_frame(CONTEXT* ctx, RMuint32 frame_count,
                       struct EMhwlibWindow* luma_position_in_buffer, RMuint32 luma_ttl_wd,
                       struct EMhwlibWindow* chroma_position_in_buffer, RMuint32 chroma_ttl_wd)
{
//  RMuint8  *pLuma     = ctx->pLuma;
//  RMuint8  *pChroma   = ctx->pChroma;
    RMuint32 luma_x     = luma_position_in_buffer->x;
//  RMuint32 luma_y     = luma_position_in_buffer->y;
    RMuint32 luma_w     = luma_position_in_buffer->width;
    RMuint32 luma_h     = luma_position_in_buffer->height;
    RMuint32 chroma_x   = chroma_position_in_buffer->x;
//  RMuint32 chroma_y   = chroma_position_in_buffer->y;
    RMuint32 chroma_w   = chroma_position_in_buffer->width;
    RMuint32 chroma_h   = chroma_position_in_buffer->height;
//	RMuint32 chromasize = 0;
//	RMuint8	 *data      = 0L;
//	RMuint8	 *ptr       = 0L;
    RMuint32 x,y;
    RMuint32 x_min, x_max, y_min, y_max;
    RMuint32 luma_tile_cnt, chroma_tile_cnt;
    RMuint8  *uPtr      = 0L,
             *vPtr      = 0L;
    RMuint32 i;

#ifndef ENABLE_CURSES
    printf("Saving frame %ld (luma %ld x %ld) (chroma %ld x %ld)...\n", frame_count,
           luma_w, luma_h, chroma_w, chroma_h);
    fflush(stdout);
#endif // ENABLE_CURSES

    luma_w   = luma_w * ctx->luma_nb_comp_per_sample;
    chroma_w = chroma_w * ctx->chroma_nb_comp_per_sample;

    luma_tile_cnt   = (luma_ttl_wd + (1 << ctx->tile_width_l2) - 1) / ( 1<<ctx->tile_width_l2);
    chroma_tile_cnt = (chroma_ttl_wd + (1 << ctx->tile_width_l2) - 1) / ( 1<<ctx->tile_width_l2);

    y_min = 0;
    y_max = luma_h;
    x_min = luma_x;
    x_max = luma_w+luma_x;

    for (y = y_min ; y < y_max ; y++) {
        for (x = x_min ; x < x_max ; x++) {
            RMuint8*    pData = ctx->pLuma + offset_address(ctx->soc_arch,
                                                            ctx->tile_width_l2,
                                                            ctx->tile_height_l2,
                                                            x, y,
                                                            luma_tile_cnt, 1, 1);
            fwrite(pData, 1, 1, ctx->yuvfp);
        }
    }

    y_min = 0;
    y_max = chroma_h;
    x_min = chroma_x * 2;
    x_max = chroma_w + (chroma_x * 2);

    uPtr = (RMuint8*)malloc( (chroma_w * chroma_h) / 2);
    vPtr = (RMuint8*)malloc( (chroma_w * chroma_h) / 2);

    i = 0;
    for (y = y_min ; y < y_max ; y++) {
        for (x = x_min ; x < x_max ; x += 2, i++) {
            RMuint8*    pData = ctx->pChroma + offset_address(ctx->soc_arch,
                                                            ctx->tile_width_l2,
                                                            ctx->tile_height_l2,
                                                            x, y,
                                                            chroma_tile_cnt, 1, 1);
            uPtr[i] = pData[0];
            vPtr[i] = pData[1];
        }
    }

    fwrite(uPtr, (chroma_w * chroma_h)/2, 1, ctx->yuvfp);
    fwrite(vPtr, (chroma_w * chroma_h)/2, 1, ctx->yuvfp);

    free( vPtr );
    free( uPtr );
}

/**
 *  Extract picture from display FIFO.
 */

static RMstatus process_picture(CONTEXT* ctx, RMuint32 picture_address)
{
    struct gbus*    pgbus = ctx->pgbus;
    RMstatus        result = RM_ERROR;
    RMuint32        frame_count = 0;
    RMuint32        luma_address = 0,
                    chroma_address = 0;
    RMuint32        luma_ttl_wd = 0,
                    chroma_ttl_wd = 0;
    RMuint32        luma_buf_width   = 0,
                    luma_buf_height  = 0,
                    chroma_buf_width = 0,
                    chroma_buf_height = 0;
    RMuint32        luma_size_tile = 0,
                    chroma_size_tile = 0;
    struct EMhwlibWindow    luma_position_in_buffer,
                            chroma_position_in_buffer;
    RMuint8         *pLuma, *pChroma;
//  union VideoMicrocodePictureDisplayData pic_data_type;

    frame_count     = READ_PICTURE_BUFFER(pgbus, picture_address, frame_count);
    luma_address    = READ_PICTURE_BUFFER(pgbus, picture_address, luma_address);
    chroma_address  = READ_PICTURE_BUFFER(pgbus, picture_address, chroma_address);
    luma_ttl_wd     = READ_PICTURE_BUFFER(pgbus, picture_address, luma_total_width);
    chroma_ttl_wd   = READ_PICTURE_BUFFER(pgbus, picture_address, chroma_total_width);
//  pic_data_type   = (union VideoMicrocodePictureDisplayData)READ_PICTURE_BUFFER(pgbus, picture_address, picture_display_data);

    READ_PICTURE_BUFFER_STRUCT(pgbus, picture_address, luma_position_in_buffer,
                               luma_position_in_buffer, struct EMhwlibWindow);
    READ_PICTURE_BUFFER_STRUCT(pgbus, picture_address, chroma_position_in_buffer,
                               chroma_position_in_buffer, struct EMhwlibWindow);

    /* calculate luma buffer size */
    luma_buf_width  = ((luma_position_in_buffer.width + ctx->pvc_tw - 1)/ctx->pvc_tw) * ctx->pvc_tw;
    luma_buf_height = ((luma_position_in_buffer.height + ctx->pvc_th - 1)/ctx->pvc_th) * ctx->pvc_th;
    luma_size_tile = (luma_buf_width * luma_buf_height);

    /* calculate chroma buffer size */
    chroma_buf_width  = ((chroma_position_in_buffer.width + ctx->pvc_tw - 1)/ctx->pvc_tw) * ctx->pvc_tw;
    chroma_buf_height = ((chroma_position_in_buffer.height + ctx->pvc_th - 1)/ctx->pvc_th) * ctx->pvc_th;
    chroma_size_tile = (chroma_buf_width * chroma_buf_height) * 2;

    result          = RM_OK;

//    /* Save width & height */
//    ctx->picture_w = luma_position_in_buffer.width;
//    ctx->picture_h = luma_position_in_buffer.height;
//    ctx->picture_count = frame_count;

#ifdef ENABLE_CURSES
    lock_context( ctx->pUIContext );

    SET_DISPLAY_CONTEXT(ctx, frameCnt, frame_count);
    SET_DISPLAY_CONTEXT(ctx, picbuf.uiPicAddress, picture_address);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiBufAddress, luma_address);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiTotalWidth, luma_ttl_wd);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiBufWidth, luma_buf_width);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiBufHeight, luma_buf_height);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiPosX, luma_position_in_buffer.x);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiPosY, luma_position_in_buffer.y);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiPosWidth, luma_position_in_buffer.width);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiPosHeight, luma_position_in_buffer.height);
    SET_DISPLAY_CONTEXT(ctx, picbuf.lumaComp.uiSizeTile, luma_size_tile);

    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiBufAddress, chroma_address);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiTotalWidth, chroma_ttl_wd);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiBufWidth, chroma_buf_width);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiBufHeight, chroma_buf_height);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiPosX, chroma_position_in_buffer.x);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiPosY, chroma_position_in_buffer.y);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiPosWidth, chroma_position_in_buffer.width);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiPosHeight, chroma_position_in_buffer.height);
    SET_DISPLAY_CONTEXT(ctx, picbuf.chromaComp.uiSizeTile, chroma_size_tile);

    unlock_context( ctx->pUIContext );
#else
#ifdef  DISPLAY_PICTURE_INFO
    printf("frame %ld luma_buffer @ 0x%08lx width 0x%08lx chroma_buffer @ 0x%08lx width 0x%08lx\n",
           frame_count, luma_address, luma_ttl_wd, chroma_address, chroma_ttl_wd);
//  printf("picture_data_type = %ld format = %d bits_per_pixel = %d\n", pic_data_type.value, pic_data_type.bits.pixel_format, pic_data_type.bits.bits_per_pixel);
    printf("luma tiled dimensions ( %ld x %ld ) chroma tiled dimensions ( %ld x %ld )\n", luma_buf_width,
           luma_buf_height, chroma_buf_width, chroma_buf_height);
    printf("==> luma position   x %ld y %ld w %ld h %ld size_tile %ld\n", luma_position_in_buffer.x,
           luma_position_in_buffer.y, luma_position_in_buffer.width, luma_position_in_buffer.height, luma_size_tile);
    printf("==> chroma position x %ld y %ld w %ld h %ld size_tile %ld\n", chroma_position_in_buffer.x,
           chroma_position_in_buffer.y, chroma_position_in_buffer.width, chroma_position_in_buffer.height, chroma_size_tile);
    fflush(stdout);
#endif
#endif // ENABLE_CURSES

    RMDBGLOG((ENABLE, "Picture Buffer @ 0x%08lx\n", picture_address));
    RMDBGLOG((ENABLE, "Luma Buffer    @ 0x%08lx %ld bytes\n", luma_address, luma_size_tile));
    RMDBGLOG((ENABLE, "Chroma Buffer  @ 0x%08lx %ld bytes\n", chroma_address, chroma_size_tile));

    /* If saving frames to file... */
    if (ctx->yuvfp != 0) {
        if (ctx->pLuma == 0) {
            ctx->pLuma = (RMuint8*)malloc(luma_size_tile);
        }

        if (ctx->pChroma == 0) {
            ctx->pChroma = (RMuint8*)malloc(chroma_size_tile);
        }

        pLuma   = ctx->pLuma;
        pChroma = ctx->pChroma;

        gbus_read_data8(pgbus, luma_address,   pLuma,   luma_size_tile);
        gbus_read_data8(pgbus, chroma_address, pChroma, chroma_size_tile);

        if (ctx->dump_y_uv == TRUE) {
            char sYFname[128], sUVFname[128];
            FILE *yFP = 0, *uvFP = 0;

            RMDBGLOG((LOCALDBG, "Saving frame %ld .Y & .UV to /tmp/\n", frame_count));

            snprintf(sYFname, 128, "/tmp/frame%03ld-tiled.Y", frame_count);
            snprintf(sUVFname, 128, "/tmp/frame%03ld-tiled.UV", frame_count);

            yFP = fopen(sYFname, "wb");
            uvFP = fopen(sUVFname, "wb");
            if ((yFP != 0) && (uvFP != 0)) {
                fwrite(pLuma,   1, luma_size_tile,   yFP);
                fwrite(pChroma, 1, chroma_size_tile, uvFP);
            }
            fclose(uvFP);
            fclose(yFP);
        }

        save_frame(ctx, frame_count,
                    &luma_position_in_buffer, luma_ttl_wd,
                    &chroma_position_in_buffer, chroma_ttl_wd);

        result = RM_OK;
    }

    /* Save width & height */
    ctx->picture_w = luma_position_in_buffer.width;
    ctx->picture_h = luma_position_in_buffer.height;
    ctx->picture_count = frame_count;


    return result;
}

#ifdef ENABLE_THREADS

/**
 *  Thread used to fill the bitstream fifo.
 */

static void* fifoFillThread(void* arg) {
    CONTEXT*        ctx = (CONTEXT*)arg;
    FILE*           ifp;
    unsigned char   Buffer[BUFFERSIZE];
    RMuint32        bytesRead, sizeLeft;
//  RMuint32        nDone = 0;
//  RMuint32        loopCount = 0;
    unsigned char*  pBuffer = 0;

    ctx->fifoFillRunning = TRUE;    // set thread flag to running.
#ifdef  ENABLE_CURSES
    SET_FLAG( ctx, FLAG_FILLTHREAD_RUNNING );
#endif // ENABLE_CURSES

    /* Open the input stream */
    if ((ifp = fopen(ctx->file.sStrFilename.c_str(), "r")) != 0) {
//      printf("%s: %s\n", __FUNCTION__, ctx->szStrFilename);

        while (!feof(ifp)) {
//          RMuint32 nTry = 0;

            bytesRead = fread(Buffer, 1, BUFFERSIZE, ifp);
            sizeLeft  = bytesRead;
            pBuffer   = Buffer;

            while (sizeLeft && (ctx->terminateThreads == FALSE)) {
//                RMuint32 sizeToRead = sizeLeft;

                sizeLeft = write_data_in_circular_bts_fifo(ctx, pBuffer, sizeLeft);

//                fprintf(stderr, "sizeLeft = %ld sizeToRead = %ld\n", sizeLeft, sizeToRead);

                if (sizeLeft==0)
                    break;
            }

            if (ctx->terminateThreads == TRUE) {
#ifndef ENABLE_CURSES
                fprintf(stderr, "-- Terminating fifoFillThread thread!\n");
#endif // ENABLE_CURSES
                break;
            }

            usleep(50000);
        }
        fclose(ifp);

//      printf("%s: EndOfFile %s\n", __FUNCTION__, ctx->szStrFilename);

    } else {
        fprintf(stderr, "ERROR: Unable to open input stream!\n");
    }

//exit:
#ifdef ENABLE_CURSES
    CLEAR_FLAG( ctx, FLAG_FILLTHREAD_RUNNING );
#endif // ENABLE_CURSES
    ctx->fifoFillRunning = FALSE;

    return 0;
}

#define BILLION 1000000000L

/**
 *  Thread used to empty picture buffers.
 */

static void* fifoEmptyThread(void* arg)
{
    CONTEXT*                ctx = (CONTEXT*)arg;
    struct gbus*            pgbus = ctx->pgbus;
    struct gbus_entry_fifo* fifo;
    RMuint32                entry_size = 4; // address for the picture info
    RMuint32                rd, wr, fifo_base, fifo_size;
    RMuint32                size = 0, picture_address;
    RMuint32                total_frames = 0;
#ifdef  ENABLE_PROFILING
    struct timespec         ts1, ts2, ts3 = { 0, 0 };
#endif // ENABLE_PROFILING
//    RMuint64                ns;

    ctx->fifoEmptyRunning = TRUE;
#ifdef ENABLE_CURSES
    SET_FLAG( ctx, FLAG_EMPTYTHREAD_RUNNING );
#endif // ENABLE_CURSES

    fifo = (struct gbus_entry_fifo *)ctx->display_fifo;

    while (ctx->terminateThreads == FALSE) {
        fifo_base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
        fifo_size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
        rd = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
        wr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));

#ifdef ENABLE_CURSES
        lock_context( ctx->pUIContext );

        SET_DISPLAY_CONTEXT( ctx, DispFifo.uiFifoCont, (RMuint32)fifo );
        SET_DISPLAY_CONTEXT( ctx, DispFifo.uiFifoPtr, fifo_base );
        SET_DISPLAY_CONTEXT( ctx, DispFifo.uiFifoSize, fifo_size );
        SET_DISPLAY_CONTEXT( ctx, DispFifo.uiFifoRdPtr, rd );
        SET_DISPLAY_CONTEXT( ctx, DispFifo.uiFifoWrPtr, wr );
        if ((ts3.tv_sec != 0) || (ts3.tv_nsec != 0)) {
            SET_DISPLAY_CONTEXT( ctx, secsPerFrame, get_ts_seconds(ts3));
        }

        unlock_context( ctx->pUIContext );
#endif // ENABLE_CURSES

        if ( wr >= rd ){
            /* fullness in one chunck */
            size = wr - rd;
        } else if (wr != rd) {
            /* fullness in two chuncks because of circular fifo. */
            size = fifo_size - rd + wr;
        }

        /* If there is a picture available extract it, if the terminate thread
           flag is set exit the loop. */
        while (size && (ctx->terminateThreads == FALSE)) {
            picture_address = gbus_read_uint32(pgbus, fifo_base + rd*entry_size);

#ifndef ENABLE_CURSES
#ifdef  VERBOSE_MESSAGES
            printf("%s disp_fifo=0x%lx pic=0x%lx wr=0x%lx rd=0x%lx\n",
                   __FUNCTION__, ctx->display_fifo, picture_address, wr, rd);
            fflush(stdout);
#endif
#endif // ENABLE_CURSES

#ifdef ENABLE_PROFILING
            clock_gettime(CLOCK_REALTIME, &ts1);
#endif // ENABLE_PROFILING

            process_picture(ctx, picture_address);

#ifdef ENABLE_PROFILING
            clock_gettime(CLOCK_REALTIME, &ts2);

            ts3 = difftimespec( ts1, ts2 );
#endif // ENABLE_PROFILING

            // advance read pointer
            rd = (rd + 1) % fifo_size;
            size--;
            // release pictures
            gbus_write_uint32(pgbus, (RMuint32) &(((struct VideoMicrocodePicture *)picture_address)->picture_display_status), 0);

            total_frames++;

            // update FIFO read pointer
            gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd);
        }

        if (ctx->terminateThreads == TRUE) {
#ifndef ENABLE_CURSES
            printf("Terminating fifoEmptyThread!\n");
#endif // ENABLE_CURSES
            break;
        }

        usleep(50000);
    }

    //printf("-- %ld frames consumed!\n", total_frames);
    ctx->fifoEmptyRunning = FALSE;
#ifdef ENABLE_CURSES
    CLEAR_FLAG( ctx, FLAG_EMPTYTHREAD_RUNNING );
#endif // ENABLE_CURSES

    return 0;
}

/**
 *  Launch the FIFO fill and FIFO empty threads.
 */

static int launch_threads(CONTEXT_PTR pCtx)
{
#ifndef ENABLE_CURSES
    printf("Launching FIFO fill thread...\n");
#endif // ENABLE_CURSES

    if (pthread_create(&pCtx->fifoFillThread, NULL, fifoFillThread, pCtx.get()) != 0) {
        fprintf(stderr, "ERROR: Unable to start FIFO fill thread!\n");
        return 0;
    } else {
#ifndef ENABLE_CURSES
        printf("Launching FIFO empty thread...\n");
#endif // ENABLE_CURSES
        if (pthread_create(&pCtx->fifoEmptyThread, NULL, fifoEmptyThread, pCtx.get()) != 0) {
            fprintf(stderr, "ERROR: Unable to start FIFO empty thread!\n");
            return 0;
        }
    }
#ifndef ENABLE_CURSES
    fflush(stdout);
#endif // ENABLE_CURSES

    /* Wait for both threads to enter running state */
    while ((pCtx->fifoFillRunning == FALSE) ||
           (pCtx->fifoEmptyRunning == FALSE))
    {
        usleep(50);
    }

#ifdef ENABLE_CURSES
    /* Update user interface elements */
    SET_DISPLAY_CONTEXT(pCtx, startTime, time(NULL));
    SET_DISPLAY_CONTEXT(pCtx, state, APP_PLAYING);
    SET_DISPLAY_CONTEXT(pCtx, szPlayFile, pCtx->file.sStrFilename.c_str());
    SET_DISPLAY_CONTEXT(pCtx, szCapFile, pCtx->file.sYUVFilename.c_str());
    SET_DISPLAY_CONTEXT(pCtx, szBinFile[0], pCtx->file.sBinFilename.c_str());
//    SET_DISPLAY_CONTEXT(pCtx, szBinFile[1], pCtx->szBinFilename[1]);
    SET_DISPLAY_CONTEXT(pCtx, uivtdb, pCtx->pvtdb);
    SET_DISPLAY_CONTEXT(pCtx, uivtif, pCtx->pvti);
    SET_DISPLAY_CONTEXT(pCtx, codec, get_profile_string_from_id(pCtx->decoderProfile));

    update_user_interface( pCtx->pUIContext );
#endif // ENABLE_CURSES

    while ((pCtx->fifoFillRunning == TRUE) ||
           (pCtx->fifoEmptyRunning == TRUE))
    {
#ifdef ENABLE_CURSES
        int ch = getch();

        if (ch != ERR) {
            if (ch == 'q' || ch == 'Q') {
                pCtx->terminateThreads = TRUE;
                SET_FLAG(pCtx, FLAG_QUIT_IN_PROGRESS);
                break;
            }

            if ((toupper(ch) == 'V') && (pCtx->yuvfp != 0)) {
                launch_viewer(pCtx.get());
            }
        }

        update_user_interface( pCtx->pUIContext );

#else   // ENABLE_CURSES

        int ch = getkey();

        if (ch != EOF) {
            if (ch == 'q' || ch == 'Q') {
                printf("User hit quit... Please wait!\n");
                fflush(stdout);
                pCtx->terminateThreads = TRUE;
                break;
            }
        }
#endif // ENABLE_CURSES

        usleep(5000);
    }

    /* Wait for threads to complete... */
    pthread_join( pCtx->fifoFillThread, NULL);
    pthread_join( pCtx->fifoEmptyThread, NULL);

    return 1;
}

#else   // ENABLE_THREADS

/**
 *  Read pictures out of display FIFO.
 *
 *  Read all currently output frames from the display FIFO.
 */

static RMuint32 consume_pictures(CONTEXT* ctx)
{
    struct gbus*            pgbus = ctx->pgbus;
    struct gbus_entry_fifo* fifo;
    RMuint32                entry_size = 4; // address for the picture info
    RMuint32                rd, wr, fifo_base, fifo_size;
    RMuint32                size, picture_address;
    RMuint32                total_frames = 0;

    fifo = (struct gbus_entry_fifo *)ctx->display_fifo;
    fifo_base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
    fifo_size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
    rd = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
    wr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));

    if ( wr >= rd )
    {
        /* fullness in one chunck */
        size = wr - rd;
    }
    else if (wr != rd)
    {
        /* fullness in two chuncks because of circular fifo. */
        size = fifo_size - rd + wr;

    }

    while (size)
    {
        picture_address = gbus_read_uint32(pgbus, fifo_base + rd*entry_size);

#ifndef ENABLE_CURSES
#ifdef  VERBOSE_MESSAGES
        printf("%s disp_fifo=0x%lx pic=0x%lx wr=0x%lx rd=0x%lx\n",
               __FUNCTION__, ctx->display_fifo, picture_address, wr, rd);
        fflush(stdout);
#endif
#endif // ENABLE_CURSES

        process_picture(ctx, picture_address);

        rd = (rd + 1) % fifo_size;
        size--;
        // release pictures
        gbus_write_uint32(pgbus, (RMuint32) &(((struct VideoMicrocodePicture *)picture_address)->picture_display_status), 0);
        total_frames++;
    }

    gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd);

    //printf("-- %ld frames consumed!\n", total_frames);

    return total_frames;
}

/**
 *  Open input stream and send to bitstream FIFO.
 */

static void send_data(CONTEXT* ctx)
{
    FILE*           ifp;
    unsigned char   Buffer[BUFFERSIZE];
    RMuint32        bytesRead, sizeLeft;
    RMuint32        nDone = 0;
    RMuint32        loopCount = 0;
    unsigned char*  pBuffer = 0;

    /* Open the input stream */
    if ((ifp = fopen(ctx->szStrFilename, "r")) != 0)
    {
        printf("%s: %s\n", __FUNCTION__, ctx->szStrFilename);

        while (!feof(ifp))
        {
            RMuint32 nTry = 0;

            if (_kbhit() != 0)
            {
                char ch = getchar();

                /* Did the user hit 'q' key? */
                if (tolower(ch) == 'q')
                {
                    printf("-- QUITTING!\n");
                    goto exit;
                }
            }

            bytesRead = fread(Buffer, 1, BUFFERSIZE, ifp);
            sizeLeft  = bytesRead;
            pBuffer = Buffer;

            while (sizeLeft)
            {
                RMuint32 sizeToRead = sizeLeft;

                sizeLeft = write_data_in_circular_bts_fifo(ctx, pBuffer, sizeLeft);

//                fprintf(stderr, "sizeLeft = %ld sizeToRead = %ld\n", sizeLeft, sizeToRead);

                if (sizeLeft==0)
                    break;
                consume_pictures(ctx);
#ifdef  ENABLE_TIMEOUT
                nTry++;
                if (nTry > 10000)
                {
                    printf("%s: data is not consumed !!!\n", __FUNCTION__);
                    goto exit;
                }
#endif // ENABLE_TIMEOUT
            }

            consume_pictures(ctx);
        }

        printf("%s: EndOfFile %s\n", __FUNCTION__, ctx->szStrFilename);

        printf("-- Polling output FIFO for final frames...\n");

        while (nDone == 0) {
            int num_frames = consume_pictures( ctx );

#if 0
            if (num_frames == 0) {
                loopCount++;
                //usleep( 1000 );
                sleep(2);
            }

            if (loopCount == 8) {
                nDone = 1;
            }
#endif // 0
        }
exit:
        fclose(ifp);
    }
    else
    {
        fprintf(stderr, "ERROR: Unable to open input stream!\n");
    }

    return;
}
#endif // ENABLE_THREADS

static RMstatus close_video_decoder(CONTEXT_PTR ctx)
{
    send_video_command(ctx, VideoCommandStop, VideoStatusStop);

    return RM_OK;
}

#ifndef ENABLE_CURSES
static const char* getDecoderID(RMuint32 id) {
    struct profileEntry *pCurEntry = profileTable;

    while (pCurEntry->szIdent != NULL)
    {
        if (pCurEntry->nProfile ==  (int)id)
        {
            return pCurEntry->szIdent;
        }
        pCurEntry++;    // Advance to next profile entry...
    }

    return "unknown";
}

static void display_context_info(CONTEXT* ctx)
{
    printf("---CONTEXT INFO---\n");
//    DISPLAY_CTX_PTR( uiDRAMPtr );

    printf("%-40s : 0x%08lX\n", "DRAM_BASE" , (RMuint32)DRAM_BASE);
    DISPLAY_CTX_STR( file.sStrFilename.c_str(), "Input stream");
    DISPLAY_CTX_STR( file.sBinFilename.c_str(), "Microcode Binary #0");
//    if (ctx->szBinFilename[1] != 0L)
//        DISPLAY_CTX_STR( szBinFilename[1], "Microcode Binary #1");
    if (!ctx->file.sYUVFilename.empty())
        DISPLAY_CTX_STR( file.sYUVFilename.c_str(), "Capture File")
    DISPLAY_CTX_VAR( DecoderDataSize );
    DISPLAY_CTX_VAR( DecoderContextSize );
    DISPLAY_CTX_VAR( UserDataSize );
    DISPLAY_CTX_VAR( BitstreamFIFOSize );
    DISPLAY_CTX_VAR( PtsFIFOCount );
    DISPLAY_CTX_VAR( InbandFIFOCount );
    DISPLAY_CTX_VAR( ExtraPictureBufferCount );
    DISPLAY_CTX_VAR( NumOfPictures );
    DISPLAY_CTX_STR2( decoderProfile, getDecoderID(ctx->decoderProfile) );
    DISPLAY_CTX_VAR( pvc_tw );
    DISPLAY_CTX_VAR( pvc_th );
    DISPLAY_CTX_VAR( pvc_ts );
    DISPLAY_CTX_PTR( pmBaseAddress );
    DISPLAY_CTX_PTR( dmBaseAddress );
    DISPLAY_CTX_PTR( regBaseAddress );
    DISPLAY_CTX_PTR( pvtdb );
    DISPLAY_CTX_PTR( pvti );
    DISPLAY_CTX_PTR( data_fifo );
    DISPLAY_CTX_PTR( bts_fifo );
    DISPLAY_CTX_PTR( display_fifo );
    DISPLAY_CTX_PTR( user_data_fifo );
    DISPLAY_CTX_VAR( binSize );
    DISPLAY_CTX_VAR( dram_lo );
    DISPLAY_CTX_VAR( dram_hi );

    fflush(stdout);

    return;
}
#endif // ENABLE_CURSES

#ifndef ENABLE_CURSES
void cleanup(int result, void* ptr)
{
    reset_terminal_mode();
}
#endif // ENABLE_CURSES

#ifdef ENABLE_ENV_VARS

#define GET_ENVIRONMENT_VALUE_STR( ctx, member, env )                           \
    {                                                                           \
        const char* sValue = 0L;                                                \
        if ((sValue = getenv( (env) )) != 0L)                                   \
            (ctx)->member = strdup(sValue);                                     \
    }

void update_environment_vars(CONTEXT* pCtx)
{
    const char* sValue = NULL;

//    GET_ENVIRONMENT_VALUE_STR( pCtx, szBinFilename[0], UCODE_0 );
//    GET_ENVIRONMENT_VALUE_STR( pCtx, szBinFilename[1], UCODE_1 );

    sValue = getenv(CODEC_ID);
    if (sValue != NULL) {
        pCtx->decoderProfile = get_profile_id_from_string(sValue);
    }

    return;
}

#endif // ENABLE_ENV_VARS

/**
 *  Initialize application context structure...
 */

void init_context(CONTEXT_PTR ctx) {
//    ctx.symMgr              = new UcodeSymbolMgr;
    video_interface::set_symbol_resolver( &ctx->symMgr );

    /* initialize default values */
    ctx->uiDRAMPtr           = DRAM_BASE;
    ctx->DecoderDataSize	 = DECODER_DATA_SIZE;        // hard-coded (should be calculated)
    ctx->DecoderContextSize  = DECODER_CTX_SIZE;         // hard-coded (should be calculated)
    ctx->BitstreamFIFOSize   = (2 * 1024 * 1024);
    ctx->PtsFIFOCount        = 512;
    ctx->InbandFIFOCount	 = 512;
    ctx->NumOfPictures       = PICTURE_COUNT;
    ctx->decoderProfile      = VideoProfileMPEG2;        // default to MPEG2 stream

    set_tile_dimensions( ctx.get(), RMTILE_WIDTH_SHIFT, RMTILE_HEIGHT_SHIFT );

    ctx->soc_arch            = SOC_TANGO;
    ctx->reset_control       = G2L_ANOTHER_RESET_CONTROL;

    /* Set default base addresses */
    ctx->memBaseAddress      = MEM_BASE_mpeg_engine_0;
    ctx->pmBaseAddress       = PMEM_BASE_mpeg_engine_0;
    ctx->dmBaseAddress       = DMEM_BASE_mpeg_engine_0;
    ctx->regBaseAddress      = REG_BASE_mpeg_engine_0;
    ctx->dramBaseAddress     = DRAM_BASE;

    ctx->storage_format              = 0;
    ctx->luma_nb_comp_per_sample     = 1;
    ctx->chroma_nb_comp_per_sample   = 2;

    //ctx->application_state   = APP_INITIALIZING;

    RMDBGLOG((LOCALDBG, "Tile Width Shift %ld\n", RMTILE_WIDTH_SHIFT));
    RMDBGLOG((LOCALDBG, "Tile Height Shift %ld\n", RMTILE_HEIGHT_SHIFT));

    ctx->dump_y_uv                   = FALSE;

#ifdef ENABLE_THREADS
    ctx->fifoFillRunning             = FALSE;
    ctx->fifoEmptyRunning            = FALSE;
    ctx->terminateThreads            = FALSE;

    pthread_mutex_init(&ctx->contextMutex, NULL);
    pthread_mutex_init(&ctx->displayMutex, NULL);
#endif // ENABLE_THREADS

#ifdef ENABLE_CURSES
    /* Allocate User Interface context */
//    ctx->pUIContext = (UI_CONTEXT*)malloc(sizeof(UI_CONTEXT));
    ctx->pUIContext = new UI_CONTEXT;
    assert(ctx->pUIContext != 0L);
    memset(ctx->pUIContext, 0, sizeof(UI_CONTEXT));
#endif // ENABLE_CURSES

#ifdef  ENABLE_ENV_VARS
    update_environment_vars( ctx.get() );
#endif // ENABLE_ENV_VARS

    return;
}

/**
 *  Main entry point.
 */

int main(int argc, char *argv[])
{
    CONTEXT_PTR     shared_context = std::make_shared<CONTEXT>();

    open_log_files("messages.txt", "errors.txt");

    init_context( shared_context );

    /* parse commandline arguments */
    if (parse_options(shared_context, "interface2", argc, argv) != RM_OK)
    {
        fprintf(stderr, "ERROR: Incorrect parameters!\n");
        release_context( shared_context );
        return -1;
    }

#ifdef ENABLE_CURSES
    init_user_interface(shared_context->pUIContext);
#else
    set_terminal_mode();
    on_exit( cleanup, 0L);
#endif // ENABLE_CURSES

#ifdef ENABLE_CURSES

    shared_context->pUIContext->state = APP_INITIALIZING;
    update_user_interface(shared_context->pUIContext);

#endif // ENABLE_CURSES

    if (open_gbus(shared_context /*, chipnum */) == RM_ERROR)
    {
        fprintf(stderr, "ERROR: Unable to obtain gbus pointer!\n");
        return -1;
    }

    /* Stop the both video engines */
    do_stop_engine(shared_context);

    if (load_video_ucode(shared_context) != RM_OK)
        goto clean_exit;

    /* Start the video engine */
    do_start_engine(shared_context);
    init_video_engine(shared_context);
    open_video_decoder(shared_context);

#ifndef ENABLE_CURSES
    display_context_info(shared_context.get());
#endif // ENABLE_CURSES

    set_video_codec(shared_context);

    /* Send play command */
    send_video_command(shared_context, VideoCommandPlayFwd, VideoStatusPlayFwd);

#ifdef ENABLE_THREADS
    /* handle threaded code */
    launch_threads(shared_context);
#else
    send_data(shared_context.get());
#endif // ENABLE_THREADS

    close_video_decoder(shared_context);

clean_exit:
#ifdef ENABLE_CURSES
    uninit_user_interface(shared_context->pUIContext);
#endif // ENABLE_CURSES

    close_gbus(shared_context);
    release_context(shared_context);

    close_log_files();

//    delete ctx;

    return 0;
}


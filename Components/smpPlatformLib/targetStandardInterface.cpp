#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#define ALLOW_OS_CODE
#include "targetEngine.h"
#include "targetInterfaceBase.h"
#include "targetStandardInterface.h"
#include "video_utils.h"
#include "struct_utils.h"
#include "gbus_fifo.h"
#include "gbus_fifo_eraser.h"
#include "gbus_packet_fifo.h"
#include "gbus_packet_fifo_eraser.h"
#include "file_utils.h"
#include "string_utils.h"
#include "gbus.h"
#include "gbus_utils.h"
#include "misc_utils.h"
#include "targetOptionsManager.h"
#include "libOptions.h"

#ifdef _DEBUG
#define LOCALDBG    ENABLE
#else
#define LOCALDBG    DISABLE
#endif // _DEBUG

#define ENABLE_EXTRA_DEBUG_INFO 1

#define COMMAND_TIMEOUT         0xffffffff

#define INIT_STRUCT( var, str )                                                 \
    nStructSize = pStructDB->get_structure( (str) )->size();                    \
    (var)       = pAlloc->alloc(targetAllocator::ALLOC_DRAM, nStructSize);      \
                                                                                \
    for (i = 0 ; i < nStructSize/4 ; i++) {                                     \
        pIF->get_gbusptr()->gbus_write_uint32((var) + 4 * i, 0);                \
    }


using namespace video_utils;

typedef std::lock_guard<std::mutex>     mutex_guard;


std::ostream& operator<<(std::ostream& os, const targetStandardIFTask& task)
{
    os << "Input stream : " << task.inputStreamName <<
        " Output stream : " << task.outputYUVName <<
        " Task Database : " << std::hex << "0x" << task.pvtdb <<
        " Task Interface : " << std::hex << "0x" << task.pvti;

    return os;
}

targetStandardIFTask::targetStandardIFTask()
:   bValid(false),
    pChroma(nullptr),
    pLuma(nullptr),
    picture_count(0),
    picbuf_address(0),
    luma_address(0),
    chroma_address(0),
    save_time(0.0),
    yuvfp(nullptr),
    total_frames(0),
    dump_y_uv(false),
    total_bytes_read(0),
    task_state(TASK_UNINITIALIZED),
    task_substate(TASK_SUBSTATE_UNKNOWN),
    pIF(nullptr),
    fifoFillRunning(false),
    fifoEmptyRunning(false),
    terminateThreads(false)
{
    // ctor
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));
    update_output_stats();

}

targetStandardIFTask::targetStandardIFTask(targetStdIfParms& parms)
:   bValid(false),
    pChroma(nullptr),
    pLuma(nullptr),
    picture_count(0),
    picbuf_address(0),
    luma_address(0),
    chroma_address(0),
    save_time(0.0),
    yuvfp(nullptr),
    total_frames(0),
    dump_y_uv(false),
    total_bytes_read(0),
    task_state(TASK_UNINITIALIZED),
    task_substate(TASK_SUBSTATE_UNKNOWN),
    pIF(nullptr),
    fifoFillRunning(false),
    fifoEmptyRunning(false),
    terminateThreads(false)
{
    // ctor
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    pAlloc          = parms.pAlloc;
    pIF             = parms.pIF;

    inputStreamName = parms.sInputStreamName;
    outputYUVName   = parms.sOutputYUVName;
    decoderProfile  = parms.nProfile;
    dump_y_uv       = parms.bDumpUntiled;
    dumpPath        = parms.sDumpPath;
    sXmlPath        = parms.sXmlPath;

    init_parameters();

	return;
}

bool targetStandardIFTask::start() {
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    init_video_engine();
    open_video_decoder();

    set_video_codec();
    send_video_command( VideoCommandPlayFwd, VideoStatusPlayFwd );

  //  task_state = TASK_INITIALIZED;

    update_output_stats();
    launch_threads();

    return true;
}
/**
 *
 */

targetStandardIFTask::~targetStandardIFTask()
{
    // dtor
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    stop();
}

/**
 *  Return the tasks state.
 */

void targetStandardIFTask::get_state(taskState* pState, taskSubstate* pSubstate)
{
    mutex_guard lock(stateMutex);

    if (pState != nullptr)
        *pState = task_state;
    if (pSubstate != nullptr)
        *pSubstate = task_substate;

    return;
}

/**
 *  Initialize decoding parameters...
 */

void targetStandardIFTask::init_parameters()
{
    std::string                 sOptionsXml;

    sOptionsXml    = sXmlPath + "/" + PLATFORM_OPTION_FILE;
    targetOptionsManager        mgr(sOptionsXml);
    TARGET_OPTIONS_REQ          req;

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    /* Fill in request structure with pointers to 32bit integers */
    req.ifVersion           = &ifVersion;
    req.decoderDataSize     = &DecoderDataSize;
    req.decoderContextSize  = &DecoderContextSize;
    req.bitstreamFIFOSize   = &BitstreamFIFOSize;
    req.numPictures         = &NumOfPictures;

    mgr.get_options(pIF->get_target()->get_chipid(), req);

    PtsFIFOCount                = 512;
    InbandFIFOCount             = 512;
    soc_arch                    = SOC_TANGO;
    storage_format              = 0;
    luma_nb_comp_per_sample     = 1;
    chroma_nb_comp_per_sample   = 2;
    UserDataSize                = 0;
    ExtraPictureBufferCount     = 0;

    set_tile_dimensions( pIF->get_target()->get_chipid() );
//    set_tile_dimensions( pIF->get_engine()->get_parent()->get_parent()->get_chip_id() );

    //m_pAlloc[0]->set_tile_dimensions( )
}

/**
 *
 */

RMstatus targetStandardIFTask::init_video_engine()
{
    RMuint32            memBase = pIF->get_engine()->get_pmBase();
    RMuint32            Address = 0,
                        Size = 0;
    RMuint32            uiDRAMPtr = pAlloc->dramPtr();

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    video_get_scheduler_memory( pIF, memBase, &Address, &Size );

    if ((Address == 0) && Size) {
        Address = (uiDRAMPtr & 0xfffffffc) + 4; // align by 4
        video_set_scheduler_memory(pIF, memBase, Address, Size);
        Size += 4;
        pAlloc->alloc(targetAllocator::ALLOC_DRAM, Size);
#ifdef _DEBUG
        pAlloc->dump(std::cerr);
#endif // _DEBUG
    }

    return RM_OK;
}

/**
 *
 */

RMstatus targetStandardIFTask::open_video_decoder()
{
    RMstatus                nStatus     = RM_ERROR;
    structure_database*     pStructDB   = pIF->get_structdb();
    RMuint32                nStructSize = 0L;
    RMuint32                i           = 0;
    RMstatus 		        err __attribute__ ((unused))         = RM_OK;
    RMuint32                dramPtr     = 0;
    RMuint32                video_bts_fifo,
                            video_pts_fifo;
    RMuint32                fifoEraserSize = 0;

//    assert(pStructDB != nullptr);
    assert(pIF != nullptr);

#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("entering open_video_decoder");
#endif // ENABLE_GBUS_LOGGER

    pAlloc->alloc(targetAllocator::ALLOC_DRAM, 4);

    INIT_STRUCT( pvtdb, "video_task_data_base" );
    INIT_STRUCT( pvti,  "video_task_interface" );

    RMDBGLOG((LOCALDBG, "pvtdb = 0x%08X\n", pvtdb));
    RMDBGLOG((LOCALDBG, "pvti  = 0x%08X\n", pvti));

    video_set_display_error_threshold(pIF, pvti, 0);
    video_set_anchor_propagation_parms(pIF, pvti, 500, 13);

    /* Set pvti pointer in DRAM */
    video_set_vti_pointer(pIF, pvtdb, pvti);
    /* Set pvtb in DMEM */
    video_set_vtdb_pointer(pIF,
                           pIF->get_engine()->get_pmBase(),
                           0,
                           pvtdb);

//    RMuint32 tempVal = RM_NEXT_TILE_ALIGN(pAlloc->dramPtr());
//    dramPtr = tempVal;
    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM|targetAllocator::ALLOC_TILEALIGN, DecoderDataSize);

    if (ifVersion == 1) {
        err = video_set_data_context_buffer_v1(pIF, pvti, dramPtr,
                                               DecoderDataSize, DecoderContextSize);
    } else {
        err = video_set_data_context_buffer_v2(pIF, pvti, dramPtr,
                                               DecoderDataSize, DecoderContextSize);
    }

    struct_utils::write_structure_member(pIF, pvti, "video_task_interface", "MiscFlags", 1);

    fifoEraserSize = struct_utils::get_structure_size(pIF, "gbus_fifo_eraser");

    video_bts_fifo = pAlloc->alloc(targetAllocator::ALLOC_DRAM|targetAllocator::ALLOC_PAGEALIGN, fifoEraserSize);
    RMDBGLOG((LOCALDBG, "video_bts_fifo = %08X\n", video_bts_fifo));
    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM|targetAllocator::ALLOC_PAGEALIGN, BitstreamFIFOSize);
    RMDBGLOG((LOCALDBG, "dramPtr = %08X\n", dramPtr));

    gbus_fifo_eraser_open( pIF->get_gbusptr(), dramPtr, BitstreamFIFOSize, video_bts_fifo );
    err = video_set_bts_fifo_pointer( pIF, pvtdb, video_bts_fifo );

    bts_fifo = video_bts_fifo;

    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM, (RMuint32)(PtsFIFOCount * VPTS_FIFO_ENTRY_SIZE));

    err = video_get_pts_fifo(pIF, pvtdb, &video_pts_fifo);
    err = video_open_pts_fifo(pIF, pvtdb, dramPtr, PtsFIFOCount);

    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM,
                            (RMuint32)(InbandFIFOCount * sizeof(struct MicrocodeInbandCommand)));
    video_open_inband_fifo(pIF, pvtdb, dramPtr, InbandFIFOCount);

    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM,
                            (RMuint32)(InbandFIFOCount * sizeof(struct MicrocodeInbandParams)));
    inband_params_address = dramPtr;

    RMDBGLOG((LOCALDBG, "inband_params_address = %08X\n", inband_params_address));
    for (i = 0 ; i < InbandFIFOCount * sizeof(struct MicrocodeInbandParams)/sizeof(RMuint32) ; i++)
    {
        pIF->get_gbusptr()->gbus_write_uint32( inband_params_address + (4*i), 0);
    }

    video_set_inband_param_addr(pIF, pvtdb, inband_params_address);

    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM, (sizeof(RMuint32) * (NumOfPictures + 1)));
    err = video_get_display_fifo(pIF, pvtdb, &display_fifo);

    //gbus_entry_fifo_open(pContext->pgbus, unprotected_ptr, pContext->NumOfPictures + 1, pContext->display_fifo);
    gbus_entry_fifo_open( pIF->get_gbusptr(), dramPtr, (NumOfPictures + 1), display_fifo );

    //clear the pointers to picture buffers
    for ( i =0; i < NumOfPictures + 1; i++) {
        pIF->get_gbusptr()->gbus_write_uint32(dramPtr + (4* i), 0);
    }

    video_get_irq_info(pIF, pvti, &event_table_pointer);

    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM, UserDataSize);

    /* initialize user data fifo - the container and data are in DRAM */
    err = video_get_user_data_fifo(pIF, pvtdb, &user_data_fifo);
    err = video_open_user_data_fifo(pIF, pvtdb, dramPtr, UserDataSize);

    if (UserDataSize > 0)
    {
        /* initialize the internal user_data input and helper fifo  */
//        gbus_fifo_eraser_open(pContext->pgbus, unprotected_ptr, pContext->UserDataSize, (RMuint32) &(((struct video_task_data_base *)pContext->pvtdb)->user_data_in_fifo));
//        unprotected_ptr += pContext->UserDataSize;
//        gbus_entry_fifo_eraser_open(pContext->pgbus, unprotected_ptr, pContext->UserDataSize / 16, (RMuint32) &(((struct video_task_data_base *)pContext->pvtdb)->user_data_info_fifo));
//        unprotected_ptr += (pContext->UserDataSize / 16)  * (2*sizeof(RMuint32));
        dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM, (UserDataSize/16) * (2*sizeof(RMuint32)));
    }
    else
    {
        RMuint32 gbusAddr;

        gbusAddr = struct_utils::resolve_offset(pIF->get_structdb(), pvtdb, "video_task_data_base", "user_data_in_fifo");
        /* if user data is not required initialize the start address to 0 for the internal user_data input and helper fifo  */
        gbus_fifo_eraser_open(pIF->get_gbusptr(), 0, 0, gbusAddr);
        gbusAddr = struct_utils::resolve_offset(pIF->get_structdb(), pvtdb, "video_task_data_base", "user_data_info_fifo");
        gbus_entry_fifo_eraser_open(pIF->get_gbusptr(), 0, 0, gbusAddr);
    }

    dramPtr =  pAlloc->alloc(targetAllocator::ALLOC_DRAM, DECODE_ERROR_ENTRIES *
                              struct_utils::get_structure_size(pIF, "EMhwlibVideoDecoder_DecodeError"));
//    err = video_open_error_code_fifo(pContext->pgbus, (struct video_task_data_base *)pContext->pvtdb, unprotected_ptr, DECODE_ERROR_ENTRIES);//pValueIn->ErrorCodeCount);
    err = video_open_error_code_fifo(pIF, pvtdb, dramPtr, DECODE_ERROR_ENTRIES);

//    unprotected_ptr += DECODE_ERROR_ENTRIES * sizeof(struct EMhwlibVideoDecoder_DecodeError);
    dramPtr =  pAlloc->alloc(targetAllocator::ALLOC_DRAM, 0);
  //  video_set_extra_pictures(pContext->pgbus, (struct video_task_interface *)pContext->pvti, pContext->ExtraPictureBufferCount);
    video_set_extra_pictures(pIF, pvti, ExtraPictureBufferCount);

#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("exiting open_video_decoder");
#endif // ENABLE_GBUS_LOGGER

    return nStatus;
}

typedef struct {
    std::string sID;
    RMuint32    tileW;
    RMuint32    tileH;
} tileDef;

static tileDef  chipTileSizes[] = {
    { "8756", 8, 5, },
    { "8758", 8, 5, },
    { "8760", 9, 5, },
};

/**
 *  Set tile dimensions by chip ID...
 */

bool targetStandardIFTask::set_tile_dimensions(std::string sChipId)
{
    RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__, sChipId.c_str()));

    for (size_t i = 0 ; i < sizeof(chipTileSizes)/sizeof(tileDef) ; i++) {
        if (sChipId == chipTileSizes[i].sID) {
            set_tile_dimensions( chipTileSizes[i].tileW, chipTileSizes[i].tileH );
            return true;
        }
    }

    set_tile_dimensions( 8, 5 );

    return false;
}

/**
 *  Set the tile dimensions tsw x tsh...
 */

void targetStandardIFTask::set_tile_dimensions(RMuint32 tsw, RMuint32 tsh)
{
    RMDBGLOG((LOCALDBG, "%s(%ld, %ld)\n", __PRETTY_FUNCTION__, tsw, tsh));

    tile_width_l2       = tsw;
    tile_height_l2      = tsh;
    pvc_tw              = (1 << tsw);
    pvc_th              = (1 << tsh);
    pvc_ts              = pvc_tw * pvc_th;

    pAlloc->set_tile_size( tsw, tsh );

    return;
}


/**
 *
 */

RMstatus targetStandardIFTask::set_video_codec()
{
#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("entering set_video_codec");
#endif // ENABLE_GBUS_LOGGER

    send_video_command( VideoCommandUninit,  VideoStatusUninit );

    video_set_profile(pIF, pvti, decoderProfile );

    send_video_command( VideoCommandInit,    VideoStatusStop );

#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("exiting set_video_codec");
#endif // ENABLE_GBUS_LOGGER

    return RM_OK;
}


RMstatus targetStandardIFTask::send_video_command(enum VideoCommand cmd,
                                                  enum VideoStatus stat)
{
    RMstatus            result = RM_ERROR;
    enum VideoStatus    VideoDecoderStatus;
    RMuint32            started;

#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("entering send_video_command");
#endif // ENABLE_GBUS_LOGGER

    update_task_state(cmd, VideoStatusPending);

    video_set_command(pIF, pvti, cmd );

    started = gbus_utils::gbus_time_us(pIF->get_gbusptr());

    while (1) {
        video_get_status(pIF, pvti, &VideoDecoderStatus);

        //printf("-- status %d\n", (int) VideoDecoderStatus);

        if (VideoDecoderStatus == stat) {
            result = RM_OK;
            break;
        }

        if (gbus_utils::gbus_time_delta(started, gbus_utils::gbus_time_us(pIF->get_gbusptr())) > COMMAND_TIMEOUT) {
            RMDBGLOG((DISABLE, "-- TIMEOUT (command not received) --\n"));
            result = RM_PENDING;
            break;
        }
        //usleep(1000);
    }

    update_task_state(VideoCommandNoCmd, stat);

#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("exiting send_video_command");
#endif // ENABLE_GBUS_LOGGER

    return result;
}

/**
 *  Launch the background threads, use std::thread unless USE_PTHREADS is defined.
 */

bool targetStandardIFTask::launch_threads()
{
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    fifoFillThread  = std::thread( &targetStandardIFTask::fifoFillThreadFunc, this );
    fifoEmptyThread = std::thread( &targetStandardIFTask::fifoEmptyThreadFunc, this );

#if 0
    /* Wait for both threads to enter running state */
    while ((fifoFillRunning == false) || (fifoEmptyRunning == false)) {
        usleep(50);
    }

    task_state = TASK_PLAYING;
#endif // 0

    RMDBGLOG((LOCALDBG, "-- threads running!\n"));

    return true;
}

/**
 *  Thread responsible for filling the bitstream FIFO.
 */

void* targetStandardIFTask::fifoFillThreadFunc()
{
    FILE*           ifp                 = nullptr;
    unsigned char   Buffer[XFER_BUFFERSIZE];
    RMuint32        bytesRead           = 0L,
                    sizeLeft            = 0L;
    unsigned char*  pBuffer             = nullptr;

    fifoFillRunning = true;

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    /* Open the input stream */
    if ((ifp = fopen(inputStreamName.c_str(), "r")) != 0) {

        while (!feof(ifp)) {
            bytesRead = fread(Buffer, 1, XFER_BUFFERSIZE, ifp);
            sizeLeft  = bytesRead;
            pBuffer   = Buffer;

            while (sizeLeft && (terminateThreads == false)) {
//                RMuint32 sizeToRead = sizeLeft;

                sizeLeft = write_data_in_circular_bts_fifo( pBuffer, sizeLeft );

//                fprintf(stderr, "sizeLeft = %ld sizeToRead = %ld\n", sizeLeft, sizeToRead);

                if (sizeLeft==0)
                    break;

                usleep(50000);
            }

            if (terminateThreads == true) {
                RMDBGLOG((LOCALDBG, "-- Terminating fifoFillThread thread!\n"));
                break;
            }

            total_bytes_read += bytesRead;

            update_input_stats();

            usleep(50000);
        }

        fclose(ifp);

//      printf("%s: EndOfFile %s\n", __FUNCTION__, ctx->szStrFilename);

    } else {
        RMDBGLOG((LOCALDBG, "ERROR: Unable to open input stream!\n"));
    }

    RMDBGLOG((LOCALDBG, "-- exiting fifoFillThread()\n"));
    fifoFillRunning = false;

    return (void*)nullptr;
}

/**
 *  Thread responsible for emptying the display FIFO.
 */

void* targetStandardIFTask::fifoEmptyThreadFunc()
{
//  controlInterface*       pIF         = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    RMuint32                rd          = 0,
                            wr          = 0,
                            fifo_base   = 0,
                            fifo_size   = 0;
    RMuint32                entry_size  = 4; // address for the picture info
    RMuint32                size        = 0,
                            picture_address = 0;

    fifoEmptyRunning = true;

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    if (!outputYUVName.empty()) {
        RMDBGLOG((LOCALDBG, "Opening YUV file %s...\n", outputYUVName.c_str()));
        yuvfp = fopen(outputYUVName.c_str(), "w");
    } else {
        RMDBGLOG((LOCALDBG, "No YUV capture file specified!\n"));
    }

    while (terminateThreads == false) {
        gbus_fifo_get_pointer(pIF->get_gbusptr(), (struct gbus_fifo*)display_fifo,
                              &fifo_base, &fifo_size, &rd, &wr);

        if ( wr >= rd ){
            /* fullness in one chunck */
            size = wr - rd;
        } else if (wr != rd) {
            /* fullness in two chuncks because of circular fifo. */
            size = fifo_size - rd + wr;
        }

        while (size && (terminateThreads == false)) {
            picture_address = pIF->get_gbusptr()->gbus_read_uint32( fifo_base + (rd*entry_size) );

            process_picture( picture_address );

            // advance read pointer
            rd = (rd + 1) % fifo_size;
            size--;

            // release pictures
            struct_utils::write_structure_member(pIF, picture_address, "VideoMicrocodePicture", "picture_display_status", 0);
            total_frames++;

            // update FIFO read pointer
            gbus_fifo_incr_read_ptr(pIF->get_gbusptr(), (struct gbus_fifo*)display_fifo, 1);

            outputStatMutex.lock();
            oStats.dispFifo.uiFifoCont  = display_fifo;
            oStats.dispFifo.uiFifoPtr   = fifo_base;
            oStats.dispFifo.uiFifoSize  = fifo_size;
            oStats.dispFifo.uiFifoRdPtr = rd;
            oStats.dispFifo.uiFifoWrPtr = wr;
            outputStatMutex.unlock();

            update_output_stats();
        }

        usleep(50000);
    }

    RMDBGLOG((LOCALDBG, "-- exiting fifoEmptyThread()\n"));

    usleep(5000);
    fifoEmptyRunning = false;

    return (void*)nullptr;
}

/**
 *  Write data into the bitstream FIFO.
 *
 *  Function to write data into a circular FIFO including wrap-around condition.
 */

RMuint32 targetStandardIFTask::write_data_in_circular_bts_fifo(RMuint8 *pBuf,
                                                                  RMuint32 sizeToSend)
{
//    controlInterface*       pIF         = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    GBUS_PTR                pGbus       = pIF->get_gbusptr();
	RMuint32                rd, wr,
                            fifo_base, fifo_size;
	RMuint32                size, sizeLeft;

    RMDBGLOG((LOCALDBG, "%s(%p, %d)\n", __PRETTY_FUNCTION__, pBuf, sizeToSend));

    gbus_fifo_get_pointer(pGbus, (struct gbus_fifo*)bts_fifo, &fifo_base,
                          &fifo_size, &rd, &wr);

    RMDBGLOG((LOCALDBG, "FIFO @ 0x%08lX START 0x%08lX SIZE 0x%08lX RD = 0x%08lX WR = 0x%08lX\n",
            (unsigned long)bts_fifo, fifo_base, fifo_size, rd, wr));

    inputStatMutex.lock();
    iStats.btsFifo.uiFifoCont   = bts_fifo;
    iStats.btsFifo.uiFifoPtr    = fifo_base;
    iStats.btsFifo.uiFifoSize   = fifo_size;
    iStats.btsFifo.uiFifoRdPtr  = rd;
    iStats.btsFifo.uiFifoWrPtr  = wr;
    inputStatMutex.unlock();

	if ( rd > wr ) {
		/* emptiness in one chunk */
		RMuint32 empty;
		empty = rd - wr - 1;
		if (empty < sizeToSend)
			return sizeToSend;

		pGbus->gbus_write_data8(fifo_base + wr, pBuf, sizeToSend);
	} else { // rd <= wr
		/* emptiness in two chunks because of circular fifo. */
		RMuint32 empty;
		empty = fifo_size - wr + rd - 1;
		if (empty < sizeToSend)
			return sizeToSend;
		//first chunk
		size = RMmin(fifo_size - wr, sizeToSend);
		pGbus->gbus_write_data8(fifo_base + wr, pBuf, size);

		//second chunk
		sizeLeft = sizeToSend - size;
		if (sizeLeft)
			pGbus->gbus_write_data8(fifo_base, pBuf+size, sizeLeft);
	}

	sizeLeft = 0;
	gbus_fifo_incr_write_ptr(pGbus, (struct gbus_fifo*)bts_fifo, sizeToSend);

    return sizeLeft;
}

/**
 *  Retrieve the rectangle from the picture buffer.
 */

void targetStandardIFTask::READ_PICTURE_BUFFER_RECT(RMuint32 address, std::string sField, struct EMhwlibWindow* pDest) {
    RMuint32 gbusAddr   = 0;
    RMuint32 nSize      = 0;

    gbusAddr = struct_utils::resolve_offset(pIF, address, "VideoMicrocodePicture", sField);
    nSize = struct_utils::get_structure_size(pIF, "EMhwlibWindow");
    pIF->get_gbusptr()->gbus_read_data8(gbusAddr, (RMuint8*)pDest, nSize);

    return;
}

/**
 *  Retrieve a field from the picture buffer structure.
 */

RMuint32 targetStandardIFTask::READ_PICTURE_BUFFER_MEMBER(RMuint32 address, const std::string& member) {
    RMuint32    value = 0L;
    struct_utils::read_structure_member(pIF, address, "VideoMicrocodePicture", member, &value);
    return value;
}

/**
 *  Extract picture from display FIFO.
 */

RMstatus targetStandardIFTask::process_picture(RMuint32 picture_address)
{
    RMstatus            result = RM_ERROR;
    RMuint32            frame_count = 0;
    RMuint32            luma_ttl_wd = 0,
                        chroma_ttl_wd = 0;
    RMuint32            luma_buf_width   = 0,
                        luma_buf_height  = 0,
                        chroma_buf_width = 0,
                        chroma_buf_height = 0;
    RMuint32            luma_size_tile = 0,
                        chroma_size_tile = 0;
    EMhwlibWindow       luma_position_in_buffer,
                        chroma_position_in_buffer;
    time_point          ts1, ts2;
    time_diff           ts3;


    frame_count    = READ_PICTURE_BUFFER_MEMBER(picture_address, "frame_count");
    luma_address   = READ_PICTURE_BUFFER_MEMBER(picture_address, "luma_address");
    chroma_address = READ_PICTURE_BUFFER_MEMBER(picture_address, "chroma_address");
    luma_ttl_wd    = READ_PICTURE_BUFFER_MEMBER(picture_address, "luma_total_width");
    chroma_ttl_wd  = READ_PICTURE_BUFFER_MEMBER(picture_address, "chroma_total_width");

    READ_PICTURE_BUFFER_RECT(picture_address, "luma_position_in_buffer", &luma_position_in_buffer);
    READ_PICTURE_BUFFER_RECT(picture_address, "chroma_position_in_buffer", &chroma_position_in_buffer);

    /* calculate luma buffer size */
    luma_buf_width  = ((luma_position_in_buffer.width + luma_position_in_buffer.x + pvc_tw - 1)/pvc_tw) * pvc_tw;
    luma_buf_height = ((luma_position_in_buffer.height + luma_position_in_buffer.y + pvc_th - 1)/pvc_th) * pvc_th;
    luma_size_tile = (luma_buf_width * luma_buf_height);

    /* calculate chroma buffer size */
    chroma_buf_width  = ((chroma_position_in_buffer.width + chroma_position_in_buffer.x + pvc_tw - 1)/pvc_tw) * pvc_tw;
    chroma_buf_height = ((chroma_position_in_buffer.height + chroma_position_in_buffer.y + pvc_th - 1)/pvc_th) * pvc_th;
    chroma_size_tile = (chroma_buf_width * chroma_buf_height) * 2;

    RMDBGLOG((ENABLE, "Picture Buffer @ 0x%08lx\n", picture_address));
    RMDBGLOG((ENABLE, "Frame Count %d\n", frame_count));
    RMDBGLOG((ENABLE, "Luma Buffer    @ 0x%08lx %ld bytes\n", luma_address, luma_size_tile));
    RMDBGLOG((ENABLE, "Chroma Buffer  @ 0x%08lx %ld bytes\n", chroma_address, chroma_size_tile));

#ifdef ENABLE_EXTRA_DEBUG_INFO
    RMDBGLOG((ENABLE,"frame %ld luma_buffer @ 0x%08lx width 0x%08lx chroma_buffer @ 0x%08lx width 0x%08lx\n",
           frame_count, luma_address, luma_ttl_wd, chroma_address, chroma_ttl_wd));
    RMDBGLOG((ENABLE,"luma tiled dimensions ( %ld x %ld ) chroma tiled dimensions ( %ld x %ld )\n", luma_buf_width,
           luma_buf_height, chroma_buf_width, chroma_buf_height));
    RMDBGLOG((ENABLE,"==> luma position   x %ld y %ld w %ld h %ld size_tile %ld\n", luma_position_in_buffer.x,
           luma_position_in_buffer.y, luma_position_in_buffer.width, luma_position_in_buffer.height, luma_size_tile));
    RMDBGLOG((ENABLE,"==> chroma position x %ld y %ld w %ld h %ld size_tile %ld\n", chroma_position_in_buffer.x,
           chroma_position_in_buffer.y, chroma_position_in_buffer.width, chroma_position_in_buffer.height, chroma_size_tile));
#endif // ENABLE_EXTRA_DEBUG_INFO

    ts1 = std::chrono::high_resolution_clock::now();

    /* If the output file is open, save the frame to the file... */
    if (yuvfp != nullptr) {
        if (pLuma == nullptr) {
            pLuma = (RMuint8*)malloc(luma_size_tile);
        }

        if (pChroma == nullptr) {
            pChroma = (RMuint8*)malloc(chroma_size_tile);
        }

        pIF->get_gbusptr()->gbus_read_data8(luma_address,   pLuma,   luma_size_tile);
        pIF->get_gbusptr()->gbus_read_data8(chroma_address, pChroma, chroma_size_tile);

        if (dump_y_uv == true) {
            std::string sYFname,
                        sUVFname;
            FILE        *yFP = 0,
                        *uvFP = 0;

            get_dump_filenames(frame_count, sYFname, sUVFname);

            RMDBGLOG((LOCALDBG, "Saving frame %ld .Y & .UV to %s.\n", frame_count,
                      dumpPath.c_str()));

            yFP  = fopen(sYFname.c_str(), "wb");
            uvFP = fopen(sUVFname.c_str(), "wb");

            if ((yFP != 0) && (uvFP != 0)) {
                fwrite(pLuma,   1, luma_size_tile,   yFP);
                fwrite(pChroma, 1, chroma_size_tile, uvFP);
            }

            fclose(uvFP);
            fclose(yFP);
        }

        save_frame(frame_count, &luma_position_in_buffer, luma_ttl_wd,
                   &chroma_position_in_buffer, chroma_ttl_wd);

        result = RM_OK;
    }

    ts2 = std::chrono::high_resolution_clock::now();

    picture_w       = luma_position_in_buffer.width;
    picture_h       = luma_position_in_buffer.height;
    picture_count   = frame_count;
    picbuf_address  = picture_address;

    ts3 = ts2 - ts1;
    save_time = ts3.count();

    return result;
}

/**
 *  Generate filenames for Y & UV dump files.
 */

void  targetStandardIFTask::get_dump_filenames(RMuint32 frame_no,
                                                  std::string& sYFilename,
                                                  std::string& sUVFilename)
{
    std::ostringstream  os;

    os << dumpPath << "frame" << std::setfill('0') << std::setw(4) << frame_no << "-tiled.Y";
    sYFilename = os.str();
    os.clear();
    os.str("");
    os << dumpPath << "frame" << std::setfill('0') << std::setw(4) << frame_no << "-tiled.UV";
    sUVFilename = os.str();

    return;
}


/**
 *  Save picture buffer in YUV output file.
 */

void targetStandardIFTask::save_frame(RMuint32 frame_count,
                                        EMhwlibWindow* luma_position_in_buffer, RMuint32 luma_ttl_wd,
                                        EMhwlibWindow* chroma_position_in_buffer, RMuint32 chroma_ttl_wd)
{
    RMuint32 luma_x     = luma_position_in_buffer->x;
//  RMuint32 luma_y     = luma_position_in_buffer->y;
    RMuint32 luma_w     = luma_position_in_buffer->width;
    RMuint32 luma_h     = luma_position_in_buffer->height;
    RMuint32 chroma_x   = chroma_position_in_buffer->x;
//  RMuint32 chroma_y   = chroma_position_in_buffer->y;
    RMuint32 chroma_w   = chroma_position_in_buffer->width;
    RMuint32 chroma_h   = chroma_position_in_buffer->height;
    RMuint32 x,y;
    RMuint32 x_min, x_max, y_min, y_max;
    RMuint32 luma_tile_cnt, chroma_tile_cnt;
    RMuint8  *uPtr      = 0L,
             *vPtr      = 0L;
    RMuint32 i;

    luma_w   = luma_w   * luma_nb_comp_per_sample;
    chroma_w = chroma_w * chroma_nb_comp_per_sample;

    luma_tile_cnt   = (luma_ttl_wd + (1 << tile_width_l2) - 1) / (1<<tile_width_l2);
    chroma_tile_cnt = (chroma_ttl_wd + (1 << tile_width_l2) - 1) / ( 1<<tile_width_l2);

    y_min = 0;
    y_max = luma_h;
    x_min = luma_x;
    x_max = luma_w+luma_x;

    for (y = y_min ; y < y_max ; y++) {
        for (x = x_min ; x < x_max ; x++) {
            RMuint8*    pData = pLuma + offset_address(soc_arch,
                                                       tile_width_l2,
                                                       tile_height_l2,
                                                       x, y,
                                                       luma_tile_cnt, 1, 1);
            fwrite(pData, 1, 1, yuvfp);
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
            RMuint8*    pData = pChroma + offset_address(soc_arch,
                                                         tile_width_l2,
                                                         tile_height_l2,
                                                         x, y,
                                                         chroma_tile_cnt, 1, 1);
            uPtr[i] = pData[0];
            vPtr[i] = pData[1];
        }
    }

    fwrite(uPtr, (chroma_w * chroma_h)/2, 1, yuvfp);
    fwrite(vPtr, (chroma_w * chroma_h)/2, 1, yuvfp);

    free( vPtr );
    free( uPtr );
}

/**
 *
 */

void targetStandardIFTask::stop_threads()
{
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    terminateThreads = true;

    fifoFillThread.join();
    fifoEmptyThread.join();

    return;
}

/**
 *  Stop playback.
 */

bool targetStandardIFTask::stop() {
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    if (task_state == TASK_PLAYING) {
        stop_threads();
        send_video_command(VideoCommandStop, VideoStatusStop);
    }

    return true;
}

/**
 *  Update input statistics block, locking mutex...
 */

void targetStandardIFTask::update_input_stats()
{
    mutex_guard guard(inputStatMutex);

    iStats.sInputFile   = inputStreamName;
    iStats.profile      = decoderProfile;
    iStats.bytesRead    = total_bytes_read;
    iStats.pvtdb        = pvtdb;
    iStats.pvti         = pvti;

    return;
}

/**
 *  Update the output statistics block, locking mutex...
 */

void targetStandardIFTask::update_output_stats()
{
    mutex_guard guard(outputStatMutex);

    oStats.bSavingYUV        = (yuvfp != nullptr)?true:false;
    oStats.sYUVFile          = outputYUVName;
    oStats.pic_address       = picbuf_address;
    oStats.pic_luma_buffer   = luma_address;
    oStats.pic_chroma_buffer = chroma_address;
    oStats.pic_width         = picture_w;
    oStats.pic_height        = picture_h;
    oStats.save_time         = save_time;
    oStats.frame_count       = picture_count;

    return;
}

/**
 *  Get the output stats from the task.
 */

bool targetStandardIFTask::get_output_stats(outputStats& stats) const
{
    mutex_guard guard(inputStatMutex);

    stats = oStats;

    return true;
}

/**
 *  Get the input stats from the task.
 */

bool targetStandardIFTask::get_input_stats(inputStats& stats) const
{
    mutex_guard guard(inputStatMutex);

    stats = iStats;

    return true;
}

void targetStandardIFTask::set_state(taskState state, taskSubstate subState) {
    mutex_guard     lock(stateMutex);

    task_state      = state;
    task_substate   = subState;

    return;
}

void targetStandardIFTask::update_task_state(VideoCommand command, VideoStatus status) {
    taskSubstate    subState = TASK_SUBSTATE_UNKNOWN;
    taskState       State = TASK_COMMAND_PENDING;

    std::string sName;

    if (command != VideoCommandNoCmd) {
        switch (command) {
            case VideoCommandUninit:
                sName = "VideoCommandUninit";
                subState = TASK_SUBSTATE_SENT_UNINIT;
                break;

            case VideoCommandInit:
                sName = "VideoCommandInit";
                subState = TASK_SUBSTATE_SENT_INIT;
                break;

            case VideoCommandStop:
                sName = "VideoCommandStop";
                subState = TASK_SUBSTATE_SENT_STOP;
                break;

            case VideoCommandPlayFwd:
                sName = "VideoCommandPlayFwd";
                subState = TASK_SUBSTATE_SENT_PLAY;
                break;
            default:
                sName = "Invalid command";
                subState = TASK_SUBSTATE_UNKNOWN;
                break;
        }
//      printf("Sent %s\n", sName.c_str());
    } else if (status != VideoStatusPending) {
        switch (status) {
            case VideoStatusUninit:
                sName = "VideoStatusUninit";
                State       = TASK_INITIALIZED;
                subState    = TASK_SUBSTATE_UNINIT;
                break;

            case VideoStatusStop:
                sName       = "VideoStatusStop";
                State       = TASK_STOPPED;
                subState    = TASK_SUBSTATE_STOP;
                break;

            case VideoStatusPlayFwd:
                sName       = "VideoStatusPlayFwd";
                State       = TASK_PLAYING;
                subState    = TASK_SUBSTATE_PLAY;
                break;

            default:
                sName = "Invalid command";
                subState = TASK_SUBSTATE_UNKNOWN;
                break;
        }
//      printf("Received %s\n", sName.c_str());
    }

    set_state(State, subState);

    return;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



/**
 *  Object represents the standard microcode interface.
 */

targetStandardInterface::targetStandardInterface(TARGET_ENGINE_PTR pEngine)
:   targetInterfaceBase(pEngine),
    bValid(false),
    ifState(IF_UNINITIALIZED)
{
    // ctor
    RMuint32 offset = 0;
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    pEngine->get_ucode_offset(nullptr, &offset);

    init_parameters();

    m_pAlloc[0]->alloc(targetAllocator::ALLOC_DRAM, offset);

#ifdef _DEBUG
    m_pAlloc[0]->dump(std::cerr);
#endif // _DEBUG

    ifState = IF_INITIALIZED;
}

/**
 *
 */

targetStandardInterface::~targetStandardInterface()
{
    // dtor
    if (ifState == IF_PLAYING) {
        stop();
    }

    for (size_t i = 0 ; i < MAX_TASK_COUNT ; i++) {
        if (tasks[i]) {
            targetStandardIFTask::taskState state;
            targetStandardIFTask::taskSubstate substate;

            tasks[i]->get_state(&state, &substate);

            if (state == targetStandardIFTask::TASK_STOPPED) {
                // release the task object...
                tasks[i].reset();
            }
        }
    }

    clear_scheduler_data();
}

#ifdef _DEBUG

/**
 *  Display interface state...
 */

void targetStandardInterface::debug_state(std::ostream& os)
{
    os << "Task list" << std::endl;

    for (size_t i = 0 ; i < MAX_TASK_COUNT ; i++) {
        os << "Task # " << std::dec << std::setw(3) << i << " : ";

        if (tasks[i]) {
            os << *(tasks[i]) << std::endl;
        } else {
            os << "Not initialized" << std::endl;
        }
    }
}

#endif // _DEBUG

/**
 *  Set dump flag and path...
 */

void targetStandardInterface::enable_dump(const std::string& sPath)
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...
    RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__, sPath.c_str()));

    dump_y_uv = true;
    dumpPath  = sPath;

    if (!dumpPath.empty() && *dumpPath.rbegin() != '/')
        dumpPath += '/';

    return;
}

/**
 *  Clear dump flag...
 */

void targetStandardInterface::disable_dump()
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...
    RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__));

    dump_y_uv = false;

    return;
}

/**
 *  Return dump flag...
 */

bool targetStandardInterface::get_dump_info(std::string& sPath)
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...
    RMDBGLOG((LOCALDBG, "%s(%s)\n", __PRETTY_FUNCTION__));

    sPath = dumpPath;

    return dump_y_uv;
}

/**
 *  Play the stream...
 */

bool targetStandardInterface::play_stream(const std::string& sInputStreamName,
                                          const std::string& sOutputYUVName,
                                          const std::string& sProfile,
                                          RMuint32           taskID)
{
    RMuint32 nProfile = VideoProfileMPEG2;
    RMDBGLOG((LOCALDBG, "%s(%s, %s, %s)\n", __PRETTY_FUNCTION__,
              sInputStreamName.c_str(), sOutputYUVName.c_str(),
              sProfile.c_str()));

    if ((nProfile = get_profile_id_from_string(sProfile)) == (RMuint32)-1) {
        RMDBGLOG((LOCALDBG, "-- invalid profile [%s]!\n", sProfile.c_str()));
        return false;
    }

    return play_stream(sInputStreamName, sOutputYUVName, nProfile, taskID);
}

bool targetStandardInterface::play_stream(const std::string& sInputStreamName,
                                          const std::string& sOutputYUVName,
                                          RMuint32 profile,
                                          RMuint32 taskID)
{
    bool bRes = false;
    RMDBGLOG((LOCALDBG, "%s(%s, %s, %d, %d)\n", __PRETTY_FUNCTION__,
              sInputStreamName.c_str(), sOutputYUVName.c_str(), profile, taskID));

    if (!tasks[taskID]) {
        std::thread     playThread(&targetStandardInterface::_play_stream, this,
                                   sInputStreamName, sOutputYUVName, profile, taskID);

        playThread.detach();
        bRes = true;
    } else {
        targetStandardIFTask::taskState state;
        targetStandardIFTask::taskSubstate substate;

        tasks[taskID]->get_state(&state, &substate);

        RMDBGLOG((LOCALDBG, "ERROR: Task #%d is in state %d substate %d...\n",
                  (int)state, (int)substate));
    }

    return bRes;
}

/**
 *  Play the stream...
 */

bool targetStandardInterface::_play_stream(const std::string& sInputStreamName,
                                          const std::string& sOutputYUVName,
                                          RMuint32 profile,
                                          RMuint32 taskID)
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...
    bool        bRes = false;
    targetStandardIFTask::targetStdIfParms parms;

    RMDBGLOG((LOCALDBG, "%s(%s, %s, %d, %d)\n", __PRETTY_FUNCTION__,
              sInputStreamName.c_str(), sOutputYUVName.c_str(), profile, taskID));

    /* Check if the output YUV file was specified and can be opened! */
    if (!sOutputYUVName.empty()) {
        if (file_utils::can_write_file(sOutputYUVName)) {
//            outputYUVName   = sOutputYUVName;
        } else {
            RMDBGLOG((LOCALDBG, "Unable to create YUV output file!\n"));
            return false;
        }
    }

    parms.sInputStreamName  = sInputStreamName;
    parms.sOutputYUVName    = sOutputYUVName;
    parms.nProfile          = profile;
    parms.pAlloc            = m_pAlloc[0];
    parms.pIF               = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    parms.sXmlPath          = OPTION_XML_PATH;

    ifState = IF_COMMAND_PENDING;

    tasks[taskID] = std::make_shared<targetStandardIFTask>(parms);
    tasks[taskID]->start();

    ifState = IF_PLAYING;

    RMDBGLOG((LOCALDBG, "-- exiting _play_stream()\n"));

    return bRes;
}

/**
 *  Stop playback.
 */

bool targetStandardInterface::stop() {
    mutex_guard guard(contextMutex);    // obtain the context mutex...

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    if (ifState == IF_PLAYING) {
        stop_tasks();
        ifState = IF_INITIALIZED;
    }

    return true;
}

/**
 *  Initialize parameters...
 */

void targetStandardInterface::init_parameters()
{
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    /* Nothing to see here */

}

/**
 *  Table which relates abbreviation string to codec ID.
 */

struct targetStandardInterface::profileEntry targetStandardInterface::profileTable[] = {
    { "mpeg2",  VideoProfileMPEG2, },
    { "mpeg4",  VideoProfileMPEG4, },
    { "h264",   VideoProfileH264, },
    { "h265",   VideoProfileH265, },
    { "hevc",   VideoProfileH265, },
    { "divx",   VideoProfileDIVX3, },
    { "spu",    VideoProfileDVDSpu, },
    { "vc1",    VideoProfileVC1, },

    { "", 0, },
};

/**
 *
 */

RMint32 targetStandardInterface::get_profile_id_from_string(const std::string& sCodecID)
{
    struct profileEntry *pCurEntry = profileTable;

    while (pCurEntry->sIdent.size() > 0) {
        if (string_utils::caseInsensitiveStringCompare(pCurEntry->sIdent, sCodecID)) {
            return pCurEntry->nProfile;
        }
        pCurEntry++;    // Advance to next profile entry...
    }

    return -1;
}

/**
 *
 */

std::string targetStandardInterface::get_profile_string_from_id(RMint32 codec_id)
{
    struct profileEntry *pCurEntry = profileTable;

    while (pCurEntry->sIdent.size() > 0) {
        if (pCurEntry->nProfile == codec_id) {
            return pCurEntry->sIdent;
        }
        pCurEntry++;    // Advance to next profile entry...
    }

    return "Undefined";
}

/**
 *
 */

void targetStandardInterface::get_profile_vector(PROFILE_VECTOR& pVec)
{
    struct profileEntry *pCurEntry = profileTable;

    while (pCurEntry->sIdent.size() > 0) {
        pVec.push_back(pCurEntry->sIdent);
        pCurEntry++;    // Advance to next profile entry...
    }

    return;
}

/**
 *
 */

void targetStandardInterface::stop_tasks() {
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    for (auto task : tasks) {
        if (task) {
            targetStandardIFTask::taskState state;

            task->get_state(&state, nullptr);

            if (state == targetStandardIFTask::TASK_PLAYING) {
                task->stop();
            }
        }
    }

    return;
}

/**
 *
 */

bool targetStandardInterface::get_output_stats(RMuint32 taskID, outputStats& stats) const
{
    bool    bRes = false;

    if (taskID < MAX_TASK_COUNT) {

        if (tasks[taskID]) {
            targetStandardIFTask::taskState state;

            tasks[taskID]->get_state(&state, nullptr);

            if (state == targetStandardIFTask::TASK_PLAYING) {
                bRes = tasks[taskID]->get_output_stats(stats);
            } else {
                RMDBGLOG((LOCALDBG, "ERROR: task ID %d is not playing.\n", taskID));
            }
        }
    } else {
        RMDBGLOG((LOCALDBG, "ERROR: task ID %d out of range.\n", taskID));
    }

    return bRes;
}

/**
 *
 */
bool targetStandardInterface::get_input_stats(RMuint32 taskID, inputStats& stats) const
{
    bool    bRes = false;

    if (taskID < MAX_TASK_COUNT) {

        if (tasks[taskID]) {
            targetStandardIFTask::taskState state;

            tasks[taskID]->get_state(&state, nullptr);

            if (state == targetStandardIFTask::TASK_PLAYING) {
                bRes = tasks[taskID]->get_input_stats(stats);
            } else {
                RMDBGLOG((LOCALDBG, "ERROR: task ID %d is not playing.\n", taskID));
            }
        }
    } else {
        RMDBGLOG((LOCALDBG, "ERROR: task ID %d out of range.\n", taskID));
    }

    return bRes;
}

/**
 *
 */

void targetStandardInterface::clear_scheduler_data()
{
    controlInterface*       pIF         = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    RMuint32                memBase     = pIF->get_engine()->get_pmBase();

    video_utils::video_set_scheduler_memory(pIF, memBase, 0, 0);
}

/**
 *
 */

targetStandardInterface::if_state targetStandardInterface::get_interface_state(uint32_t* taskCount) const
{
    if (taskCount != nullptr) {
        *taskCount = 0;
        for (auto task : tasks) {
            if (task) {
                (*taskCount)++;
            }
        }
    }

    return ifState;
}

/**
 *
 */

bool targetStandardInterface::get_task_state(uint32_t taskID,
                                       targetStandardIFTask::taskState* pTaskState,
                                       targetStandardIFTask::taskSubstate* pTaskSubstate)
{
    bool bRes = false;

    if ((taskID >= 0) && (taskID < MAX_TASK_COUNT)) {
        if (tasks[taskID]) {
            tasks[taskID]->get_state(pTaskState, pTaskSubstate);
            bRes = true;
        }
    }

    return bRes;
}


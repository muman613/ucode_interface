#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
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

#ifdef _DEBUG
#define LOCALDBG    ENABLE
#else
#define LOCALDBG    DISABLE
#endif // _DEBUG

using namespace video_utils;

typedef std::lock_guard<std::mutex>     mutex_guard;

/**
 *  Object represents the standard microcode interface.
 */

targetStandardInterface::targetStandardInterface(TARGET_ENGINE_PTR pEngine)
:   targetInterfaceBase(pEngine),
    bValid(false),
    ifState(IF_UNINITIALIZED),
    pChroma(nullptr),
    pLuma(nullptr),
    yuvfp(nullptr),
    total_frames(0),
    fifoFillRunning(false),
    fifoEmptyRunning(false),
    terminateThreads(false)
{
    RMuint32 offset = 0;
    // ctor
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    pEngine->get_ucode_offset(nullptr, &offset);

    init_parameters();

    m_pAlloc[0]->alloc(targetAllocator::ALLOC_DRAM, offset);

#ifdef _DEBUG
    m_pAlloc[0]->dump(std::cerr);
#endif // _DEBUG

}

targetStandardInterface::~targetStandardInterface()
{
    // dtor
    if (ifState == IF_PLAYING) {
        stop();
    }
}

/**
 *  Play the stream...
 */

bool targetStandardInterface::play_stream(const std::string& sInputStreamName,
                                          const std::string& sOutputYUVName,
                                          const std::string& sProfile)
{
    RMuint32 nProfile = VideoProfileMPEG2;
    RMDBGLOG((LOCALDBG, "%s(%s, %s, %s)\n", __PRETTY_FUNCTION__,
              sInputStreamName.c_str(), sOutputYUVName.c_str(),
              sProfile.c_str()));
    nProfile = get_profile_id_from_string(sProfile);

    return play_stream(sInputStreamName, sOutputYUVName, nProfile);
}

/**
 *  Play the stream...
 */

bool targetStandardInterface::play_stream(const std::string& sInputStreamName,
                                          const std::string& sOutputYUVName,
                                          RMuint32 profile)
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...
    bool        bRes = false;

    RMDBGLOG((LOCALDBG, "%s(%s, %s, %d)\n", __PRETTY_FUNCTION__,
              sInputStreamName.c_str(), sOutputYUVName.c_str(), profile));

    if (ifState == IF_PLAYING) {
        RMDBGLOG((LOCALDBG, "Interface already playing media!\n"));
        return false;
    }

    /* Check if the output YUV file was specified and can be opened! */
    if (!sOutputYUVName.empty()) {
        if (file_utils::can_write_file(sOutputYUVName)) {
            outputYUVName   = sOutputYUVName;
        } else {
            RMDBGLOG((LOCALDBG, "Unable to create YUV output file!\n"));
        }
    }

    if (file_utils::file_exists(sInputStreamName)) {
        /* copy the names into the class storage. */
        inputStreamName = sInputStreamName;
        decoderProfile  = profile;

        init_video_engine();
        open_video_decoder();

        launch_threads();
        ifState = IF_PLAYING;
    } else {
        RMDBGLOG((LOCALDBG, "-- input/output error!\n"));
    }

    RMDBGLOG((LOCALDBG, "-- exiting play_stream()\n"));

    return bRes;
}

/**
 *  Stop playback.
 */

bool targetStandardInterface::stop() {
    mutex_guard guard(contextMutex);    // obtain the context mutex...

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    if (ifState == IF_PLAYING) {
        stop_threads();
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

    DecoderDataSize	            = DECODER_DATA_SIZE;
    DecoderContextSize          = DECODER_CTX_SIZE;
    BitstreamFIFOSize           = (2 * 1024 * 1024);
    PtsFIFOCount                = 512;
    InbandFIFOCount             = 512;
    NumOfPictures               = PICTURE_COUNT;
    soc_arch                    = SOC_TANGO;
    storage_format              = 0;
    luma_nb_comp_per_sample     = 1;
    chroma_nb_comp_per_sample   = 2;
    decoderProfile              = VideoProfileMPEG2;
    UserDataSize                = 0;

    set_tile_dimensions( m_pEngine[0]->get_engine()->get_parent()->get_parent()->get_chip_id() );

    //m_pAlloc[0]->set_tile_dimensions( )
}

/**
 *  Initialize the video decoder...
 */

RMstatus targetStandardInterface::init_video_engine()
{
    RMuint32            memBase = m_pEngine[0]->get_engine()->get_pmBase();
    RMuint32            Address = 0,
                        Size = 0;
    controlInterface*   pIF = nullptr;
    RMuint32            uiDRAMPtr = m_pAlloc[0]->dramPtr();

    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    pIF = dynamic_cast<controlInterface*>(m_pEngine[0].get());

    video_get_scheduler_memory( pIF, memBase, &Address, &Size);

    if ((Address == 0) && Size) {
        Address = (uiDRAMPtr & 0xfffffffc) + 4; // align by 4
        video_set_scheduler_memory(pIF, memBase, Address, Size);
        Size += 4;
        m_pAlloc[0]->alloc(targetAllocator::ALLOC_DRAM, Size);
        m_pAlloc[0]->dump(std::cerr);
//        pContext->uiDRAMPtr += Size;
    }

    return RM_OK;
}


#define INIT_STRUCT( var, str )                                                 \
    nStructSize = pStructDB->get_structure( (str) )->size();                    \
    (var)       = pAlloc->alloc(targetAllocator::ALLOC_DRAM, nStructSize);      \
                                                                                \
    for (i = 0 ; i < nStructSize ; i++) {                                       \
        m_pEngine[0]->get_gbusptr()->gbus_write_uint32((var) + 4 * i, 0);       \
    }

/**
 *
 */
#define RMTILE_SIZE_SHIFT 0xd

RMstatus targetStandardInterface::open_video_decoder()
{
    RMstatus                nStatus     = RM_ERROR;
    TARGET_ALLOC_PTR        pAlloc      = m_pAlloc[0];
    structure_database*     pStructDB   = m_pEngine[0]->get_structdb();
    RMuint32                nStructSize = 0L;
    controlInterface*       pIF         = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    RMuint32                i           = 0;
    RMstatus 		        err __attribute__ ((unused))         = RM_OK;
    RMuint32                dramPtr     = 0;
    RMuint32                video_bts_fifo,
                            video_pts_fifo;
    RMuint32                fifoEraserSize = 0;

    assert(pStructDB != nullptr);
    assert(pIF != nullptr);

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
                           m_pEngine[0]->get_engine()->get_pmBase(),
                           0,
                           pvtdb);

//    RMuint32 tempVal = RM_NEXT_TILE_ALIGN(pAlloc->dramPtr());
//    dramPtr = tempVal;
    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM|targetAllocator::ALLOC_TILEALIGN, DecoderDataSize);

    err = video_set_data_context_buffer(pIF, pvti, dramPtr,
                                        DecoderDataSize, DecoderContextSize);

    struct_utils::write_structure_member(pIF, pvti, "video_task_interface", "MiscFlags", 1);

    fifoEraserSize = struct_utils::get_structure_size(pIF, "gbus_fifo_eraser");

    video_bts_fifo = pAlloc->alloc(targetAllocator::ALLOC_DRAM|targetAllocator::ALLOC_PAGEALIGN, fifoEraserSize);
    RMDBGLOG((LOCALDBG, "video_bts_fifo = %08X\n", video_bts_fifo));
    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM|targetAllocator::ALLOC_PAGEALIGN, BitstreamFIFOSize);
    RMDBGLOG((LOCALDBG, "dramPtr = %08X\n", dramPtr));

    gbus_fifo_eraser_open( pIF->get_gbusptr(), dramPtr, BitstreamFIFOSize, video_bts_fifo );
    err = video_set_bts_fifo_pointer( pIF, pvtdb, video_bts_fifo );

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

    {
        RMuint32 i;

        for (i = 0 ; i < InbandFIFOCount * sizeof(struct MicrocodeInbandParams)/sizeof(RMuint32) ; i++)
        {
            pIF->get_gbusptr()->gbus_write_uint32( inband_params_address + (4*i), 0);
        }
    }

    video_set_inband_param_addr(pIF, pvtdb, inband_params_address);

    err = video_get_display_fifo(pIF, pvtdb, &display_fifo);

    dramPtr = pAlloc->alloc(targetAllocator::ALLOC_DRAM, (sizeof(RMuint32) * (NumOfPictures + 1)));

    //gbus_entry_fifo_open(pContext->pgbus, unprotected_ptr, pContext->NumOfPictures + 1, pContext->display_fifo);
    gbus_entry_fifo_open( pIF->get_gbusptr(), dramPtr, (NumOfPictures + 1), display_fifo );

        //clear the pointers to picture buffers
    for ( i =0; i < NumOfPictures + 1; i++)
    {
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

#if 0
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
#endif // 1

    return nStatus;
}

typedef struct {
    std::string sID;
    RMuint32    tileW;
    RMuint32    tileH;
} tileDef;

static tileDef  chipTileSizes[] = {
    { "8758", 8, 5, },
    { "8760", 9, 5, },
};

/**
 *  Set tile dimensions by chip ID...
 */

bool targetStandardInterface::set_tile_dimensions(std::string sChipId)
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

void targetStandardInterface::set_tile_dimensions(RMuint32 tsw, RMuint32 tsh)
{
    RMDBGLOG((LOCALDBG, "%s(%ld, %ld)\n", __PRETTY_FUNCTION__, tsw, tsh));

    tile_width_l2       = tsw;
    tile_height_l2      = tsh;
    pvc_tw              = (1 << tsw);
    pvc_th              = (1 << tsh);
    pvc_ts              = pvc_tw * pvc_th;

    m_pAlloc[0]->set_tile_size( tsw, tsh );

    return;
}

#ifdef USE_PTHREADS
/**
 *  Stub for the fifo fill thread.
 */

void* targetStandardInterface::_fifoFillThreadFunc(targetStandardInterface* pThis)
{
    return pThis->fifoFillThreadFunc();
}

/**
 *  Stub for the fifo empty thread.
 */

void* targetStandardInterface::_fifoEmptyThreadFunc(targetStandardInterface* pThis)
{
    return pThis->fifoEmptyThreadFunc();
}

#endif // USE_PTHREADS

/**
 *  Launch the background threads, use std::thread unless USE_PTHREADS is defined.
 */

bool targetStandardInterface::launch_threads()
{
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

#ifdef USE_PTHREADS
    RMDBGLOG((LOCALDBG, "-- using pthreads to launch threads...\n"));
    if (pthread_create(&fifoFillThread, NULL, _fifoFillThreadFunc, this) != 0) {
        RMDBGLOG((LOCALDBG, "Unable to start fifoFillThread!\n"));
        return false;
    } else {
        if (pthread_create(&fifoEmptyThread, NULL, _fifoEmptyThreadFunc) != 0) {
            RMDBGLOG((LOCALDBG, "Unable to start fifoEmptyThread!\n"));
            pthread_cancel(fifoFillThread);
            return false;
        }
    }
#else
    RMDBGLOG((LOCALDBG, "-- using c++11 std::thread to launch threads...\n"));

    fifoFillThread  = std::thread( &targetStandardInterface::fifoFillThreadFunc, this );
    fifoEmptyThread = std::thread( &targetStandardInterface::fifoEmptyThreadFunc, this );

#endif // USE_PTHREADS

    /* Wait for both threads to enter running state */
    while ((fifoFillRunning == false) || (fifoEmptyRunning == false)) {
        usleep(50);
    }

    RMDBGLOG((LOCALDBG, "-- threads running!\n"));

    return true;
}

/**
 *  Signal the background threads to terminate. Wait for the threads to exit...
 */

void targetStandardInterface::stop_threads()
{
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

    terminateThreads = true;

    fifoFillThread.join();
    fifoEmptyThread.join();

    return;
}

/**
 *  Thread responsible for filling the bitstream FIFO.
 */

void* targetStandardInterface::fifoFillThreadFunc()
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

void* targetStandardInterface::fifoEmptyThreadFunc()
{
    controlInterface*       pIF         = dynamic_cast<controlInterface*>(m_pEngine[0].get());
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

        //    process_picture( picture_address );

            // advance read pointer
            rd = (rd + 1) % fifo_size;
            size--;
            // release pictures
//            pIF->get_gbusptr()->gbus_write_uint32((RMuint32) &(((struct VideoMicrocodePicture *)picture_address)->picture_display_status), 0);
            struct_utils::write_structure_member(pIF, picture_address, "VideoMicrocodePicture", "picture_display_status", 0);
            total_frames++;

            // update FIFO read pointer
            //pIF->get_gbusptr()->gbus_write_uint32((RMuint32) &(fifo->rd), rd);
            gbus_fifo_incr_read_ptr(pIF->get_gbusptr(), (struct gbus_fifo*)display_fifo, 1);
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

RMuint32 targetStandardInterface::write_data_in_circular_bts_fifo(RMuint8 *pBuf,
                                                                  RMuint32 sizeToSend)
{
#if 1
    RMDBGLOG((LOCALDBG, "%s(%p, %d)\n", __PRETTY_FUNCTION__, pBuf, sizeToSend));
    return 0;
#else
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
#endif // 1
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


#if 0

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
#endif



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <iomanip>
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

#ifdef _DEBUG
#define LOCALDBG    ENABLE
#else
#define LOCALDBG    DISABLE
#endif // _DEBUG

#define ENABLE_EXTRA_DEBUG_INFO 1

#define COMMAND_TIMEOUT         0xffffffff

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
    picture_count(0),
    save_time(0.0),
    yuvfp(nullptr),
    total_frames(0),
    dump_y_uv(false),
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

    /* Initialize and open the video decoder */
    init_video_engine();
    open_video_decoder();

    ifState = IF_INITIALIZED;
}

targetStandardInterface::~targetStandardInterface()
{
    // dtor
    if (ifState == IF_PLAYING) {
        stop();
    }
}

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

/**
 *  Play the stream...
 */

bool targetStandardInterface::play_stream(const std::string& sInputStreamName,
                                          const std::string& sOutputYUVName,
                                          RMuint32 profile,
                                          RMuint32 taskID)
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...
    bool        bRes = false;

    RMDBGLOG((LOCALDBG, "%s(%s, %s, %d, %d)\n", __PRETTY_FUNCTION__,
              sInputStreamName.c_str(), sOutputYUVName.c_str(), profile, taskID));

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

        set_video_codec();
        send_video_command( VideoCommandPlayFwd, VideoStatusPlayFwd );
        launch_threads();
        ifState = IF_PLAYING;
    } else {
        RMDBGLOG((LOCALDBG, "ERROR: Unable to find input file!\n"));
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
    ExtraPictureBufferCount     = 0;

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

    video_get_scheduler_memory( pIF, memBase, &Address, &Size );

    if ((Address == 0) && Size) {
        Address = (uiDRAMPtr & 0xfffffffc) + 4; // align by 4
        video_set_scheduler_memory(pIF, memBase, Address, Size);
        Size += 4;
        m_pAlloc[0]->alloc(targetAllocator::ALLOC_DRAM, Size);
#ifdef _DEBUG
        m_pAlloc[0]->dump(std::cerr);
#endif // _DEBUG
    }

    return RM_OK;
}


#define INIT_STRUCT( var, str )                                                 \
    nStructSize = pStructDB->get_structure( (str) )->size();                    \
    (var)       = pAlloc->alloc(targetAllocator::ALLOC_DRAM, nStructSize);      \
                                                                                \
    for (i = 0 ; i < nStructSize/4 ; i++) {                                     \
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

            process_picture( picture_address );

            // advance read pointer
            rd = (rd + 1) % fifo_size;
            size--;

            // release pictures
            struct_utils::write_structure_member(pIF, picture_address, "VideoMicrocodePicture", "picture_display_status", 0);
            total_frames++;

            // update FIFO read pointer
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
    controlInterface*       pIF         = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    GBUS_PTR                pGbus       = pIF->get_gbusptr();
	RMuint32                rd, wr,
                            fifo_base, fifo_size;
	RMuint32                size, sizeLeft;

    RMDBGLOG((LOCALDBG, "%s(%p, %d)\n", __PRETTY_FUNCTION__, pBuf, sizeToSend));

    gbus_fifo_get_pointer(pGbus, (struct gbus_fifo*)bts_fifo, &fifo_base,
                          &fifo_size, &rd, &wr);

    RMDBGLOG((LOCALDBG, "FIFO @ 0x%08lX START 0x%08lX SIZE 0x%08lX RD = 0x%08lX WR = 0x%08lX\n",
            (unsigned long)bts_fifo, fifo_base, fifo_size, rd, wr));

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
	} else { // rd <= wr
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

RMstatus targetStandardInterface::set_video_codec()
{
    controlInterface*   pIF    = dynamic_cast<controlInterface*>(m_pEngine[0].get());

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


RMstatus targetStandardInterface::send_video_command(enum VideoCommand cmd,
                                                     enum VideoStatus stat)
{
    RMstatus            result = RM_ERROR;
    controlInterface*   pIF    = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    enum VideoStatus    VideoDecoderStatus;
    RMuint32            started;

//    APP_STATE appState;
//
//    switch (cmd) {
//    case VideoCommandUninit:
//        appState = APP_SENDING_UNINIT;
//        break;
//    case VideoCommandInit:
//        appState = APP_SENDING_INIT;
//        break;
//    case VideoCommandPlayFwd:
//        appState = APP_SENDING_PLAY;
//        break;
//    case VideoCommandStop:
//        appState = APP_SENDING_STOP;
//        break;
//    default:
//        appState = APP_STATE_UNKNOWN;
//        break;
//    }

#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("entering send_video_command");
#endif // ENABLE_GBUS_LOGGER

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

#ifdef ENABLE_GBUS_LOGGER
    pIF->get_gbusptr()->gbus_log_mark("exiting send_video_command");
#endif // ENABLE_GBUS_LOGGER

    return result;
}

/**
 *  Retrieve the rectangle from the picture buffer.
 */

void targetStandardInterface::READ_PICTURE_BUFFER_RECT(controlInterface* pIF, RMuint32 address, std::string sField, struct targetStandardInterface::EMhwlibWindow* pDest) {
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

RMuint32 targetStandardInterface::READ_PICTURE_BUFFER_MEMBER(controlInterface* pIF, RMuint32 address, const std::string& member) {
    RMuint32    value = 0L;
    struct_utils::read_structure_member(pIF, address, "VideoMicrocodePicture", member, &value);
    return value;
}

/**
 *  Extract picture from display FIFO.
 */

RMstatus targetStandardInterface::process_picture(RMuint32 picture_address)
{
    mutex_guard         guard(contextMutex);    // obtain the context mutex...
    controlInterface*   pIF    = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    RMstatus            result = RM_ERROR;
    RMuint32            frame_count = 0;
    RMuint32            luma_address = 0,
                        chroma_address = 0;
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
    struct timespec     ts1, ts2, ts3 = { 0, 0 };

    clock_gettime(CLOCK_REALTIME, &ts1);

    frame_count    = READ_PICTURE_BUFFER_MEMBER(pIF, picture_address, "frame_count");
    luma_address   = READ_PICTURE_BUFFER_MEMBER(pIF, picture_address, "luma_address");
    chroma_address = READ_PICTURE_BUFFER_MEMBER(pIF, picture_address, "chroma_address");
    luma_ttl_wd    = READ_PICTURE_BUFFER_MEMBER(pIF, picture_address, "luma_total_width");
    chroma_ttl_wd  = READ_PICTURE_BUFFER_MEMBER(pIF, picture_address, "chroma_total_width");

    READ_PICTURE_BUFFER_RECT(pIF, picture_address, "luma_position_in_buffer", &luma_position_in_buffer);
    READ_PICTURE_BUFFER_RECT(pIF, picture_address, "chroma_position_in_buffer", &chroma_position_in_buffer);

    /* calculate luma buffer size */
    luma_buf_width  = ((luma_position_in_buffer.width + pvc_tw - 1)/pvc_tw) * pvc_tw;
    luma_buf_height = ((luma_position_in_buffer.height + pvc_th - 1)/pvc_th) * pvc_th;
    luma_size_tile = (luma_buf_width * luma_buf_height);

    /* calculate chroma buffer size */
    chroma_buf_width  = ((chroma_position_in_buffer.width + pvc_tw - 1)/pvc_tw) * pvc_tw;
    chroma_buf_height = ((chroma_position_in_buffer.height + pvc_th - 1)/pvc_th) * pvc_th;
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

    if (yuvfp != nullptr) {
        if (pLuma == nullptr) {
            pLuma = (RMuint8*)malloc(luma_size_tile);
        }

        if (pChroma == nullptr) {
            pChroma = (RMuint8*)malloc(chroma_size_tile);
        }

//        pLuma   = ctx->pLuma;
//        pChroma = ctx->pChroma;

        pIF->get_gbusptr()->gbus_read_data8(luma_address,   pLuma,   luma_size_tile);
        pIF->get_gbusptr()->gbus_read_data8(chroma_address, pChroma, chroma_size_tile);

//        gbus_read_data8(pgbus, luma_address,   pLuma,   luma_size_tile);
//        gbus_read_data8(pgbus, chroma_address, pChroma, chroma_size_tile);

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

    picture_w       = luma_position_in_buffer.width;
    picture_h       = luma_position_in_buffer.height;
    picture_count   = frame_count;
    picbuf_address  = picture_address;

    clock_gettime(CLOCK_REALTIME, &ts2);

    ts3         = difftimespec( ts1, ts2 );
    save_time   = get_ts_seconds(ts3);

    return result;
}

/**
 *  Generate filenames for Y & UV dump files.
 */

void  targetStandardInterface::get_dump_filenames(RMuint32 frame_no,
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

void targetStandardInterface::save_frame(RMuint32 frame_count,
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
//	RMuint32 chromasize = 0;
//	RMuint8	 *data      = 0L;
//	RMuint8	 *ptr       = 0L;
    RMuint32 x,y;
    RMuint32 x_min, x_max, y_min, y_max;
    RMuint32 luma_tile_cnt, chroma_tile_cnt;
    RMuint8  *uPtr      = 0L,
             *vPtr      = 0L;
    RMuint32 i;

//#ifndef ENABLE_CURSES
//    printf("Saving frame %ld (luma %ld x %ld) (chroma %ld x %ld)...\n", frame_count,
//           luma_w, luma_h, chroma_w, chroma_h);
//    fflush(stdout);
//#endif // ENABLE_CURSES

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
 *  Return the current frame counter...
 */

bool targetStandardInterface::get_output_stats(outputStats& stats) const
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...

    stats.sYUVFile          = outputYUVName;
    stats.pic_address       = picbuf_address;
    stats.pic_width         = picture_w;
    stats.pic_height        = picture_h;
    stats.save_time         = save_time;
    stats.frame_count       = picture_count;

    return true;
}

/**
 *
 */

bool targetStandardInterface::get_input_stats(inputStats& stats) const
{
    mutex_guard guard(contextMutex);    // obtain the context mutex...

    stats.sInputFile        = inputStreamName;
    stats.bytesRead         = 0;

    return true;
}

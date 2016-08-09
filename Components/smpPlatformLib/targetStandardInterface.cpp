#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ALLOW_OS_CODE
#include "targetEngine.h"
#include "targetInterfaceBase.h"
#include "targetStandardInterface.h"
#include "video_utils.h"
#include "struct_utils.h"
#include "gbus_fifo_eraser.h"

#ifdef _DEBUG
#define LOCALDBG    ENABLE
#else
#define LOCALDBG    DISABLE
#endif // _DEBUG

using namespace video_utils;

/**
 *  Object represents the standard microcode interface.
 */

targetStandardInterface::targetStandardInterface(TARGET_ENGINE_PTR pEngine)
:   targetInterfaceBase(pEngine)
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

    set_tile_dimensions( m_pEngine[0]->get_engine()->get_parent()->get_parent()->get_chip_id() );

    //m_pAlloc[0]->set_tile_dimensions( )
}

//void targetStandardInterface::test_function()
//{
//    GBUS_PTR pGbus = m_pEngine[0]->get_gbusptr();
//
//    pGbus->gbus_write_uint32(0x100000, 0xdeadbeef);
//}

/**
 *
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

RMstatus targetStandardInterface::open_video_decoder()
{
    RMstatus                nStatus     = RM_ERROR;
    TARGET_ALLOC_PTR        pAlloc      = m_pAlloc[0];
    structure_database*     pStructDB   = m_pEngine[0]->get_structdb();
    RMuint32                nStructSize = 0L;
    controlInterface*       pIF         = dynamic_cast<controlInterface*>(m_pEngine[0].get());
    RMuint32                i           = 0;
    RMstatus 		        err         = RM_OK;
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
 *
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
 *
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


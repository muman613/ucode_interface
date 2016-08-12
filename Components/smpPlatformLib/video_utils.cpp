#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "targetStandardInterface.h"
#include "video_utils.h"
#include "struct_utils.h"
#include "gbus_fifo.h"
#include "gbus_packet_fifo.h"
#include "gbus_packet_fifo_eraser.h"

#ifdef _DEBUG
    #define LOCALDBG ENABLE
#else
    #define LOCALDBG DISABLE
#endif // _DEBUG

namespace video_utils {

#define RESOLVE_SYMBOL(sym)                                                     \
    (*pSymMgr)[(sym)]

/**
 *  set the DRAM address where the video microcode is loaded
 */

RMstatus video_set_ucode_dram_offset(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 start_address)
{
    GBUS_PTR        pGbus = pIF->get_gbusptr();
    UcodeSymbolMgr* pSymMgr = pIF->get_symmgr();

	RMDBGLOG((LOCALDBG, "video_set_ucode_dram_offset = 0x%lx\n", start_address));

	pGbus->gbus_write_uint32(MemBase + RESOLVE_SYMBOL("VDsp_CodeOffsetLo"),
                             start_address & 0xFFFF);
	pGbus->gbus_write_uint32(MemBase + RESOLVE_SYMBOL("VDsp_CodeOffsetHi"),
                             start_address >> 16);

	return RM_OK;
}

/**
 *
 */

RMstatus video_get_scheduler_memory(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 *pstart_address,
	RMuint32 *psize)
{
    GBUS_PTR        pGBus = pIF->get_gbusptr();
    UcodeSymbolMgr* pSymMgr = pIF->get_symmgr();
	RMuint32        schedStart;
	RMuint32        scheduler_data_address = MemBase + RESOLVE_SYMBOL("SchedulerDataStart");
    const structure_definition* pDef = nullptr;

	RMDBGLOG((LOCALDBG, "video_get_scheduler_memory(0x%p, 0x%lx)\n", pGBus.get(), MemBase));

	schedStart = (pGBus->gbus_read_uint32(scheduler_data_address) & 0xFFFF);
	schedStart |= (pGBus->gbus_read_uint32(scheduler_data_address + 4) << 16);

	*pstart_address = schedStart;

    pDef = pIF->get_structdb()->get_structure("scheduler_data");
    if (pDef != nullptr) {
        *psize = pDef->size();
    }

	RMDBGLOG((LOCALDBG, "video_get_scheduler_memory: addr=0x%lx size=%ld bytes\n",
		*pstart_address, *psize));

	return RM_OK;
}

/**
 *
 */

RMstatus video_set_scheduler_memory(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 start_address,
	RMuint32 size)
{
    GBUS_PTR        pGBus   = pIF->get_gbusptr();
    UcodeSymbolMgr* pSymMgr = pIF->get_symmgr();
    structure_database* pStructDB = pIF->get_structdb();
    RMuint32            scheduler_size = 0L;
    const structure_definition* pSched = nullptr;

	/* size it is unused in microcode */
	RMuint32 scheduler_data_address = MemBase + RESOLVE_SYMBOL("SchedulerDataStart");

	RMDBGLOG((LOCALDBG, "video_set_scheduler_memory() at 0x%lx: addr=0x%lx size=%ld (prev=0x%04lx%04lx)\n",
		scheduler_data_address, start_address, size,
		pGBus->gbus_read_uint32(scheduler_data_address + 4),
		pGBus->gbus_read_uint32(scheduler_data_address) ));

    pSched = pStructDB->get_structure("scheduler_data");
    if (pSched == nullptr) {
        return RM_ERROR;
    }
    scheduler_size = pSched->size();

	if (start_address) {
		RMuint32 i;

		/* set new not NULL scheduler address - should I check if previous address was not NULL ?? */
		/* set first the hi part as 0 to invalidate it */
		pGBus->gbus_write_uint32(scheduler_data_address + 4, 0);
		for (i = 0 ; i < scheduler_size/4 ; i++) {
			pGBus->gbus_write_uint32(start_address + (i * 4), 0);
		}

		pGBus->gbus_write_uint32(start_address, MAX_TASK_COUNT); /* Write # of tasks in tables */
		pGBus->gbus_write_uint32(scheduler_data_address, (start_address & 0xFFFF));
		pGBus->gbus_write_uint32(scheduler_data_address + 4, (start_address >> 16));
	}
	else {
		/* set NULL scheduler address - set first the hi part */
		pGBus->gbus_write_uint32(scheduler_data_address + 4, 0);
		pGBus->gbus_write_uint32(scheduler_data_address, 0);
	}

	return RM_OK;
}

/**
 *  The pictures with an error count above this value are not sent to display.
 */

RMstatus video_set_display_error_threshold(
	controlInterface* pIF,
	RMuint32 pvti,
	RMuint32 threshold)
{
    GBUS_PTR                    pGBus     = pIF->get_gbusptr();
    structure_database*         pStructDB = pIF->get_structdb();
	const structure_definition* pStruct   = nullptr;

	RMuint32 addr; // = (RMuint32) &(pvti->DisplayErrorThreshold);

    pStruct = pStructDB->get_structure("video_task_interface");
    if (pStruct != nullptr) {
        addr = pvti + pStruct->member("DisplayErrorThreshold")->offset();

        RMDBGLOG((LOCALDBG, "video_set_display_error_threshold addr=0x%lx %ld (previous=%ld)\n",
            addr, threshold, pGBus->gbus_read_uint32(addr)));

        pGBus->gbus_write_uint32(addr, threshold);
    } else {
        RMDBGLOG((LOCALDBG, "ERROR: Unable to resolve 'video_task_interface'!\n"));
    }

	return RM_OK;
}

/**
 *  Set the anchor error propagation parameters.
 */

RMstatus video_set_anchor_propagation_parms(
	controlInterface* pIF,
	RMuint32 pvti,
	RMuint32 threshold, RMuint32 length)
{
    RMstatus                    result    = RM_ERROR;
    GBUS_PTR                    pGBus     = pIF->get_gbusptr();
    structure_database*         pStructDB = pIF->get_structdb();
	const structure_definition* pStruct   = nullptr;
	RMuint32                    addr      = 0L;

	RMDBGLOG((LOCALDBG, "video_set_anchor_propagation_parms(%d, %d)\n", threshold, length));

    pStruct = pStructDB->get_structure("video_task_interface");
    if (pStruct != nullptr) {
        addr = pvti + pStruct->member("AnchorErrPropagationThreshold")->offset();
        pGBus->gbus_write_uint32(addr, threshold);
        addr = pvti + pStruct->member("AnchorErrPropagationLength")->offset();
        pGBus->gbus_write_uint32(addr, length);
        result = RM_OK;
    } else {
        RMDBGLOG((LOCALDBG, "ERROR: Unable to resolve 'video_task_interface'!\n"));
    }

	return result;
}

/**
 *
 */

RMstatus video_set_vti_pointer(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 pvti)
{
    RMstatus                    result    = RM_ERROR;
    GBUS_PTR                    pGBus     = pIF->get_gbusptr();
    structure_database*         pStructDB = pIF->get_structdb();
	const structure_definition* pVtdbStr  = nullptr;
	const structure_definition* pVtiStr   = nullptr;
	RMuint32                    addr      =  0L;

//	struct video_task_interface *pvti = (struct video_task_interface *)pvti_in;

    pVtdbStr = pStructDB->get_structure("video_task_data_base");
    pVtiStr  = pStructDB->get_structure("video_task_interface");

    assert( (pVtdbStr != nullptr) && (pVtiStr != nullptr));

    if ((pVtdbStr != nullptr) && (pVtiStr != nullptr)) {
        RMDBGLOG((LOCALDBG, "video_set_vti_pointer pvdtb= 0x%lx pvti= 0x%lx\n", pvtdb, pvti));

        addr = pvtdb + pVtdbStr->member("Task_InterfacePtr")->offset();
        pGBus->gbus_write_uint32(addr, pvti);
        addr = pvti + pVtiStr->member("Command")->offset();
        pGBus->gbus_write_uint32(addr, VIDEO_NO_CMD);
        addr = pvti + pVtiStr->member("Status")->offset();
        pGBus->gbus_write_uint32(addr, VIDEO_UNINIT);

        result = RM_OK;
    } else {
        RMDBGLOG((LOCALDBG, "ERROR: Unable to resolve video_task_data_base or video_task_interface!\n"));
    }

	return result;
}

/**
 *  set video_task_data_base
 */

RMstatus video_set_vtdb_pointer(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 index,
	RMuint32 pvtdb)
{
    RMstatus                    result    = RM_ERROR;
    GBUS_PTR                    pGBus     = pIF->get_gbusptr();
    structure_database*         pStructDB = pIF->get_structdb();
    UcodeSymbolMgr*             pSymMgr   = pIF->get_symmgr();
	const structure_definition* pTaskStr  = nullptr;
	RMuint32                    addr      =  0L;
	RMuint32                    scheduler_data_address;
	RMuint32                    decoderHead = 0;

	scheduler_data_address = MemBase + RESOLVE_SYMBOL("SchedulerDataStart");

    if (index >= MAX_TASK_COUNT)
		return RM_ERROR;

	RMDBGLOG((LOCALDBG, "video_set_vtdb_pointer addr= 0x%lx pvtb= 0x%lx\n", addr, pvtdb));

	pTaskStr = pStructDB->get_structure("task_entry");

	if (pTaskStr != nullptr) {
        const member_definition* pMember = nullptr;

        pMember = pTaskStr->member("DataBasePtr");
        if (pMember != nullptr) {
            decoderHead = pGBus->gbus_read_uint32(scheduler_data_address);
            decoderHead |= (pGBus->gbus_read_uint32(scheduler_data_address + 4) << 16);

            RMDBGLOG((LOCALDBG, "SchedulerDataStart = 0x%lx\n", decoderHead));

            addr = decoderHead + (index * pTaskStr->size()) + sizeof(RMuint32);
            pGBus->gbus_write_uint32(addr, pvtdb);

            RMDBGLOG((LOCALDBG, "video_set_vtdb_pointer addr= 0x%lx pvtb= 0x%lx\n", addr, pvtdb));

            result = RM_OK;
        } else {
            RMDBGLOG((LOCALDBG, "ERROR: No member 'DataBasePtr'!\n"));
        }
	} else {
        RMDBGLOG((LOCALDBG, "ERROR: Unable to resolve 'video_task_interface'!\n"));
	}

	return result;
}

#if 1
#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)

/**
 *  Set the DRAM address for picture and context for legacy codecs.
 */

RMstatus video_set_data_context_buffer(
	controlInterface* pIF,
	RMuint32 pvti,
	RMuint32 start_address,
	RMuint32 total_size,
	RMuint32 context_size)
{
	RMDBGLOG((LOCALDBG, "%s: addr= 0x%lx total_size= 0x%lx context_size= 0x%lx\n",
             __PRETTY_FUNCTION__, start_address, total_size, context_size));

 #if 1
    struct_utils::write_structure_member (pIF, pvti,
                                         "video_task_interface",
                                         "ContextBuffer.StartAddress",
                                         start_address);
    struct_utils::write_structure_member (pIF, pvti,
                                         "video_task_interface",
                                         "ContextBuffer.Size",
                                         context_size);
    struct_utils::write_structure_member (pIF, pvti,
                                         "video_task_interface",
                                         "LumaFrameBuffer0.StartAddress",
                                         (start_address + context_size));
    struct_utils::write_structure_member (pIF, pvti,
                                         "video_task_interface",
                                         "LumaFrameBuffer0.Size",
                                         (total_size - context_size));
    struct_utils::write_structure_member (pIF, pvti,
                                         "video_task_interface",
                                         "LumaFrameBuffer1.StartAddress",
                                         0);
    struct_utils::write_structure_member (pIF, pvti,
                                         "video_task_interface",
                                         "LumaFrameBuffer1.Size",
                                         0);
 #else
    structure_database* pStructDB   = pIF->get_structdb();
    GBUS_PTR            pGBus       = pIF->get_gbusptr();
    RMuint32            gbusAddress = 0L;

    gbusAddress = struct_utils::resolve_offset(pStructDB, pvti,
                                               "video_task_interface",
                                               "ContextBuffer.StartAddress");
    pGBus->gbus_write_uint32( gbusAddress, start_address );

    gbusAddress = struct_utils::resolve_offset(pStructDB, pvti,
                                               "video_task_interface",
                                               "ContextBuffer.Size");
    pGBus->gbus_write_uint32( gbusAddress, context_size );

    gbusAddress = struct_utils::resolve_offset(pStructDB, pvti,
                                               "video_task_interface",
                                               "LumaFrameBuffer0.StartAddress");
    pGBus->gbus_write_uint32( gbusAddress, start_address + context_size );

    gbusAddress = struct_utils::resolve_offset(pStructDB, pvti,
                                               "video_task_interface",
                                               "LumaFrameBuffer0.Size");
    pGBus->gbus_write_uint32( gbusAddress, total_size - context_size );

    gbusAddress = struct_utils::resolve_offset(pStructDB, pvti,
                                               "video_task_interface",
                                               "LumaFrameBuffer1.StartAddress");
    pGBus->gbus_write_uint32( gbusAddress, 0 );

    gbusAddress = struct_utils::resolve_offset(pStructDB, pvti,
                                               "video_task_interface",
                                               "LumaFrameBuffer1.Size");
    pGBus->gbus_write_uint32( gbusAddress, 0 );
#endif // 1

	return RM_OK;
}

RMstatus video_set_picture_buffer(
	controlInterface* pIF,
	RMuint32 pvti, /* struct video_task_data_base *pvtdb, */
	RMuint32 id,
	RMuint32 address,
	RMuint32 size)
{
    return RM_ERROR;
}

#else // (RMFEATURE_VIDEO_INTERFACE_VERSION==2)

#endif // (RMFEATURE_VIDEO_INTERFACE_VERSION==2)

#else // 1
#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
/* set the DRAM address where picture buffers are allocated */
RMstatus video_set_picture_buffer(
	struct gbus *pGBus,
	struct video_task_interface *pvti, /* struct video_task_data_base *pvtdb, */
	RMuint32 id,
	RMuint32 address,
	RMuint32 size)
{
	RMuint32 buffer_address;
	RMuint32 size_address;
	switch(id) {
	case PICTURE_BUFFER_BANK_0:
		buffer_address = (RMuint32) &(pvti->LumaFrameBuffer0.StartAddress);
		size_address   = (RMuint32) &(pvti->LumaFrameBuffer0.Size);
		break;
	case PICTURE_BUFFER_BANK_1:
		buffer_address = (RMuint32) &(pvti->LumaFrameBuffer1.StartAddress);
		size_address   = (RMuint32) &(pvti->LumaFrameBuffer1.Size);
		break;
	default:
		RMDBGLOG((ENABLE, "%s: ERROR id=%ld address=0x%lx size= %lx\n", __FUNCTION__, id, address, size));
		return RM_ERROR;
	}
	RMDBGLOG((ENABLE, "%s: id=%ld address=0x%lx size= %lx\n", __FUNCTION__, id, address, size));
	gbus_write_uint32(pGBus, buffer_address, address);
	gbus_write_uint32(pGBus, size_address, size);
	return RM_OK;
}

/* set the DRAM address for context */
RMstatus video_set_context_buffer(
	struct gbus *pGBus,
	struct video_task_interface *pvti, /* struct video_task_data_base *pvtdb, */
	RMuint32 address,
	RMuint32 size)
{
	RMDBGLOG((ENABLE, "%s: 0x%lx size= %lx\n", __FUNCTION__, address, size));
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->ContextBuffer.StartAddress), address);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->ContextBuffer.Size), size);
	return RM_OK;
}
/* set the DRAM address for picture and context for legacy codecs */
RMstatus video_set_data_context_buffer(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 start_address,
	RMuint32 total_size,
	RMuint32 context_size)
{
	RMDBGLOG((LOCALDBG, "%s: addr= 0x%lx total_size= 0x%lx context_size= 0x%lx\n", __FUNCTION__, start_address, total_size, context_size));
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->ContextBuffer.StartAddress), start_address);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->ContextBuffer.Size), context_size);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->LumaFrameBuffer0.StartAddress), start_address + context_size);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->LumaFrameBuffer0.Size), total_size - context_size);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->LumaFrameBuffer1.StartAddress), 0);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->LumaFrameBuffer1.Size), 0);
	return RM_OK;
}
#else // (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
/* set the DRAM address where picture buffers are allocated */
RMstatus video_set_data_context_buffer(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 start_address,
	RMuint32 total_size,
	RMuint32 context_size)
{
	RMDBGLOG((LOCALDBG, "%s: addr= 0x%lx total_size= 0x%lx context_size= 0x%lx\n", __FUNCTION__, start_address, total_size, context_size));
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->DataAddress), start_address);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->DataSize), total_size);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->ContextTotalSize), context_size);
	return RM_OK;
}
#endif // (RMFEATURE_VIDEO_INTERFACE_VERSION==2)

#endif // 0

/**
 *  set the pointer to bitstream fifo container, located in demux DMEM.
 */

RMstatus video_set_bts_fifo_pointer(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 bts_fifo)
{
    const structure_definition* pStruct = pIF->get_structdb()->get_structure("video_task_data_base");
    RMuint32 gBusAddress = pvtdb;

	RMDBGLOG((LOCALDBG, "video_set_bts_fifo_pointer= 0x%lx\n", bts_fifo));

	if (pStruct != nullptr) {
        gBusAddress += pStruct->member("InputFifoPtr")->offset();
        pIF->get_gbusptr()->gbus_write_uint32(gBusAddress, bts_fifo);
	}

	return RM_OK;
}

/* get the pointer to time stamp fifo container, allocated in DRAM */
RMstatus video_get_pts_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 *pts_fifo)
{
    RMuint32 ptsFifo = pvtdb;
    const structure_definition* pStruct = pIF->get_structdb()->get_structure( "video_task_data_base");

    if (pStruct != nullptr) {
        ptsFifo += pStruct->member("pts_fifo")->offset();
    }
	*pts_fifo = ptsFifo;

	RMDBGLOG((LOCALDBG, "video_get_pts_fifo= 0x%lx\n", *pts_fifo));

	return RM_OK;
}

/* initialize the time stamp fifo, allocated in DRAM, size in entries */
RMstatus video_open_pts_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 start,
	RMuint32 size)
{
    RMuint32 ptsFifo = pvtdb;
    const structure_definition* pStruct = pIF->get_structdb()->get_structure( "video_task_data_base");

    if (pStruct != nullptr) {
        ptsFifo += pStruct->member("pts_fifo")->offset();
        RMDBGLOG((LOCALDBG, "video_open_pts_fifo= 0x%lx start= 0x%lx size= %lx\n",
            ptsFifo, start, size));
        gbus_entry_fifo_open(pIF->get_gbusptr(), start, size, ptsFifo);
    }

	return RM_OK;
}

/**
 *  initialize the inband command fifo container, allocated in DRAM, size in entries
 */

RMstatus video_open_inband_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 start,
	RMuint32 size)
{
    RMuint32 inbFifo = pvtdb;
    const structure_definition* pStruct = pIF->get_structdb()->get_structure( "video_task_data_base");

    if (pStruct != nullptr) {
        inbFifo += pStruct->member("inband_cmd_fifo")->offset();
        RMDBGLOG((LOCALDBG, "video_open_inband_fifo= 0x%lx start= 0x%lx size= %lx\n",
            inbFifo, start, size));
        gbus_entry_fifo_eraser_open(pIF->get_gbusptr(), start, size, inbFifo);
    } else {
        /* */
    }

	return RM_OK;
}

/**
 *
 */

RMstatus video_set_inband_param_addr(
    controlInterface* pIF,
    RMuint32 pvtdb,
    RMuint32 inband_param_addr)
{
try {
    RMuint32 gbusAddr = struct_utils::resolve_offset(pIF->get_structdb(),
                                                     pvtdb,
                                                     "video_task_data_base",
                                                     "Inband_Params_Address");

    pIF->get_gbusptr()->gbus_write_uint32( gbusAddr, inband_param_addr );

    return RM_OK;
}
catch (std::runtime_error& err) {
    RMDBGLOG((LOCALDBG, "ERROR: video_set_inband_param_addr() failed!\n"));
    return RM_ERROR;
}
}

/* get display data fifo container */
RMstatus video_get_display_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 *display_fifo)
{
try {
    RMuint32 gbusAddr = 0;

    gbusAddr = struct_utils::resolve_offset(pIF->get_structdb(),
                                            pvtdb,
                                            "video_task_data_base",
                                            "display_fifo");
	*display_fifo = gbusAddr;
	RMDBGLOG((LOCALDBG, "video_get_display_fifo = %lx\n", *display_fifo));

	return RM_OK;
}
catch (std::runtime_error& err) {
    RMDBGLOG((LOCALDBG, "ERROR: video_get_display_fifo() failed!\n"));
    return RM_ERROR;
}
}

}

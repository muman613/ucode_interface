#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <unistd.h>

#define ALLOW_OS_CODE 1

#include "llad/include/llad.h"
#include "llad/include/gbus.h"
#include "rmchip/rmchip_registers.h"
#include "video_microcode_labels.h"
#include "video_interface.h"

// to enable or disable the debug messages of this source file, put 1 or 0 below

#if 1
#define LOCALDBG ENABLE
#else
#define LOCALDBG DISABLE
#endif

#ifdef __cplusplus
namespace video_interface {
#endif // __cplusplus

/* set the DRAM address where the video microcode is loaded */
RMstatus video_set_ucode_dram_offset(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 start_address)
{

	RMDBGLOG((LOCALDBG, "video_set_ucode_dram_offset = 0x%lx\n", start_address));

	gbus_write_uint32(pGBus, MemBase + VDsp_CodeOffsetLo, start_address & 0xFFFF);
	gbus_write_uint32(pGBus, MemBase + VDsp_CodeOffsetHi, start_address >> 16);

	return RM_OK;
}


RMstatus video_set_scheduler_memory(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 start_address,
	RMuint32 size)
{
	/* size it is unused in microcode */
	RMuint32 scheduler_data_address = MemBase + SchedulerDataStart;

	RMDBGLOG((LOCALDBG, "video_set_scheduler_memory() at 0x%lx: addr=0x%lx size=%ld (prev=0x%04lx%04lx)\n",
		scheduler_data_address, start_address, size,
		gbus_read_uint32(pGBus, scheduler_data_address + 4),
		gbus_read_uint32(pGBus, scheduler_data_address) ));

	if (start_address) {
		RMuint32 i;

		/* set new not NULL scheduler address - should I check if previous address was not NULL ?? */
		/* set first the hi part as 0 to invalidate it */
		gbus_write_uint32(pGBus, scheduler_data_address + 4, 0);
		for (i = 0 ; i < sizeof(struct scheduler_data)/4 ; i++) {
			gbus_write_uint32(pGBus, start_address + (i * 4), 0);
		}

		gbus_write_uint32(pGBus, start_address, MAX_TASK_COUNT); /* Write # of tasks in tables */
		gbus_write_uint32(pGBus, scheduler_data_address, (start_address & 0xFFFF));
		gbus_write_uint32(pGBus, scheduler_data_address + 4, (start_address >> 16));
	}
	else {
		/* set NULL scheduler address - set first the hi part */
		gbus_write_uint32(pGBus, scheduler_data_address + 4, 0);
		gbus_write_uint32(pGBus, scheduler_data_address, 0);
	}

	return RM_OK;
}

RMstatus video_get_scheduler_memory(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 *pstart_address,
	RMuint32 *psize)
{
	RMuint32 schedStart;
	RMuint32 scheduler_data_address = MemBase + SchedulerDataStart;

	RMDBGLOG((LOCALDBG, "video_get_scheduler_memory(0x%lx, 0x%lx)\n", pGBus, MemBase));

	schedStart = gbus_read_uint32(pGBus, scheduler_data_address) & 0xFFFF;
	schedStart |= (gbus_read_uint32(pGBus, scheduler_data_address + 4) << 16);

	*pstart_address = schedStart;
	*psize = sizeof(struct scheduler_data);

	RMDBGLOG((LOCALDBG, "video_get_scheduler_memory: addr=0x%lx size=%ld bytes\n",
		*pstart_address, *psize));

	return RM_OK;
}

/* The pictures with an error count above this value are not sent to display. */
RMstatus video_set_display_error_threshold(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 threshold)
{
	RMuint32 addr = (RMuint32) &(pvti->DisplayErrorThreshold);
	RMDBGLOG((LOCALDBG, "video_set_display_error_threshold addr=0x%lx %ld (previous=%ld)\n",
		addr, threshold, gbus_read_uint32(pGBus, addr)));
	gbus_write_uint32(pGBus, addr, threshold);

	return RM_OK;
}

/* Set the anchor error propagation parameters */
RMstatus video_set_anchor_propagation_parms(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 threshold, RMuint32 length)
{
	RMuint32 addr = (RMuint32) &(pvti->AnchorErrPropagationThreshold);

	RMDBGLOG((LOCALDBG, "video_set_anchor_propagation_parms(%d, %d)\n", threshold, length));

	gbus_write_uint32(pGBus, addr, threshold);
	addr = (RMuint32) &(pvti->AnchorErrPropagationLength);
	gbus_write_uint32(pGBus, addr, length);

	return RM_OK;
}

/* set video_task_interface */
RMstatus video_set_vti_pointer(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 pvti_in)
{
	struct video_task_interface *pvti = (struct video_task_interface *)pvti_in;

	RMDBGLOG((LOCALDBG, "video_set_vti_pointer addr= 0x%lx pvti= 0x%lx\n", (RMuint32) &(pvtdb->Task_InterfacePtr), pvti_in));

	gbus_write_uint32(pGBus, (RMuint32) &(pvtdb->Task_InterfacePtr), pvti_in);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->Command), VIDEO_NO_CMD);
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->Status), VIDEO_UNINIT);

	return RM_OK;
}

/* set video_task_data_base */
RMstatus video_set_vtdb_pointer(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 index,
	RMuint32 pvtdb)
{
	RMuint32 addr;
	RMuint32 decoderHead = 0;
	struct task_entry* pEntry = 0;

	if (index >= MAX_TASK_COUNT)
		return RM_ERROR;

	decoderHead = gbus_read_uint32(pGBus, MemBase + SchedulerDataStart);
	decoderHead |= (gbus_read_uint32(pGBus, MemBase + SchedulerDataStart + 4) << 16);

	RMDBGLOG((LOCALDBG, "SchedulerDataStart = 0x%lx\n", decoderHead));

	addr 	= decoderHead + (index * sizeof(struct task_entry)) + sizeof(RMuint32);
	pEntry 	= (struct task_entry*)addr;

	gbus_write_uint32(pGBus, (RMuint32) &(pEntry->DataBasePtr), pvtdb);

	RMDBGLOG((LOCALDBG, "video_set_vtdb_pointer addr= 0x%lx pvtb= 0x%lx\n", addr, pvtdb));

	return RM_OK;
}

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
		size_address = (RMuint32) &(pvti->LumaFrameBuffer0.Size);
		break;
	case PICTURE_BUFFER_BANK_1:
		buffer_address = (RMuint32) &(pvti->LumaFrameBuffer1.StartAddress);
		size_address = (RMuint32) &(pvti->LumaFrameBuffer1.Size);
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
#else
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
#endif

/* set the pointer to bitstream fifo container, located in demux DMEM */
RMstatus video_set_bts_fifo_pointer(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 bts_fifo)
{
	RMDBGLOG((LOCALDBG, "video_set_bts_fifo_pointer= 0x%lx\n", bts_fifo));
	gbus_write_uint32(pGBus, (RMuint32) &(pvtdb->InputFifoPtr), bts_fifo);

	return RM_OK;
}

/* get the pointer to time stamp fifo container, allocated in DRAM */
RMstatus video_get_pts_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 *pts_fifo)
{
	*pts_fifo = (RMuint32) &(pvtdb->pts_fifo);
	RMDBGLOG((LOCALDBG, "video_get_pts_fifo= 0x%lx\n", *pts_fifo));

	return RM_OK;
}

/* initialize the time stamp fifo, allocated in DRAM, size in entries */
RMstatus video_open_pts_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size)
{
	RMDBGLOG((LOCALDBG, "video_open_pts_fifo= 0x%lx start= 0x%lx size= %lx\n",
		(RMuint32) &(pvtdb->pts_fifo), start, size));
	gbus_entry_fifo_open(pGBus, start, size, (RMuint32) &(pvtdb->pts_fifo));

	return RM_OK;
}
/* initialize the inband command fifo container, allocated in DRAM, size in entries */
RMstatus video_open_inband_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size)
{
	RMDBGLOG((LOCALDBG, "video_open_inband_fifo= 0x%lx start= 0x%lx size= %lx\n",
		(RMuint32) &(pvtdb->inband_cmd_fifo), start, size));
	gbus_entry_fifo_eraser_open(pGBus, start, size, (RMuint32) &(pvtdb->inband_cmd_fifo));

	return RM_OK;
}
/* get display data fifo container */
RMstatus video_get_display_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 *display_fifo)
{
	*display_fifo = (RMuint32) &(pvtdb->display_fifo);
	RMDBGLOG((LOCALDBG, "video_get_display_fifo = %lx\n", *display_fifo));

	return RM_OK;
}
/* get user data fifo container */
RMstatus video_get_user_data_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 *fifo)
{
	RMDBGLOG((LOCALDBG, "video_get_user_data_fifo: fifo=%lx\n", (RMuint32) &(pvtdb->user_data_fifo)));

	/* allocated size for this container is gbus_fifo_eraser - but the eraser is used only by microcode */
	*fifo = (RMuint32) &(pvtdb->user_data_fifo);

	return RM_OK;
}
RMstatus video_get_irq_info(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 *pevent_table_pointer)
{
	*pevent_table_pointer = (RMuint32) &(pvti->EventTablePointer);

	return RM_OK;
}
/* initialize user data fifo container, allocated in DRAM,  size in entries */
RMstatus video_open_user_data_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size)
{
	RMDBGLOG((LOCALDBG, "video_open_user_data_fifo: fifo= %lx start= %lx size= %lx\n",
		(RMuint32) &(pvtdb->user_data_fifo), start, size));
	if (size == 0)
		start = 0;

	/* allocated size for this container is gbus_fifo_eraser - but the eraser is used only by microcode */
	gbus_fifo_open(pGBus, start, size, (RMuint32) &(pvtdb->user_data_fifo));

	return RM_OK;
}

RMstatus video_open_error_code_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size)
{
	RMuint32 i;
	RMDBGLOG((LOCALDBG, "video_open_error_code_fifo: fifo= %lx start= %lx size= %lx\n",
		(RMuint32) &(pvtdb->error_code_fifo), start, size));

	gbus_entry_fifo_open(pGBus, start, size, (RMuint32) &(pvtdb->error_code_fifo));

	/* initialize the error codes */
	for (i=0; i< size*sizeof(struct EMhwlibVideoDecoder_DecodeError)/sizeof(RMuint32); i++)
		gbus_write_uint32(pGBus, start+4*i, 0);

	return RM_OK;
}

RMstatus video_set_extra_pictures(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMint32 extra_buffer_count)
{
	if (extra_buffer_count >= 0) {
		gbus_write_uint32(pGBus, (RMuint32) &(pvti->ExtraPictureBufferCount), extra_buffer_count);
		gbus_write_uint32(pGBus, (RMuint32) &(pvti->DisplayPictureBufferCount), 2);
	}
	else if (extra_buffer_count >= -2) {
		gbus_write_uint32(pGBus, (RMuint32) &(pvti->ExtraPictureBufferCount), 0);
		gbus_write_uint32(pGBus, (RMuint32) &(pvti->DisplayPictureBufferCount), 2 + extra_buffer_count);
	}
	else {
		RMDBGLOG((ENABLE, "video_set_extra_pictures error: %ld\n", extra_buffer_count));
		return RM_ERROR;
	}
	return RM_OK;
}

/* set video command: play, stop, iframe */
RMstatus video_set_command(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	enum VideoCommand command)
{
	RMDBGLOG((LOCALDBG, "***** %s: addr=0x%lx command=0x%lx\n", __FUNCTION__, (RMuint32) &(pvti->Command), command));
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->Command), command);

	return RM_OK;
}

/* get current video state. State reflects the previous command. */
RMstatus video_get_status(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	enum VideoStatus *status)
{
	*status = (VideoStatus)gbus_read_uint32(pGBus, (RMuint32) &(pvti->Status));
	RMDBGLOG((DISABLE, "video_get_status addr=0x%lx status=0x%lx\n", (RMuint32) &(pvti->Status), *status));

	return RM_OK;
}

/* set video profile: mpeg2, 4, wmv, .. */
RMstatus video_set_profile(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 profile)
{
	RMDBGLOG((LOCALDBG, "video_set_profile addr=0x%lx profile=0x%lx\n", (RMuint32) &(pvti->Profile), profile));
	gbus_write_uint32(pGBus, (RMuint32) &(pvti->Profile), profile);

	return RM_OK;
}

/* get current video profile */
RMstatus video_get_profile(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 *profile)
{
	*profile = gbus_read_uint32(pGBus, (RMuint32) &(pvti->Profile)) & VideoProfileMask;

	return RM_OK;
}

#ifdef __cplusplus
}
#endif // __cplusplus

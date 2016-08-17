#ifndef __VIDEO_UTILS_H__
#define __VIDEO_UTILS_H__

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"
#include "targetEngine.h"
#include "targetStandardInterface.h"

namespace video_utils {

RMstatus video_set_ucode_dram_offset(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 start_address);

RMstatus video_get_scheduler_memory(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 *pstart_address,
	RMuint32 *psize);

RMstatus video_set_scheduler_memory(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 start_address,
	RMuint32 size);

RMstatus video_set_display_error_threshold(
	controlInterface* pIF,
	RMuint32 pvti,
	RMuint32 threshold);

RMstatus video_set_anchor_propagation_parms(
	controlInterface* pIF,
	RMuint32 pvti,
	RMuint32 threshold, RMuint32 length);

RMstatus video_set_vti_pointer(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 pvti);

RMstatus video_set_vtdb_pointer(
	controlInterface* pIF,
	RMuint32 MemBase,
	RMuint32 index,
	RMuint32 pvtdb);

RMstatus video_set_data_context_buffer(
	controlInterface* pPF,
	RMuint32 pvti,
	RMuint32 start_address,
	RMuint32 total_size,
	RMuint32 context_size);

RMstatus video_set_picture_buffer(
	controlInterface* pIF,
	RMuint32 pvti, /* struct video_task_data_base *pvtdb, */
	RMuint32 id,
	RMuint32 address,
	RMuint32 size);

RMstatus video_get_pts_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 *pts_fifo);

RMstatus video_set_bts_fifo_pointer(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 bts_fifo);

RMstatus video_open_pts_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 start,
	RMuint32 size);

RMstatus video_open_inband_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 start,
	RMuint32 size);

RMstatus video_set_inband_param_addr(
    controlInterface* pIF,
    RMuint32 pvtdb,
    RMuint32 inband_param_addr);

RMstatus video_get_display_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 *display_fifo);

RMstatus video_get_irq_info(
	controlInterface* pIF,
	RMuint32          pvti,
	RMuint32*         pevent_table_pointer);

RMstatus video_get_user_data_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 *fifo);

RMstatus video_open_user_data_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 start,
	RMuint32 size);

RMstatus video_open_error_code_fifo(
	controlInterface* pIF,
	RMuint32 pvtdb,
	RMuint32 start,
	RMuint32 size);

RMstatus video_set_extra_pictures(
	controlInterface*   pIF,
	RMuint32            pvti,
	RMint32             extra_buffer_count);

RMstatus video_set_command(
	controlInterface* pIF,
	RMuint32 pvti,
	enum VideoCommand command);

RMstatus video_get_status(
	controlInterface* pIF,
	RMuint32 pvti,
	enum VideoStatus *status);

RMstatus video_set_profile(
	controlInterface* pIF,
	RMuint32 pvti,
	RMuint32 profile);

}



#endif // __VIDEO_UTILS_H__

#ifndef __VIDEO_UTILS_H__
#define __VIDEO_UTILS_H__

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"
#include "targetEngine.h"

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

}


#endif // __VIDEO_UTILS_H__


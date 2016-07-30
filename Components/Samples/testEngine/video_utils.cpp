#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "video_utils.h"

#ifdef _DEBUG
    #define LOCALDBG ENABLE
#else
    #define LOCALDBG DISABLE
#endif // _DEBUG

namespace video_utils {

#define RESOLVE_SYMBOL(sym)                                                     \
    (*pSymMgr)[(sym)]

/* set the DRAM address where the video microcode is loaded */
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
//	*psize = sizeof(struct scheduler_data);

    pDef = pIF->get_structdb()->get_structure("scheduler_data");
    if (pDef != nullptr) {
        *psize = pDef->size();
    }

	RMDBGLOG((LOCALDBG, "video_get_scheduler_memory: addr=0x%lx size=%ld bytes\n",
		*pstart_address, *psize));

	return RM_OK;
}
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "targetStandardInterface.h"
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


}

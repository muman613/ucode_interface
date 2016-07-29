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

	pGbus->gbus_write_uint32(MemBase + RESOLVE_SYMBOL("VDsp_CodeOffsetLo"), start_address & 0xFFFF);
	pGbus->gbus_write_uint32(MemBase + RESOLVE_SYMBOL("VDsp_CodeOffsetHi"), start_address >> 16);

	return RM_OK;
}

}

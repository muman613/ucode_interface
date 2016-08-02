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

#ifdef _DEBUG
#define LOCALDBG    ENABLE
#else
#define LOCALDBG    DISABLE
#endif // _DEBUG

using namespace video_utils;

targetStandardInterface::targetStandardInterface(TARGET_ENGINE_PTR pEngine)
:   targetInterfaceBase(pEngine)
{
    RMuint32 offset = 0;
    // ctor

    pEngine->get_ucode_offset(nullptr, &offset);

    m_pAlloc[0]->alloc(targetAllocator::ALLOC_DRAM, offset);

    m_pAlloc[0]->dump(std::cerr);
}

targetStandardInterface::~targetStandardInterface()
{
    // dtor
}

void targetStandardInterface::test_function()
{
    GBUS_PTR pGbus = m_pEngine[0]->get_gbusptr();

    pGbus->gbus_write_uint32(0x100000, 0xdeadbeef);
}

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

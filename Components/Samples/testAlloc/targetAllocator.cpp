#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
#include "targetAllocator.h"

#ifdef _DEBUG
#define LOCALDBG ENABLE
#else
#define LOCALDBG DISABLE
#endif // _DEBUG

#ifdef _DEBUG
static const char* szAllocType[] = {
    "ALLOC_PM",
    "ALLOC_DM",
    "ALLOC_DRAM",
};
#endif // _DEBUG

targetAllocator::targetAllocator(const PlatformEngine& engine)
:   m_valid(false)
{
    // ctor
    reset(engine);
}

targetAllocator::targetAllocator()
:   m_valid(false)
{
    // ctor
}

targetAllocator::~targetAllocator()
{
    // dtor
}

bool targetAllocator::valid()
{
    return m_valid;
}


/**
 *
 */

RMuint32 targetAllocator::alloc(allocType type, size_t size)
{
    RMuint32 pMemory = 0;
    RMuint32 alignedSize;

    RMDBGLOG((LOCALDBG, "%s(%s, %zu)\n", __PRETTY_FUNCTION__,
              szAllocType[type], size));

    alignedSize = (((size + 3) >> 2) << 2);

    switch (type) {
    case ALLOC_PM:
        pMemory = m_pmPtr;
        m_pmPtr += alignedSize;
        break;

    case ALLOC_DM:
        pMemory = m_dmPtr;
        m_dmPtr += alignedSize;
        break;

    case ALLOC_DRAM:
        pMemory = m_dramPtr;
        m_dramPtr += alignedSize;
        break;
    }

//    RMALIGNTO(pMemory, sizeof(RMuint32));

    return pMemory;
}

/**
 *
 */

void targetAllocator::reset()
{
    RMDBGLOG((LOCALDBG, "%()\n", __PRETTY_FUNCTION__));

    m_pmPtr   = m_pm.base;
    m_dmPtr   = m_dm.base;
    m_dramPtr = m_dram.base;

    return;
}

/**
 *
 */

void targetAllocator::reset(const PlatformEngine& engine)
{
    RMDBGLOG((LOCALDBG, "%(...)\n", __PRETTY_FUNCTION__));

    m_pm.base       = engine.get_pmBase();
    m_pm.size       = engine.get_pmSize();
    m_pm.width      = engine.get_pmWidth();

    m_dm.base       = engine.get_dmWidth();
    m_dm.size       = engine.get_dmSize();
    m_dm.width      = engine.get_dmWidth();

    m_dram.base     = engine.get_dramBase();
    m_dram.size     = engine.get_dramSize();
    m_dram.width    = engine.get_dramWidth();

    m_pmPtr         = m_pm.base;
    m_dmPtr         = m_dm.base;
    m_dramPtr       = m_dram.base;

    m_valid         = true;
}

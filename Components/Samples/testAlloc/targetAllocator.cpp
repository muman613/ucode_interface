#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
#include "targetAllocator.h"

targetAllocator::targetAllocator(const PlatformEngine& engine)
{
    // ctor
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
}

targetAllocator::~targetAllocator()
{
    // dtor
}

RMuint32 targetAllocator::alloc(allocType type, size_t size)
{
    RMuint32 pMemory = 0;
    RMuint32 alignedSize;

    alignedSize = (((size + 3) >> 2) << 2);

    printf("size = %zu aligned = %d\n", size, alignedSize);

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

    RMALIGNTO(pMemory, sizeof(RMuint32));

    return pMemory;
}

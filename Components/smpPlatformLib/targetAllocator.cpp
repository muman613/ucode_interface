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

using namespace std;

#ifdef _DEBUG
static const char* szAllocType[] = {
    "ALLOC_PM",
    "ALLOC_DM",
    "ALLOC_DRAM",
};
#endif // _DEBUG

targetAllocator::targetAllocator(const PlatformEngine& engine)
:   m_valid(false),
    m_tilesize(14)
{
    // ctor
    reset(engine);
}

targetAllocator::targetAllocator()
:   m_valid(false),
    m_tilesize(14)
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

RMuint32 targetAllocator::alloc(uint32_t type, size_t size)
{
    RMuint32 pMemory = 0;
    RMuint32 alignedSize;

    RMDBGLOG((LOCALDBG, "%s(%s, %zu)\n", __PRETTY_FUNCTION__,
              szAllocType[type & 0x03], size));

    alignedSize = (((size + 3) >> 2) << 2);

    switch (type & 0x3) {
    case ALLOC_PM:
        pMemory = m_pmPtr;
        m_pmPtr += alignedSize;
        break;

    case ALLOC_DM:
        pMemory = m_dmPtr;
        m_dmPtr += alignedSize;
        break;

    case ALLOC_DRAM:
        if (type & ALLOC_TILEALIGN) {
            m_dramPtr = RMALIGNTONEXT(m_dramPtr, m_tilesize);
            pMemory = m_dramPtr;
            m_dramPtr += alignedSize;
        } else if (type & ALLOC_PAGEALIGN) {
            m_dramPtr = RM_NEXT_PAGE_ALIGN(m_dramPtr);
            pMemory = m_dramPtr;
            m_dramPtr += alignedSize;
        } else {
            pMemory = m_dramPtr;
            m_dramPtr += alignedSize;
        }
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
    RMDBGLOG((LOCALDBG, "%s(...)\n", __PRETTY_FUNCTION__));

    m_pm.base       = engine.get_pmBase();
    m_pm.size       = engine.get_pmSize();
    m_pm.width      = engine.get_pmWidth();

    m_dm.base       = engine.get_dmBase();
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

void targetAllocator::dump(std::ostream& os)
{
    os << "PM    Base  : " << hex << uppercase << m_pm.base << endl;
    os << "DM    Base  : " << hex << uppercase << m_dm.base << endl;
    os << "DRAM  Base  : " << hex << uppercase << m_dram.base << endl;
    os << "PM    Ptr   : " << hex << uppercase << m_pmPtr << endl;
    os << "DM    Ptr   : " << hex << uppercase << m_dmPtr << endl;
    os << "DRAM  Ptr   : " << hex << uppercase << m_dramPtr << endl;

    return;
}
RMuint32 targetAllocator::pmPtr() const
{
    return m_pmPtr;
}

RMuint32 targetAllocator::dmPtr() const
{
    return m_dmPtr;
}

RMuint32 targetAllocator::dramPtr() const
{
    return m_dramPtr;
}

void targetAllocator::set_tile_size(int w, int h)
{
    RMDBGLOG((LOCALDBG, "%s(%d, %d)\n", __PRETTY_FUNCTION__, w, h));
    m_tilesize = w + h;
}

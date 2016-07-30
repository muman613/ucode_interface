#ifndef __TARGET_ALLOCATOR_H__
#define __TARGET_ALLOCATOR_H__

#include "platformDB/PlatformDatabase.h"


class targetAllocator {
public:
    enum allocType {
        ALLOC_PM,
        ALLOC_DM,
        ALLOC_DRAM,
    };

    targetAllocator(const PlatformEngine& engine);
    virtual ~targetAllocator();

    void            dump(std::ostream& os);

    RMuint32        alloc(allocType type, size_t size);

protected:
    struct targetMemSpec {
        RMuint32    base;
        RMuint32    size;
        RMuint32    width;
    };

    targetMemSpec   m_pm;
    targetMemSpec   m_dm;
    targetMemSpec   m_dram;

    RMuint32        m_pmPtr;
    RMuint32        m_dmPtr;
    RMuint32        m_dramPtr;

private:
};


#endif // __TARGET_ALLOCATOR_H__

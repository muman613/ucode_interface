#ifndef __TARGET_ALLOCATOR_H__
#define __TARGET_ALLOCATOR_H__

#include <iostream>
#include <memory>
#include "platformDB2/libplatformdb.h"


/**
 *
 */

class targetAllocator {
public:
    enum allocType {
        ALLOC_PM,
        ALLOC_DM,
        ALLOC_DRAM,
    };

    targetAllocator();
    targetAllocator(const PlatformEngine& engine);
    virtual ~targetAllocator();

    bool            valid();
    void            dump(std::ostream& os = std::cerr);

    void            reset();
    void            reset(const PlatformEngine& engine);

    RMuint32        alloc(allocType type, size_t size);

    RMuint32        pmPtr() const;
    RMuint32        dmPtr() const;
    RMuint32        dramPtr() const;

protected:
    struct targetMemSpec {
        RMuint32    base;
        RMuint32    size;
        RMuint32    width;
    };

    bool            m_valid;

    targetMemSpec   m_pm;
    targetMemSpec   m_dm;
    targetMemSpec   m_dram;

    RMuint32        m_pmPtr;
    RMuint32        m_dmPtr;
    RMuint32        m_dramPtr;

private:
};


typedef std::shared_ptr<targetAllocator>    TARGET_ALLOC_PTR;

#endif // __TARGET_ALLOCATOR_H__

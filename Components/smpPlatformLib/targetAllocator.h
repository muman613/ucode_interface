#ifndef __TARGET_ALLOCATOR_H__
#define __TARGET_ALLOCATOR_H__

#include <iostream>
#include <memory>
#include "platformDB2/libplatformdb.h"


/**
 *  Allocator object simplifies serial allocation of memory...
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

    /*! Is this allocator valid? */
    bool            valid();
    /*! Dump allocator status to the ostream. */
    void            dump(std::ostream& os = std::cerr);
    /*! Reset the allocator to initial state. */
    void            reset();
    /*! Reset the allocator to represent values from PlatformEngine. */
    void            reset(const PlatformEngine& engine);
    /*! Allocate size bytes from type memory. */
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

    bool            m_valid;                    ///< True if object is valid.

    targetMemSpec   m_pm;                       ///< PM Memory specification.
    targetMemSpec   m_dm;                       ///< DM Memory specification.
    targetMemSpec   m_dram;                     ///< DRAM Memory specification.

    RMuint32        m_pmPtr;                    ///< PM Memory Pointer.
    RMuint32        m_dmPtr;                    ///< DM Memory Pointer.
    RMuint32        m_dramPtr;                  ///< DRAM Memory Pointer.

private:
};


typedef std::shared_ptr<targetAllocator>    TARGET_ALLOC_PTR;

#endif // __TARGET_ALLOCATOR_H__

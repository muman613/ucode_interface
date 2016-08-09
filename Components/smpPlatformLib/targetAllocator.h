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
        ALLOC_PM = 0,
        ALLOC_DM = 1,
        ALLOC_DRAM = 2,
        ALLOC_TILEALIGN = 4,
        ALLOC_PAGEALIGN = 8,
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
    RMuint32        alloc(uint32_t flags, size_t size);

    RMuint32        pmPtr() const;
    RMuint32        dmPtr() const;
    RMuint32        dramPtr() const;

    void            set_tile_size(int w, int h);

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

    RMuint32        m_tilesize;
private:
};


typedef std::shared_ptr<targetAllocator>    TARGET_ALLOC_PTR;

#endif // __TARGET_ALLOCATOR_H__

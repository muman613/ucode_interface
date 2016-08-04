#ifndef	__PLATFORMBLOCK_H__
#define __PLATFORMBLOCK_H__

#include "PlatformTypes.h"
#include "PlatformChip.h"
#include "PlatformEngine.h"

#if (__cplusplus >= 201103L)
#include <memory>
#endif

class PlatformDatabase;
class PlatformChip;
class PlatformEngine;
class PlatformBlock;

typedef std::shared_ptr<PlatformChip> PLATFORM_CHIP_PTR;
//typedef std::shared_ptr<PlatformEngine> PLATFORM_ENGINE_PTR;

/**
 *  Block object represents one block on a chip. It contains an array of engines.
 */

class DLLSPEC PlatformBlock {
    public:
        PlatformBlock(STRING sBlockName,
                      wxUint32 resetReg,
                      REG_PAIR_VECTOR& hostintRegVec,
                      PLATFORM_CHIP_PTR parentChip);
        PlatformBlock(STRING sBlockName);
        PlatformBlock() {}
        virtual ~PlatformBlock();

        STRING		        get_block_name() const;
        size_t		        get_engine_count() const;
        void		        Dump(FILE* fOut = stdout);
        PLATFORM_ENGINE_PTR operator[](size_t index);
        wxUint32	        get_resetReg();
        REG_PAIR_VECTOR&    get_hostint_vector();

        const PLATFORM_CHIP_PTR get_parent() const;

    protected:
        friend class PlatformDatabase;
        friend class PlatformChip;

        void		        AddEngine(PLATFORM_ENGINE_PTR newEngine);
        void                Release();

        STRING			    m_blockName;
        ArrayOfEngines      m_engines;

        wxUint32            m_resetReg;
        REG_PAIR_VECTOR     m_hostintRegVec;

        PLATFORM_CHIP_PTR   m_parentChip;
};

#if (__cplusplus >= 201103L)
typedef std::shared_ptr<PlatformBlock> PLATFORM_BLOCK_PTR;
#else
typedef PlatformBlock* PLATFORM_BLOCK_PTR;
#endif

#if (defined(__WXGTK__) || defined(__WXMSW__))
WX_DECLARE_OBJARRAY(PLATFORM_BLOCK_PTR, ArrayOfBlocks);
#else
typedef std::vector<PLATFORM_BLOCK_PTR> ArrayOfBlocks;
#endif

#endif // __PLATFORMBLOCK_H__

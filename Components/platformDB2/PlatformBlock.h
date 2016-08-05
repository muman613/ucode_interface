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

        /*! Get the block name. */
        STRING		        get_block_name() const;
        /*! Get count of engines in block. */
        size_t		        get_engine_count() const;
        /*! Dump block information to output stream. */
        void		        Dump(FILE* fOut = stdout);
        /*! Retrieve the engine pointer for specified engine number. */
        PLATFORM_ENGINE_PTR operator[](size_t index);
        /*! Get the reset register offset. */
        wxUint32	        get_resetReg();
        /*! Get the host interrupt vector sequence. */
        REG_PAIR_VECTOR&    get_hostint_vector();
        /*! Return pointer to parent chip. */
        const PLATFORM_CHIP_PTR get_parent() const;

    protected:
        friend class PlatformDatabase;
        friend class PlatformChip;

        void		        AddEngine(PLATFORM_ENGINE_PTR newEngine);
        void                Release();

        STRING			    m_blockName;            ///< Block name.
        ArrayOfEngines      m_engines;              ///< Array of engines.

        wxUint32            m_resetReg;             ///< Gbus address of RESET.
        REG_PAIR_VECTOR     m_hostintRegVec;        ///< Host interrupt registers.

        PLATFORM_CHIP_PTR   m_parentChip;           ///< Pointer to the chip.
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

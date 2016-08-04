#ifndef	__PLATFORMCHIP_H__
#define __PLATFORMCHIP_H__

//#include "libplatformdb.h"
#include "PlatformBlock.h"
#include "PlatformEngine.h"

#if (__cplusplus >= 201103L)
#include <memory>
#endif

#include "PlatformBlock.h"
class PlatformDatabase;
class PlatformBlock;
typedef std::shared_ptr<PlatformBlock> PLATFORM_BLOCK_PTR;


/**
 *  Chip object contains an array of blocks.
 */

class DLLSPEC PlatformChip {
    public:
        PlatformChip(STRING sChipID, STRING sHWType = "RiscDSPHard", STRING sName = "");
        PlatformChip() {};
        PlatformChip(const PlatformChip& copy);
        virtual ~PlatformChip();

        STRING              get_chip_id() const;
        STRING              get_chip_name() const;

        STRING              get_hw_type() const;
        size_t              get_block_count() const;

        void                Dump(FILE* fOut = stdout);

        PLATFORM_BLOCK_PTR operator[](size_t index);
        PLATFORM_BLOCK_PTR operator[](STRING blockName);

        bool                GetBlockNames(STRING_VECTOR& sVec);

    protected:
        friend class PlatformDatabase;

        /*! Add a block to the block array. */
        void                AddBlock(PLATFORM_BLOCK_PTR newBlock);
        /*! Release all shared pointers */
        void                Release();

        STRING              m_ChipID;                     ///< String representing Chip ID.
        STRING              m_ChipName;                   ///< String representing Chip name.
        ArrayOfBlocks       m_blocks;                     ///< Array of blocks on chip.
        STRING              m_hwType;                     ///< String representing hw type.
};

#if (__cplusplus >= 201103L)
typedef std::shared_ptr<PlatformChip> PLATFORM_CHIP_PTR;
#else
typedef PlatformChip* PLATFORM_CHIP_PTR;
#endif

#if (defined(__WXGTK__) || defined(__WXMSW__))
WX_DECLARE_OBJARRAY(PLATFORM_CHIP_PTR, ArrayOfChips);
#else
typedef std::vector<PLATFORM_CHIP_PTR> ArrayOfChips;
#endif // __WXGTK__

#endif // __PLATFORMCHIP_H__

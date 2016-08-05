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

        /*! Get the chip ID string. */
        STRING              get_chip_id() const;
        /*! Get the chip name string. */
        STRING              get_chip_name() const;
        /*! Get the Hardware type string. */
        STRING              get_hw_type() const;
        /*! Get the count of blocks on this chip. */
        size_t              get_block_count() const;
        /*! Dump output to stream */
        void                Dump(FILE* fOut = stdout);
        /*! Get a list of block names on this chip */
        bool                GetBlockNames(STRING_VECTOR& sVec);

        PLATFORM_BLOCK_PTR operator[](size_t index);
        PLATFORM_BLOCK_PTR operator[](STRING blockName);

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

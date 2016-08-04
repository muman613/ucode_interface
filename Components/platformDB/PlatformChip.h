#ifndef	__PLATFORMCHIP_H__
#define __PLATFORMCHIP_H__

#include "libplatformdb.h"

class PlatformDatabase;

/**
 *  Chip object contains an array of blocks.
 */

class DLLSPEC PlatformChip {
    public:
        PlatformChip(STRING sChipID, STRING sHWType = "RiscDSPHard", STRING sName = "");
        PlatformChip() {};
        PlatformChip(const PlatformChip& copy);
        virtual ~PlatformChip();

        STRING get_chip_id() const;
        STRING get_hw_type() const;
        size_t get_block_count() const;

        void Dump(FILE* fOut = stdout);

        PlatformBlock operator[](size_t index);
        PlatformBlock operator[](STRING blockName);

    protected:
        friend class PlatformDatabase;

        /*! Add a block to the block array. */
        void AddBlock(PlatformBlock& newBlock);

        STRING        m_ChipID;                     ///< String representing Chip ID.
        STRING        m_ChipName;                   ///< String representing Chip name.
        ArrayOfBlocks m_blocks;                     ///< Array of blocks on chip.
        STRING        m_hwType;                     ///< String representing hw type.
};

#if (defined(__WXGTK__) || defined(__WXMSW__))
WX_DECLARE_OBJARRAY(PlatformChip,   ArrayOfChips);
#else
typedef std::vector<PlatformChip> ArrayOfChips;
#endif // __WXGTK__

#endif // __PLATFORMCHIP_H__

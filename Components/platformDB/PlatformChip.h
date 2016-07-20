#ifndef	__PLATFORMCHIP_H__
#define __PLATFORMCHIP_H__

#include "libplatformdb.h"

class DLLSPEC PlatformChip {
    public:
        PlatformChip(STRING sChipID, STRING sHWType = "RiscDSPHard", STRING sName = "");
        PlatformChip() {};
        PlatformChip(const PlatformChip& copy);
        virtual ~PlatformChip();

        STRING& get_chip_id() {
            return m_ChipID;
        }

        STRING& get_hw_type() {
            return m_hwType;
        }

        void AddBlock(PlatformBlock& newBlock);
        void Dump(FILE* fOut = stdout);

        size_t get_block_count();

        PlatformBlock operator[](size_t index);
        PlatformBlock operator[](STRING blockName);

    protected:
        STRING        m_ChipID;
        STRING        m_ChipName;
        ArrayOfBlocks m_blocks;
        STRING        m_hwType;
};

#if (defined(__WXGTK__) || defined(__WXMSW__))
WX_DECLARE_OBJARRAY(PlatformChip,   ArrayOfChips);
#else
typedef std::vector<PlatformChip> ArrayOfChips;
#endif // __WXGTK__

#endif // __PLATFORMCHIP_H__

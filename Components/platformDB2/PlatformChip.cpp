//#include "libplatformdb.h"
#include "PlatformTypes.h"
#include "PlatformChip.h"
#include "dbg_utils.h"

#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/arrimpl.cpp>
	WX_DEFINE_OBJARRAY(ArrayOfChips);
#endif

PlatformChip::PlatformChip(STRING sChipID, STRING sHWType, STRING sName)
:   m_ChipID(sChipID),
    m_ChipName(sName),
    m_hwType(sHWType)
{
    D(debug("PlatformChip::PlatformChip(%s, %s)\n",
            (const char*)sChipID.c_str(), (const char*)sHWType.c_str()));
}

PlatformChip::PlatformChip(const PlatformChip& copy)
:   m_ChipID(copy.m_ChipID),
//    m_blocks(copy.m_blocks),
    m_hwType(copy.m_hwType)
{
    D(debug("PlatformChip::PlatformChip(copy)\n"));
}

PlatformChip::~PlatformChip() {
    D(debug("PlatformChip::~PlatformChip()\n"));
    m_blocks.clear();
}

void PlatformChip::AddBlock(PLATFORM_BLOCK_PTR newBlock)
{
    D(debug("PlatformChip::AddBlock()\n"));
#if (defined(__WXGTK__) || defined(__WXMSW__))
    m_blocks.Add(newBlock);
#else
    m_blocks.push_back(newBlock);
#endif
}

PLATFORM_BLOCK_PTR PlatformChip::operator[](size_t index) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_blocks.Item(index);
#else
    return m_blocks[index];
#endif
}

PLATFORM_BLOCK_PTR PlatformChip::operator[](STRING blockID) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    for (size_t i = 0 ; i < m_blocks.GetCount() ; i++) {
        if (m_blocks[i]->get_block_name() == blockID) {
            return m_blocks[i];
        }
    }
#else
    for (size_t i = 0 ; i < m_blocks.size() ; i++) {
        if (m_blocks[i]->get_block_name() == blockID) {
            return m_blocks[i];
        }
    }
#endif

    PLATFORM_BLOCK_PTR nullBlock;
    return nullBlock;
}

void PlatformChip::Dump(FILE* fOut) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxFprintf(fOut, "Chip %s:\n", m_ChipID.c_str());
    if (m_blocks.GetCount() > 0) {
        for (size_t i = 0 ; i < m_blocks.GetCount() ; i++) {
            PlatformBlock   block;
            block = m_blocks.Item(i);

            wxFprintf(fOut, "Block : %s\n", block.get_block_name());
            block.Dump(fOut);
        }
    } else {
        wxFprintf(fOut, "-- no blocks defined!\n");
    }
#else   // __WXGTK__
    fprintf(fOut, "Chip %s:\n", m_ChipID.c_str());
    if (m_blocks.size() > 0) {
        for (size_t i = 0 ; i < m_blocks.size() ; i++) {
            PLATFORM_BLOCK_PTR block = m_blocks[i];

            fprintf(fOut, "Block : %s\n", block->get_block_name().c_str());
            block->Dump(fOut);
        }
    } else {
        fprintf(fOut, "-- no blocks defined!\n");
    }
#endif  // __WXGTK__
}

size_t PlatformChip::get_block_count() const {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_blocks.GetCount();
#else
    return m_blocks.size();
#endif // __WXGTK__
    return 0;
}

/**
 *  Return the Chip ID string.
 */

STRING PlatformChip::get_chip_id() const {
    return m_ChipID;
}

/**
 *  Return the "name" of the Chip.
 */

STRING PlatformChip::get_chip_name() const {
    return m_ChipName;
}

/**
 *  Return the Hardware type of the Chip.
 */

STRING PlatformChip::get_hw_type() const {
    return m_hwType;
}

/**
 *  Get all block names into a string vector.
 */

bool PlatformChip::GetBlockNames(STRING_VECTOR& sVec) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    if (m_blocks.GetCount() > 0) {
        for (size_t i = 0 ; i < m_blocks.GetCount() ; i++) {
            sVec.push_back( m_blocks[i]->get_block_name() );
        }
    }
#else
    if (m_blocks.size() > 0) {
        for (size_t i = 0 ; i < m_blocks.size() ; i++) {
            sVec.push_back( m_blocks[i]->get_block_name() );
        }
    }
#endif
    return ((sVec.size() > 0)?true:false);
}

/**
 *  Release all blocks.
 */

void PlatformChip::Release() {
    D(debug("%s\n", __PRETTY_FUNCTION__));

    for (size_t i = 0 ; i < get_block_count() ; i++) {
        m_blocks[i]->Release();
    }

    m_blocks.clear();
}

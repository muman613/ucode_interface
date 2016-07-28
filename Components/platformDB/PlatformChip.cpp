#include "libplatformdb.h"
#include "PlatformChip.h"

#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/arrimpl.cpp>
	WX_DEFINE_OBJARRAY(ArrayOfChips);
#endif

PlatformChip::PlatformChip(STRING sChipID, STRING sHWType, STRING sName)
:   m_ChipID(sChipID),
    m_ChipName(sName),
    m_hwType(sHWType)
{
    //D(debug("PlatformChip::PlatformChip(%s, %s)\n",
    //        (const char*)sChipID.c_str(), (const char*)sHWType.c_str()));
}

PlatformChip::PlatformChip(const PlatformChip& copy)
:   m_ChipID(copy.m_ChipID),
    m_blocks(copy.m_blocks),
    m_hwType(copy.m_hwType)
{
//    D(debug("PlatformChip::PlatformChip(copy)\n"));
}

PlatformChip::~PlatformChip() {
//    D(debug("PlatformChip::~PlatformChip()\n"));
}

void PlatformChip::AddBlock(PlatformBlock& newBlock)
{
//debug("PlatformChip::AddBlock()\n");
#if (defined(__WXGTK__) || defined(__WXMSW__))
    m_blocks.Add(newBlock);
#else
    m_blocks.push_back(newBlock);
#endif
}

PlatformBlock PlatformChip::operator[](size_t index) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_blocks.Item(index);
#else
    return m_blocks[index];
#endif
}

PlatformBlock PlatformChip::operator[](std::string blockID) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
//    return m_blocks.Item(index);
#pragma message "PlatformChip::operator[](std::string blockID) not implemented!"
#else
    for (size_t i = 0 ; i < m_blocks.size() ; i++) {
        if (m_blocks[i].get_block_name() == blockID) {
            return m_blocks[i];
        }
    }

    PlatformBlock nullBlock;
    return nullBlock;
#endif
}


void PlatformChip::Dump(FILE* fOut)
{
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
            PlatformBlock block = m_blocks[i];

            fprintf(fOut, "Block : %s\n", block.get_block_name().c_str());
            block.Dump(fOut);
        }
    } else {
        fprintf(fOut, "-- no blocks defined!\n");
    }
#endif  // __WXGTK__
}

size_t PlatformChip::get_block_count() {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_blocks.GetCount();
#else
    return m_blocks.size();
#endif // __WXGTK__
}

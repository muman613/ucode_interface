//#include "libplatformdb.h"
#include "dbg_utils.h"
#include "PlatformChip.h"
#include "PlatformBlock.h"

#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/arrimpl.cpp>
    WX_DEFINE_OBJARRAY(ArrayOfBlocks);
#endif

/**
 *  Platform block object contains a number of engines.
 */

PlatformBlock::PlatformBlock(STRING sBlockName, wxUint32 resetReg, REG_PAIR_VECTOR& hostintRegVec, PLATFORM_CHIP_PTR parentChip)
:   m_blockName(sBlockName),
    m_resetReg(resetReg),
    m_hostintRegVec(hostintRegVec),
    m_parentChip(parentChip)
{
    // ctor
    D(debug("PlatformBlock::PlatformBlock(%s, %d, ...)\n", (const char*)sBlockName.c_str(), resetReg ));
}

PlatformBlock::PlatformBlock(STRING sBlockName)
:   m_blockName(sBlockName),
    m_resetReg(0L),
    m_parentChip(0L)
{
    // ctor
    D(debug("PlatformBlock::PlatformBlock(%s)\n", (const char*)sBlockName.c_str()));
}


/**
 *  Platform block destructor.
 */

PlatformBlock::~PlatformBlock() {
    // dtor
    D(debug("PlatformBlock::~PlatformBlock()\n"));

    Release();
}

/**
 *  Add engine to block.
 *
 *  @param newEngine    Shared pointer to engine to add.
 */

void PlatformBlock::AddEngine(PLATFORM_ENGINE_PTR newEngine)
{
    D(debug("PlatformBlock::AddEngine(%p)\n", newEngine.get()));
#if (defined(__WXGTK__) || defined(__WXMSW__))
    m_engines.Add(newEngine);
#else
    m_engines.push_back(newEngine);
#endif
}

/**
 *  Return engine by index.
 */

PLATFORM_ENGINE_PTR PlatformBlock::operator[](size_t index) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_engines.Item(index);
#else
    return m_engines[index];
#endif
}

/**
 *  Get the blocks host interrupt address.
 */

REG_PAIR_VECTOR& PlatformBlock::get_hostint_vector() {
    return m_hostintRegVec;
}

/**
 *  Dump block contents to a file.
 *
 *  @param fOut FILE pointer to dump to.
 */

void PlatformBlock::Dump(FILE* fOut) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxFprintf(fOut, "Block %s on chip %s\n", m_blockName.c_str(),
            m_parentChip->get_chip_id().c_str());

    if (m_engines.GetCount() > 0) {
        for (size_t i = 0 ; i < m_engines.GetCount() ; i++)
            m_engines[i]->Dump(fOut);

        wxFprintf(fOut, "Reset Register @ 0x%08X\n", m_resetReg);

        REG_PAIR_VECTOR_ITER    regIter;

        for (regIter = m_hostintRegVec.begin() ;
             regIter != m_hostintRegVec.end() ;
             regIter++)
        {
            wxFprintf(fOut, "Host Interrupt : Address 0x%08X Value 0x%08X\n", (*regIter).first, (*regIter).second);
        }
    } else {
        wxFprintf(fOut, "-- no engines defined!\n");
    }
#else // __WXGTK__
    fprintf(fOut, "Block %s on chip %s\n", m_blockName.c_str(),
            m_parentChip->get_chip_id().c_str());

    if (m_engines.size() > 0) {
        for (size_t i = 0 ; i < m_engines.size() ; i++)
            m_engines[i]->Dump(fOut);

        fprintf(fOut, "Reset Register @ 0x%08X\n", m_resetReg);

        REG_PAIR_VECTOR_ITER    regIter;

        for (regIter = m_hostintRegVec.begin() ;
             regIter != m_hostintRegVec.end() ;
             regIter++)
        {
            fprintf(fOut, "Host Interrupt : Address 0x%08X Value 0x%08X\n", (*regIter).first, (*regIter).second);
        }
    }
#endif // __WXGTK__

    return;
}

/**
 *  Return the name of the block.
 */

STRING PlatformBlock::get_block_name() const {
    return m_blockName;
}

/**
 *  Return the count of engines on this block.
 */

size_t PlatformBlock::get_engine_count() const {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_engines.GetCount();
#else
    return m_engines.size();
#endif // __WXGTK__
}

/**
 *  Return address of RESET register.
 */

wxUint32 PlatformBlock::get_resetReg() {
    return m_resetReg;
}

/**
 *  Return a shared_ptr to the Chip object this block belongs to.
 */

const PLATFORM_CHIP_PTR PlatformBlock::get_parent() const {
    return m_parentChip;
}

/**
 *  Release all engines.
 */

void PlatformBlock::Release() {
    D(debug("%s()\n", __PRETTY_FUNCTION__));

#if (defined(__WXGTK__) || defined(__WXMSW__))
    m_engines.Clear();
#else
    m_engines.clear();
#endif

    return;
}

#include "libplatformdb.h"
#include "PlatformBlock.h"

#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/arrimpl.cpp>
    WX_DEFINE_OBJARRAY(ArrayOfBlocks);
#endif


PlatformBlock::PlatformBlock(STRING sBlockName, wxUint32 resetReg, REG_PAIR_VECTOR& hostintRegVec)
:   m_blockName(sBlockName),
    m_resetReg(resetReg),
    m_hostintRegVec(hostintRegVec)
{
    // ctor
//    D(debug("PlatformBlock::PlatformBlock(%s, %d, ...)\n", (const char*)sBlockName.c_str(), resetReg ));
}

PlatformBlock::PlatformBlock(STRING sBlockName)
:   m_blockName(sBlockName),
    m_resetReg(0L)
{
    // ctor
//    D(debug("PlatformBlock::PlatformBlock(%s)\n", (const char*)sBlockName.c_str()));
}


/**
 *
 */

PlatformBlock::~PlatformBlock() {
    // dtor
//    D(debug("PlatformBlock::~PlatformBlock()\n"));
}

void PlatformBlock::AddEngine(PlatformEngine& newEngine)
{
//    D(debug("PlatformBlock::AddEngine()\n"));

#if (defined(__WXGTK__) || defined(__WXMSW__))
    m_engines.Add(newEngine);
#else
    m_engines.push_back(newEngine);
#endif
}

PlatformEngine PlatformBlock::operator[](size_t index) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_engines.Item(index);
#else
    return m_engines[index];
#endif
}

REG_PAIR_VECTOR& PlatformBlock::get_hostint_vector() {
    return m_hostintRegVec;
}


void PlatformBlock::Dump(FILE* fOut)
{
#if (defined(__WXGTK__) || defined(__WXMSW__))
    if (m_engines.GetCount() > 0) {
        for (size_t i = 0 ; i < m_engines.GetCount() ; i++) {
            PlatformEngine   engine;
            engine = m_engines.Item(i);

            engine.Dump(fOut);
        }

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
    if (m_engines.size() > 0) {
        for (size_t i = 0 ; i < m_engines.size() ; i++) {
            PlatformEngine  engine = m_engines[i];
            engine.Dump(fOut);
        }

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

}

STRING PlatformBlock::get_block_name() {
    return m_blockName;
}

size_t PlatformBlock::get_engine_count() {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_engines.GetCount();
#else
    return m_engines.size();
#endif // __WXGTK__
}

wxUint32 PlatformBlock::get_resetReg() {
    return m_resetReg;
}

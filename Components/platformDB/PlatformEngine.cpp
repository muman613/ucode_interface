
#include "libplatformdb.h"
#include "PlatformEngine.h"

#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/arrimpl.cpp>
    WX_DEFINE_OBJARRAY(ArrayOfEngines);
#endif

/*--------------------------------------------------------------------------*/
/*  Platform Engine Class                                                   */
/*--------------------------------------------------------------------------*/

PlatformEngine::PlatformEngine(int engineNum,
                               wxUint32 ioBase,
                               wxUint32 pmBase,
                               wxUint32 pmSize,
							   wxUint32 pmWidth,
                               wxUint32 dmBase,
                               wxUint32 dmSize,
                               wxUint32 dmWidth,
                               wxUint32 dramBase,
                               wxUint32 dramSize,
							   wxUint32 dramWidth)
:   m_engineNum(engineNum),
    m_ioBase(ioBase),
    m_pmBase(pmBase),
    m_pmSize(pmSize),
	m_pmWidth(pmWidth),
    m_dmBase(dmBase),
    m_dmSize(dmSize),
    m_dmWidth(dmWidth),
    m_dramBase(dramBase),
    m_dramSize(dramSize),
	m_dramWidth(dramWidth)
{
#ifdef  _DEBUG
    fprintf(stderr, "PlatformEngine::PlatformEngine(%d,...)\n", engineNum);
    fprintf(stderr, "-- pmBase   0x%08X     pmSize 0x%08X   Width %d\n", pmBase, pmSize, pmWidth);
    fprintf(stderr, "-- dmBase   0x%08X     dmSize 0x%08X   Width %d\n", dmBase, dmSize, dmWidth);
    fprintf(stderr, "-- dramBase 0x%08X   dramSize 0x%08X   Width %d\n", dramBase, dramSize, dramWidth);
#endif
}

PlatformEngine::~PlatformEngine()
{
}

void PlatformEngine::Dump(FILE* fOut) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxFprintf(fOut,"Engine %d : pmBase 0x%08X pmSize 0x%08X pmWidth %d dmBase 0x%08X dmSize 0x%08X dwWidth %d dramBase 0x%08X dramSize 0x%08X dramWidth %d\n",
              get_engine_num(),
              get_pmBase(), get_pmSize(), get_pmWidth(),
              get_dmBase(), get_dmSize(), get_dmWidth(),
              get_dramBase(), get_dramSize(), get_dramWidth());
#else
    fprintf(fOut,"Engine %d : pmBase 0x%08X pmSize 0x%08X pmWidth %d dmBase 0x%08X dmSize 0x%08X dwWidth %d dramBase 0x%08X dramSize 0x%08X dramWidth %d\n",
              get_engine_num(),
              get_pmBase(), get_pmSize(), get_pmWidth(),
              get_dmBase(), get_dmSize(), get_dmWidth(),
              get_dramBase(), get_dramSize(), get_dramWidth());
#endif // __WXGTK__
}

int PlatformEngine::get_engine_num() {
    return m_engineNum;
}

wxUint32 PlatformEngine::get_ioBase() {
    return m_ioBase;
}

wxUint32 PlatformEngine::get_pmBase() {
    return m_pmBase;
}

wxUint32 PlatformEngine::get_pmSize() {
    return m_pmSize;
}

wxUint32 PlatformEngine::get_pmWidth() {
	return m_pmWidth;
}

wxUint32 PlatformEngine::get_dmBase() {
    return m_dmBase;
}

wxUint32 PlatformEngine::get_dmSize() {
    return m_dmSize;
}

wxUint32 PlatformEngine::get_dmWidth() {
    return m_dmWidth;
}

wxUint32 PlatformEngine::get_dramBase() {
    return m_dramBase;
}

wxUint32 PlatformEngine::get_dramSize() {
    return m_dramSize;
}

wxUint32 PlatformEngine::get_dramWidth() {
	return m_dramWidth;
}

#ifndef	__PLATFORMENGINE_H__
#define __PLATFORMENGINE_H__

#include "libplatformdb.h"


/**
 *
 */

class DLLSPEC PlatformEngine {
    public:
        PlatformEngine(int      engineNum,
                       wxUint32 ioBase,
                       wxUint32 pmBase,
                       wxUint32 pmSize,
					   wxUint32 pmWidth,
                       wxUint32 dmBase,
                       wxUint32 dmSize,
                       wxUint32 dmWidth,
                       wxUint32 dramBase,
                       wxUint32 dramSize,
					   wxUint32 dramWidth);

        PlatformEngine() {}
        virtual ~PlatformEngine();

        int			get_engine_num();
        wxUint32	get_ioBase();

        wxUint32	get_pmBase();
        wxUint32	get_pmSize();
		wxUint32	get_pmWidth();
		
        wxUint32	get_dmBase();
        wxUint32	get_dmSize();
		wxUint32	get_dmWidth();

        wxUint32	get_dramBase();
        wxUint32	get_dramSize();
		wxUint32	get_dramWidth();

        void		Dump(FILE* ofp);

    protected:
        int         m_engineNum;

        wxUint32    m_ioBase;

        wxUint32    m_pmBase;
        wxUint32    m_pmSize;
		wxUint32	m_pmWidth;

        wxUint32    m_dmBase;
        wxUint32    m_dmSize;
        wxUint32    m_dmWidth;

        wxUint32    m_dramBase;
        wxUint32    m_dramSize;
		wxUint32	m_dramWidth;
};

#if (defined(__WXGTK__) || defined(__WXMSW__))
WX_DECLARE_OBJARRAY(PlatformEngine, ArrayOfEngines);
#else
typedef std::vector<PlatformEngine>		ArrayOfEngines;
#endif // (defined(__WXGTK__) || defined(__WXMSW__))

#endif // __PLATFORMENGINE_H__
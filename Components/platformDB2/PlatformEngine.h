#ifndef	__PLATFORMENGINE_H__
#define __PLATFORMENGINE_H__

//#include "libplatformdb.h"
#include "PlatformBlock.h"

#if (__cplusplus >= 201103L)
#include <memory>
#endif


class PlatformBlock;
typedef std::shared_ptr<PlatformBlock> PLATFORM_BLOCK_PTR;


/**
 *  Platform engine describes a single engine on a block.
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
					   wxUint32 dramWidth,
					   PLATFORM_BLOCK_PTR parentBlock);

        PlatformEngine() {}
        virtual ~PlatformEngine();

        /*! Get the engine #. */
        int			get_engine_num() const;
        /*! Get the io base address. */
        wxUint32	get_ioBase() const;
        /*! Get PM base address. */
        wxUint32	get_pmBase() const;
        /*! Get PM size. */
        wxUint32	get_pmSize() const;
        /*! Get PM width. */
		wxUint32	get_pmWidth() const;
        /*! Get DM base address. */
        wxUint32	get_dmBase() const;
        /*! Get DM size. */
        wxUint32	get_dmSize() const;
        /*! Get DM width. */
		wxUint32	get_dmWidth() const;
        /*! Get DRAM base address. */
        wxUint32	get_dramBase() const;
        /*! Get DRAM size. */
        wxUint32	get_dramSize() const;
		/*! Get DRAM width. */
		wxUint32	get_dramWidth() const;

		void        set_pmBase(wxUint32 address);
		void        set_dmBase(wxUint32 address);
		void        set_dramBase(wxUint32 address);

        void		Dump(FILE* ofp = stderr);

        const PLATFORM_BLOCK_PTR get_parent() const;

    protected:
        friend class PlatformBlock;

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

		PLATFORM_BLOCK_PTR m_parentBlock;
};

#if (__cplusplus >= 201103L)
typedef std::shared_ptr<PlatformEngine> PLATFORM_ENGINE_PTR;
#else
typedef PlatformEngine* PLATFORM_ENGINE_PTR;
#endif

#if (defined(__WXGTK__) || defined(__WXMSW__))
WX_DECLARE_OBJARRAY(PLATFORM_ENGINE_PTR, ArrayOfEngines);
#else
typedef std::vector<PLATFORM_ENGINE_PTR>		ArrayOfEngines;
#endif // (defined(__WXGTK__) || defined(__WXMSW__))

#endif // __PLATFORMENGINE_H__

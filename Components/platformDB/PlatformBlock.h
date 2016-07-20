#ifndef	__PLATFORMBLOCK_H__
#define __PLATFORMBLOCK_H__

#include "libplatformdb.h"
#include "PlatformEngine.h"

class DLLSPEC PlatformBlock {
    public:
        PlatformBlock(STRING sBlockName, wxUint32 resetReg, REG_PAIR_VECTOR& hostintRegVec);
        PlatformBlock(STRING sBlockName);
        PlatformBlock() {}
        virtual ~PlatformBlock();

        STRING		get_block_name();
        size_t		get_engine_count();
        void		AddEngine(PlatformEngine& newEngine);
        void		Dump(FILE* fOut = stdout);
        PlatformEngine operator[](size_t index);
        wxUint32	get_resetReg();
        REG_PAIR_VECTOR&    get_hostint_vector();

    protected:
        STRING			m_blockName;
        ArrayOfEngines  m_engines;

        wxUint32        m_resetReg;
        REG_PAIR_VECTOR m_hostintRegVec;
};

#if (defined(__WXGTK__) || defined(__WXMSW__))
WX_DECLARE_OBJARRAY(PlatformBlock, ArrayOfBlocks);
#else
typedef std::vector<PlatformBlock> ArrayOfBlocks;
#endif

#endif // __PLATFORMBLOCK_H__

#ifndef	__PLATFORMBLOCK_H__
#define __PLATFORMBLOCK_H__

#include "libplatformdb.h"
#include "PlatformEngine.h"

class PlatformDatabase;

/**
 *  Block object represents one block on a chip. It contains an array of engines.
 */

class DLLSPEC PlatformBlock {
    public:
        PlatformBlock(STRING sBlockName, wxUint32 resetReg, REG_PAIR_VECTOR& hostintRegVec);
        PlatformBlock(STRING sBlockName);
        PlatformBlock() {}
        virtual ~PlatformBlock();

        STRING		get_block_name() const;
        size_t		get_engine_count() const;
        void		Dump(FILE* fOut = stdout);
        PlatformEngine operator[](size_t index);
        wxUint32	get_resetReg();
        REG_PAIR_VECTOR&    get_hostint_vector();

    protected:
        friend class PlatformDatabase;

        void		AddEngine(PlatformEngine& newEngine);

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

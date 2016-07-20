#ifndef __PLATFORMDATABASE_H__
#define __PLATFORMDATABASE_H__

#include "libplatformdb.h"

class DLLSPEC PlatformDatabase
{
    public:
        PlatformDatabase();
        virtual ~PlatformDatabase();


        void            Dump(FILE* fOut = stdout);

        bool            LoadDatabase(STRING sDbFilename,
                                     STRING sInstallPath = "");

        PlatformChip    operator[](size_t index);
        PlatformChip    operator[](STRING& sChipID);

        size_t          get_chip_count();

        bool            FindEngine(PlatformEngine& whichEngine,
                                   PlatformBlock& whichBlock,
                                   STRING chip,
                                   STRING block,
                                   int engine);

        bool            FindChip(PlatformChip& which, STRING chip);

		bool			GetChipNames(STRING_VECTOR& sVec);

        //Target*         MakeNewTarget(STRING name, STRING chip, STRING block, int engine);

    protected:
        void            AddChip(PlatformChip& newChip);
#if (defined(__WXGTK__) || defined(__WXMSW__))
        bool            HandleEngineNode(PlatformBlock* pBlock, XML_NODE& node);
#else
        bool            HandleEngineNode(PlatformBlock* pBlock, XML_NODE_PTR pNode);
#endif // __WXGTK__

        bool            parse_hostint_string(STRING hostIntStr, REG_PAIR_VECTOR& regVec);

    private:
        bool            m_bLoaded;
        ArrayOfChips    m_chips;
        STRING          m_dbVersion;
};

#endif // __PLATFORMDATABASE_H__
#ifndef __PLATFORMDATABASE_H__
#define __PLATFORMDATABASE_H__

//#include "libplatformdb.h"

#include "PlatformChip.h"

/**
 *  This object holds a database of all supported platforms and their memory
 *  ranges.
 */

class DLLSPEC PlatformDatabase
{
    public:
        PlatformDatabase();
        virtual ~PlatformDatabase();

        void            Dump(FILE* fOut = stdout);

        bool            LoadDatabase(STRING sDbFilename,
                                     STRING sInstallPath = "");

        PLATFORM_CHIP_PTR    operator[](size_t index);
        PLATFORM_CHIP_PTR    operator[](STRING& sChipID);

        /*! Return count of chips in database. */
        size_t          get_chip_count() const;

        bool            FindEngine(PlatformEngine& whichEngine,
                                   PlatformBlock& whichBlock,
                                   STRING chip,
                                   STRING block,
                                   int engine);

        bool            FindChip(PlatformChip& which, STRING chip);
        /*! Find block based on ChipID and Block name */
        bool            FindBlock(PlatformBlock& whichBlock, STRING sChipID, STRING sBlockID);

        /*! Return a vector of strings representing all chip ids in the database. */
		bool			GetChipIDs(STRING_VECTOR& sVec) const;
        /*! Return a vector of strings representing all chip names in the database. */
		bool			GetChipNames(STRING_VECTOR& sVec) const;
        /*! Return a vector of string pairs representing all chip ids and names in the database. */
		bool            GetChipPairs(STRING_PAIR_VECTOR& sVec) const;

    protected:
        /*! Add chip to the platform database. */
        void            AddChip(PLATFORM_CHIP_PTR newChip);

#if (defined(__WXGTK__) || defined(__WXMSW__))
        bool            HandleEngineNode(PLATFORM_BLOCK_PTR pBlock, XML_NODE& node);
#else
        bool            HandleEngineNode(PLATFORM_BLOCK_PTR pBlock, XML_NODE_PTR pNode);
#endif // __WXGTK__
        bool            parse_hostint_string(STRING hostIntStr, REG_PAIR_VECTOR& regVec);

        void            Release();

    private:
        bool            m_bLoaded;              ///< Is the database populated?
        ArrayOfChips    m_chips;                ///< Array holding chips.
        STRING          m_dbVersion;            ///< String representing db version.
};

#endif // __PLATFORMDATABASE_H__

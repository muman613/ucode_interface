#ifndef __PLATFORMDATABASE_H__
#define __PLATFORMDATABASE_H__

#include "libplatformdb.h"

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

        PlatformChip    operator[](size_t index);
        PlatformChip    operator[](STRING& sChipID);

        /*! Return count of chips in database. */
        size_t          get_chip_count() const;

        bool            FindEngine(PlatformEngine& whichEngine,
                                   PlatformBlock& whichBlock,
                                   STRING chip,
                                   STRING block,
                                   int engine);

        bool            FindChip(PlatformChip& which, STRING chip);

        /*! Return a vector of strings representing all chips in the database. */
		bool			GetChipNames(STRING_VECTOR& sVec) const;

    protected:
        /*! Add chip to the platform database. */
        void            AddChip(PlatformChip& newChip);
#if (defined(__WXGTK__) || defined(__WXMSW__))
        bool            HandleEngineNode(PlatformBlock* pBlock, XML_NODE& node);
#else
        bool            HandleEngineNode(PlatformBlock* pBlock, XML_NODE_PTR pNode);
#endif // __WXGTK__

        bool            parse_hostint_string(STRING hostIntStr, REG_PAIR_VECTOR& regVec);

    private:
        bool            m_bLoaded;              ///< Is the database populated?
        ArrayOfChips    m_chips;                ///< Array holding chips.
        STRING          m_dbVersion;            ///< String representing db version.
};

#endif // __PLATFORMDATABASE_H__

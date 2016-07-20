#ifndef __SYMBOLMGR_H__
#define __SYMBOLMGR_H__

#include "symboltypes.h"


class UcodeSymbolMgr {
public:
    UcodeSymbolMgr();
    UcodeSymbolMgr(const STRING sLabelHeader, Uint32 membase);
    virtual ~UcodeSymbolMgr();

    void            SetMemBase(Uint32 membase);
    Uint32          GetMemBase() const;

    bool            LoadSymbols(const STRING sLabelHeader);
    void            Clear();

    Uint32          operator[](STRING sSymbol);
    size_t          size() const;

    void            DumpSymbols(FILE* fOut = stdout);

    static bool     LoadMicrocodeSymbolsFromH(const STRING sLabelHeader,
                                              Uint32 memBase,
                                              SYMBOL_MAP& symMap);
protected:

    Uint32          m_memBase;
    SYMBOL_MAP      m_symMap;

private:
    static bool     file_exists(const STRING sFilename);

};

bool LoadMicrocodeSymbolsFromH(const STRING sLabelHeader,
                               Uint32 memBase,
                               SYMBOL_MAP& symMap);

#endif // __SYMBOLMGR_H__

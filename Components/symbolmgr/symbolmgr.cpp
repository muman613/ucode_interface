#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <exception>
#include <stdexcept>
#include "symbolmgr.h"
#include "dbgutils.h"

#define MAX_SYMBOL_LEN 1024


UcodeSymbolMgr::UcodeSymbolMgr()
:   m_memBase(0)
{

}

UcodeSymbolMgr::UcodeSymbolMgr(const STRING sLabelHeader, Uint32 memBase)
:   m_memBase(memBase)
{
    LoadSymbols(sLabelHeader);
}

UcodeSymbolMgr::~UcodeSymbolMgr()
{
    m_symMap.clear();
}

void UcodeSymbolMgr::Clear()
{
    m_symMap.clear();
}

void UcodeSymbolMgr::SetMemBase(Uint32 membase)
{
    m_memBase = membase;
}

Uint32 UcodeSymbolMgr::GetMemBase() const
{
    return m_memBase;
}

size_t UcodeSymbolMgr::size() const {
    return m_symMap.size();
}


bool UcodeSymbolMgr::LoadSymbols(const STRING sLabelHeader)
{
    return LoadMicrocodeSymbolsFromH(sLabelHeader, m_memBase, m_symMap);
}

Uint32 UcodeSymbolMgr::operator[](STRING sSymbol) {
//    Uint32 result = -1L;

    if (m_symMap.find(sSymbol) != m_symMap.end())
        return m_symMap[sSymbol];
    else {
        throw std::out_of_range("Index out of range");
    }
}

bool UcodeSymbolMgr::file_exists(const STRING sFilename)
{
    bool            result = false;
    struct stat     statbuf;

    if (stat( sFilename.c_str(), &statbuf ) == 0) {
        result = true;
    } else {
//      fprintf(stderr, "-- FILE DOES NOT EXIST!\n");
    }

//  fprintf(stderr, "result = %d\n", result);

    return result;
}

bool UcodeSymbolMgr::LoadMicrocodeSymbolsFromH(const STRING sLabelHeader,
                                               Uint32 memBase,
                                               SYMBOL_MAP& symMap)
{
    bool                    result = false;
    std::ifstream           ifHeader;
    STRING                  sLine;
    Uint32                  symbol_address;
    char                    define_name[MAX_SYMBOL_LEN];
    char                    symbol_name[MAX_SYMBOL_LEN];
    STRING                  sFoundPath;

    D(debug("probePaneMgr::LoadMicrocodeSymbolsFromH(%s) pmOffset 0x%08lx\n",
            sLabelHeader.c_str(), memBase));

//    assert(szLabelHeader != 0);
//    printf("-- loading microcode from header file %s\n", szLabelHeader);

    /* Find the file according to search rules */
    if (file_exists(sLabelHeader) == true) {
        D(debug("-- found header @ %s\n", sLabelHeader.c_str()));

        ifHeader.open( sLabelHeader.c_str() );

        if (ifHeader.is_open()) {
            while( ! ifHeader.eof() ) {
                getline( ifHeader, sLine );
                sscanf( sLine.c_str(), "%s %s %X", define_name, symbol_name, &symbol_address);
                if (strcmp( define_name, "#define" ) == 0) {

                    symbol_address += memBase;

#ifdef  DUMP_SYMBOLS
                    D(debug("Found symbol %s Value 0x%08x\n", symbol_name, symbol_address));
#endif

                    symMap[symbol_name] = symbol_address;

                }

                result = true;
            }
        } else {
            D(debug("ERROR: Unable to open header file %s\n", sLabelHeader.c_str()));
        }
    }

    return result;
}

/**
 *
 */

void UcodeSymbolMgr::DumpSymbols(FILE* fOut)
{
    for (SYMBOL_MAP_ITER it = m_symMap.begin() ; it != m_symMap.end() ; it++) {
        fprintf(fOut, "Symbol %s Value 0x%08X\n", it->first.c_str(), it->second);
    }
}

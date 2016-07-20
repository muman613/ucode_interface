#ifndef __SYMBOLTYPES_H__
#define __SYMBOLTYPES_H__

#include <string>
#include <vector>
#include <map>
#include <stdint.h>

typedef std::string                             STRING;
typedef uint32_t                                Uint32;

typedef std::map<STRING, Uint32>                SYMBOL_MAP;
typedef std::map<STRING, Uint32>::iterator      SYMBOL_MAP_ITER;
typedef std::pair<STRING, Uint32>               SYMBOL_PAIR;

#endif // __SYMBOLTYPES_H__


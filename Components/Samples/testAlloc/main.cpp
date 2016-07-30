#include <iostream>
#include <stdlib.h>
#include <string.h>

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
//#include "platformDB/PlatformDatabase.h"
#include "targetAllocator.h"

using namespace std;

int main()
{
    PlatformEngine engine(0, 0x80000,
                          0x100000, 0x2000, 4,
                          0x110000, 0x2000, 2,
                          0xa8000000, 0xefffffff, 4);
    targetAllocator     allocator(engine);
    RMuint32            address;

    address = allocator.alloc(targetAllocator::ALLOC_DRAM, 3);

    printf("Address %08x\n", address);

    address = allocator.alloc(targetAllocator::ALLOC_DRAM, 3);

    printf("Address %08x\n", address);

    return 0;
}

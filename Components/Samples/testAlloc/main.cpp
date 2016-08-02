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
#ifdef _DEBUG
    open_log_files("messages.txt", "errors.txt");
#endif // _DEBUG

    PlatformEngine engine(0, 0x80000,
                          0x100000, 0x2000, 4,
                          0x110000, 0x2000, 2,
                          0xa8000000, 0xefffffff, 4);
    targetAllocator     allocator(engine);
    RMuint32            address;

    address = allocator.alloc(targetAllocator::ALLOC_DRAM, 3);

    printf("Address %08x\n", address);

    address = allocator.alloc(targetAllocator::ALLOC_DRAM, 5);

    printf("Address %08x\n", address);

    address = allocator.alloc(targetAllocator::ALLOC_DRAM, 2);

    printf("Address %08x\n", address);

    TARGET_ALLOC_PTR     alloc2;

    alloc2 = std::make_shared<targetAllocator>();

    if (alloc2) {
        alloc2->reset( engine );

        address = alloc2->alloc(targetAllocator::ALLOC_DRAM, 3);
        printf("Address %08x\n", address);

        address = alloc2->alloc(targetAllocator::ALLOC_DRAM, 5);
        printf("Address %08x\n", address);

        address = alloc2->alloc(targetAllocator::ALLOC_DRAM, 2);
        printf("Address %08x\n", address);
    }

    return 0;
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ALLOW_OS_CODE
#include "targetEngine.h"
#include "targetStandardInterface.h"


targetStandardInterface::targetStandardInterface(TARGET_ENGINE_PTR pEngine)
:   targetInterfaceBase(pEngine)
{
    // ctor
}

targetStandardInterface::~targetStandardInterface()
{
    // dtor
}

void targetStandardInterface::test_function()
{
    GBUS_PTR pGbus = m_pEngine[0]->get_gbusptr();

    pGbus->gbus_write_uint32(0x100000, 0xdeadbeef);
}

#include <iostream>
#include <stdio.h>
#include <string.h>

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
#include "targetInterfaceBase.h"

#ifdef _DEBUG
#define LOCALDBG ENABLE
#else
#define LOCALDBG DISABLE
#endif // _DEBUG


targetInterfaceBase::targetInterfaceBase()
{
    // ctor
}

targetInterfaceBase::targetInterfaceBase(TARGET_ENGINE_PTR pEngine)
{
    // ctor
    set_target_engine(pEngine, 0);
}

targetInterfaceBase::~targetInterfaceBase()
{
    // dtor
}

void targetInterfaceBase::set_target_engine(TARGET_ENGINE_PTR pEngine, size_t index)
{
    RMDBGLOG((LOCALDBG, "%s(%p, %zu)\n", __PRETTY_FUNCTION__, pEngine.get(), index));

    if (index < MAX_ENGINES) {
        m_pEngine[index] = pEngine;
    } else {
        RMDBGLOG((LOCALDBG, "ERROR: index >= MAX_ENGINES!\n"));
    }
}

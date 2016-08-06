#ifndef __TARGET_INTERFACE_BASE_H__
#define __TARGET_INTERFACE_BASE_H__

#include <mutex>
#include <string>
#include <memory>
#include "targetEngine.h"
#include "targetAllocator.h"

#define MAX_ENGINES         2

class targetInterfaceBase {
public:
    targetInterfaceBase();
    targetInterfaceBase(TARGET_ENGINE_PTR pEngine);
    virtual ~targetInterfaceBase();

    void set_target_engine(TARGET_ENGINE_PTR pEngine, size_t index);

protected:
    TARGET_ENGINE_PTR       m_pEngine[MAX_ENGINES];
    TARGET_ALLOC_PTR        m_pAlloc[MAX_ENGINES];
};

#endif // __TARGET_INTERFACE_BASE_H__

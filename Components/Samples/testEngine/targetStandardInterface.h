#ifndef __TARGET_STD_INTERFACE_H__
#define __TARGET_STD_INTERFACE_H__

#include <memory>
#include "targetEngine.h"
#include "targetInterfaceBase.h"

class targetStandardInterface : public targetInterfaceBase
{
public:
    targetStandardInterface(TARGET_ENGINE_PTR pEngine);
    virtual ~targetStandardInterface();

    void        test_function();

protected:
};

typedef std::shared_ptr<targetStandardInterface>    TARGET_STD_IF;

#endif // __TARGET_STD_INTERFACE_H__

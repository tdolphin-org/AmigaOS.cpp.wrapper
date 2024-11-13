//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "GlobalSemaphoreScope.hpp"

#include <exec/semaphores.h>
#include <proto/exec.h>

namespace AOS::Exec
{
    GlobalSemaphoreScopeCore::GlobalSemaphoreScopeCore()
    {
        InitSemaphore(&mSignalSemaphore);
    }

    void GlobalSemaphoreScopeCore::Obtain()
    {
        ObtainSemaphore(&mSignalSemaphore);
    }

    void GlobalSemaphoreScopeCore::Release()
    {
        ReleaseSemaphore(&mSignalSemaphore);
    }
}

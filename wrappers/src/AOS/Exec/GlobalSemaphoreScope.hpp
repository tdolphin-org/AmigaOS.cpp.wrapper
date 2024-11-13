//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "Core/Singleton.hpp"

#include <exec/semaphores.h>

namespace AOS::Exec
{
    class GlobalSemaphoreScopeCore
    {
        friend class td::Singleton<GlobalSemaphoreScopeCore>;

        struct SignalSemaphore mSignalSemaphore;

        GlobalSemaphoreScopeCore();

      public:
        void Obtain();
        void Release();
    };

    typedef class td::Singleton<GlobalSemaphoreScopeCore> GlobalSemaphoreScope;
}

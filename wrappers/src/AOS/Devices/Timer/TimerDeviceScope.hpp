//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <devices/timer.h>

namespace AOS
{
    /// @brief Scope guard for the timer.device (UNIT_MICROHZ), functions-based
    class TimerDeviceScope
    {
        struct timerequest *mpTimerIO;

        char mOpenResult;

      public:
        TimerDeviceScope(bool exceptionOnError = true);
        ~TimerDeviceScope();
    };
}

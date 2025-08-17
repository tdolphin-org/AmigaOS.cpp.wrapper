//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "AOS/AmigaLib/MsgPortScope.hpp"
#include "AOS/AmigaLib/TimerIOReqScope.hpp"

namespace AOS
{
    /// @brief Scope guard for the timer.device (UNIT_MICROHZ), message-based
    class MsgTimerDeviceScope
    {
        AmigaLib::MsgPortScope mTimerMessagePortScope;
        AmigaLib::TimerIOReqScope mTimerIOReqScope;

        char mOpenResult;

      public:
        MsgTimerDeviceScope(bool exceptionOnError = true);
        ~MsgTimerDeviceScope();

        struct timerequest *timerReq() const
        {
            return mTimerIOReqScope.timerReq();
        }
    };
}

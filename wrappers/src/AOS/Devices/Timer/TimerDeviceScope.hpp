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
    class TimerDeviceScope
    {
        AmigaLib::MsgPortScope mPortScope;
        AmigaLib::TimerIOReqScope mTimerIOReqScope;

        char mOpenResult;

      public:
        TimerDeviceScope(bool exceptionOnError = true);
        ~TimerDeviceScope();

        struct timerequest *timerReq() const
        {
            return mTimerIOReqScope.timerReq();
        }
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <devices/timer.h>

namespace AOS::AmigaLib
{
    class TimerIOReqScope
    {
        struct timerequest *mpTimerReq;

      public:
        TimerIOReqScope(MsgPort *msgPort, bool exceptionOnError = true);
        ~TimerIOReqScope();

        struct timerequest *timerReq() const
        {
            return mpTimerReq;
        }
    };
}

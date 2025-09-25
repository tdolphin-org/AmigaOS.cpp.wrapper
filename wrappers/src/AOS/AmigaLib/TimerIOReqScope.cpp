//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "TimerIOReqScope.hpp"

#include <devices/timer.h>
#include <proto/alib.h>
#include <stdexcept>

namespace AOS::AmigaLib
{
    TimerIOReqScope::TimerIOReqScope(MsgPort *msgPort, bool exceptionOnError)
    {
        mpTimerReq = (struct timerequest *)CreateExtIO(msgPort, sizeof(struct timerequest));
        if (mpTimerReq == nullptr && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreateExtIO(..) failed!";
            throw std::runtime_error(error);
        }
    }

    TimerIOReqScope::~TimerIOReqScope()
    {
        if (mpTimerReq)
            DeleteExtIO((IORequest *)mpTimerReq);
    }
}

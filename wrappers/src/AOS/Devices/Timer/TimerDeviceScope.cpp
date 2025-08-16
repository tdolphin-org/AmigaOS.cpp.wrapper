//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "TimerDeviceScope.hpp"

#include <clib/exec_protos.h>
#include <stdexcept>

namespace AOS
{
    TimerDeviceScope::TimerDeviceScope(bool exceptionOnError)
      : mTimerIOReqScope(mPortScope.msgPort())
    {
        mOpenResult = OpenDevice(TIMERNAME, 0L, (IORequest *)mTimerIOReqScope.timerReq(), 0);
        if (mOpenResult != 0 && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " OpenDevice(\"" TIMERNAME "\", ...) failed!";
            throw std::runtime_error(error);
        }
    }

    TimerDeviceScope::~TimerDeviceScope()
    {
        if (mOpenResult == 0)
            CloseDevice((IORequest *)mTimerIOReqScope.timerReq());
    }
}

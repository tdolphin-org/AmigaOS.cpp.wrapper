//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "MsgTimerDeviceScope.hpp"

#include "TimerGlobals.hpp"

#include <clib/exec_protos.h>
#include <stdexcept>

namespace AOS
{
    MsgTimerDeviceScope::MsgTimerDeviceScope(bool exceptionOnError)
      : mTimerIOReqScope(mTimerMessagePortScope.msgPort())
    {
        mOpenResult = OpenDevice(TIMERNAME, UNIT_MICROHZ, (IORequest *)mTimerIOReqScope.timerReq(), 0);
        if (mOpenResult != 0 && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " OpenDevice(\"" TIMERNAME "\", ...) failed!";
            throw std::runtime_error(error);
        }

        TimerBase = (struct Device *)mTimerIOReqScope.timerReq()->tr_node.io_Device;
    }

    MsgTimerDeviceScope::~MsgTimerDeviceScope()
    {
        if (mOpenResult == 0)
        {
            if (!CheckIO((IORequest *)mTimerIOReqScope.timerReq()))
                AbortIO((IORequest *)mTimerIOReqScope.timerReq()); // Ask device to abort any pending requests
            WaitIO((IORequest *)mTimerIOReqScope.timerReq());
            CloseDevice((IORequest *)mTimerIOReqScope.timerReq());
        }
    }
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "TimerDevice.hpp"

#include <clib/timer_protos.h>

namespace AOS::Devices
{
    TimerDeviceCore::TimerDeviceCore()
    {
    }

    void TimerDeviceCore::devGetSysTime(struct timeval &tv) const
    {
        GetSysTime(&tv);
    }

    long TimerDeviceCore::devCmpTime(const struct timeval &tv1, const struct timeval &tv2) const
    {
        return CmpTime(&tv1, &tv2);
    }
}

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

    long TimerDeviceCore::TimeDiffMicroseconds(const struct timeval &tv1, const struct timeval &tv2) const
    {
        // Calculate difference: tv1 - tv2
        long secDiff = tv1.tv_secs - tv2.tv_secs;
        long microDiff = tv1.tv_micro - tv2.tv_micro;

        // Convert to microseconds: seconds * 1000000 + microseconds
        return secDiff * 1000000 + microDiff;
    }
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "TimerDevice.hpp"

#include <clib/timer_protos.h>

namespace AOS::Devices
{
    TimerDeviceCore::TimerDeviceCore() { }

    long TimerDeviceCore::devCmpTime(const timeval &tv1, const timeval &tv2) const
    {
        return CmpTime(&tv1, &tv2);
    }

    void TimerDeviceCore::devGetSysTime(timeval &tv) const
    {
        GetSysTime(&tv);
    }

    void TimerDeviceCore::devReadEClock(EClockVal &ec) const
    {
        ReadEClock(&ec);
    }

    long TimerDeviceCore::TimeDiffMicroseconds(const timeval &tv1, const timeval &tv2) const
    {
        // Calculate difference: tv1 - tv2
        long secDiff = tv1.tv_secs - tv2.tv_secs;
        long microDiff = tv1.tv_micro - tv2.tv_micro;

        // Convert to microseconds: seconds * 1000000 + microseconds
        return secDiff * 1000000 + microDiff;
    }
}

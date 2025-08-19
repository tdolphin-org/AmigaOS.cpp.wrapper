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

    long TimerDeviceCore::TimeDiffMicroseconds(const timeval &tvStart, const timeval &tvStop) const
    {
        // Calculate difference: tvStop - tvStart
        long secDiff = tvStop.tv_secs - tvStart.tv_secs;
        long microDiff = tvStop.tv_micro - tvStart.tv_micro;

        // Convert to microseconds: seconds * 1000000 + microseconds
        return secDiff * 1000000 + microDiff;
    }

    long long TimerDeviceCore::EClockDiff(const EClockVal &ecStart, const EClockVal &ecStop) const
    {
        long long t1 = ((long long)ecStart.ev_hi << 32) | ecStart.ev_lo;
        long long t2 = ((long long)ecStop.ev_hi << 32) | ecStop.ev_lo;
        long long diff = t2 - t1;

        return diff;
    }

    long TimerDeviceCore::devCmpTime(const timeval &tv1, const timeval &tv2) const
    {
        return CmpTime(&tv1, &tv2);
    }

    void TimerDeviceCore::devGetSysTime(timeval &tv) const
    {
        GetSysTime(&tv);
    }

    unsigned long TimerDeviceCore::devReadEClock(EClockVal &ec) const
    {
        return ReadEClock(&ec);
    }
}

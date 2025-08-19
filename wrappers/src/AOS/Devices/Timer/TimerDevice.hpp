//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "Core/Singleton.hpp"

#include "TimerDeviceScope.hpp"

#include <string>

namespace AOS::Devices
{
    /// @brief for applications which only use the timer device functions
    class TimerDeviceCore
    {
        friend class td::Singleton<TimerDeviceCore>;

        TimerDeviceScope mTimerDeviceScope;

        TimerDeviceCore();

      public:
        /// @brief Calculate difference in microseconds between two time values.
        /// @param tv1 The first time value.
        /// @param tv2 The second time value.
        /// @return difference in microseconds (tv1 - tv2)
        long TimeDiffMicroseconds(const timeval &tv1, const timeval &tv2) const;

        /// @brief timer.device/CmpTime(..) -- Compare two timeval structures.
        /// @param tv1 The first time value.
        /// @param tv2 The second time value.
        /// @return result will be
        ///         0 if Dest has same time as source,
        ///         -1 if Dest has more time than source,
        ///         +1 if Dest has less time than source
        /// @note This function may be called from interrupts.
        long devCmpTime(const timeval &tv1, const timeval &tv2) const;

        /// @brief timer.device/GetSysTime(..) -- Get the system time.
        ///        Ask the system what time it is. The system time starts off at
        ///        zero at power on, but may be initialized via the TR_SETSYSTIME
        ///        timer.device command.
        ///        System time is monotonically increasing and guaranteed to be
        ///        unique (except when the system time is set back).
        /// @param tv The time value to fill.
        /// @note This function may be called from interrupts.
        void devGetSysTime(timeval &tv) const;

        /// @brief timer.device/ReadEClock(..) -- Get the current value of the E-Clock.
        ///        This routine calculates the current 64 bit value of the E-Clock
        ///        and stores it in the destination EClockVal structure. The count
        ///        rate of the E-Clock is also returned.
        /// @attention This is a low overhead function designed so that very short
        ///        intervals may be timed.
        /// @param ec The EClock value to fill.
        /// @note This function may be called from interrupts.
        void devReadEClock(EClockVal &ec) const;
    };

    /// @brief main TimerDevice (singleton) object
    typedef class td::Singleton<TimerDeviceCore> TimerDevice;
}

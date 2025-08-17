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
        long TimeDiffMicroseconds(const struct timeval &tv1, const struct timeval &tv2) const;

        /// @brief Ask the system what time it is.  The system time starts off at
        ///        zero at power on, but may be initialized via the TR_SETSYSTIME
        ///        timer.device command.
        ///        System time is monotonically increasing and guaranteed to be
        ///        unique (except when the system time is set back).
        /// @param tv The time value to fill.
        /// @note This function may be called from interrupts.
        void devGetSysTime(struct timeval &tv) const;

        /// @brief Compare two time values.
        /// @param tv1 The first time value.
        /// @param tv2 The second time value.
        /// @return result will be
        ///         0 if Dest has same time as source,
        ///         -1 if Dest has more time than source,
        ///         +1 if Dest has less time than source
        /// @note This function may be called from interrupts.
        long devCmpTime(const struct timeval &tv1, const struct timeval &tv2) const;
    };

    /// @brief main TimerDevice (singleton) object
    typedef class td::Singleton<TimerDeviceCore> TimerDevice;
}

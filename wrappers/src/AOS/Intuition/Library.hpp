//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <optional>
#include <string>
#include <vector>

namespace AOS::Intuition
{
    struct Monitor
    {
        std::string name; // monitor name
        std::string driverName;
        std::string manufacturerName;
        unsigned long manufacturerId; // as in PCI ID
        unsigned long productId; // as in PCI ID
        unsigned long memorySize; // in Bytes
        std::optional<unsigned long> memoryClock; // in Hz when available
        std::optional<unsigned long> engineClock; // in Hz when available
    };

    struct Library
    {
        /// @brief intuition:GetMonitorList()
        /// @param removeMultiMonitor If true, only the first monitor of multi-monitor setups is returned.
        /// like RadeonX1650.monitor and RadeonX1650.monitor.1, only RadeonX1650.monitor is returned.
        /// this is done by checking for .x suffixes. At least related to MorphOS behavior.
        /// @return A vector of Monitor structures.
        static std::vector<Monitor> libGetMonitorList(const bool removeMultiMonitor = false);
    };
}

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
        // @brief intuition:GetMonitorList()
        static std::vector<Monitor> libGetMonitorList();
    };
}

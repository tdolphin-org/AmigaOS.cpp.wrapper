//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "ValueTypes/BaseClass.hpp"

#include <optional>
#include <vector>

namespace AOS::PCIX
{
    struct Board
    {
        unsigned long vendorId;
        unsigned long deviceId;
        unsigned long classId;
        std::optional<unsigned long> subsystemVendorId { std::nullopt };
        std::optional<unsigned long> subsystemId { std::nullopt };
        std::optional<unsigned long> subclassId { std::nullopt };
    };

    struct Library
    {
        /// @brief get all pci boards
        /// @param classes filter by base classes
        /// @return vector of boards
        static std::vector<Board> GetBoards(const std::vector<BaseClass> &classes = {}) noexcept;
    };
}

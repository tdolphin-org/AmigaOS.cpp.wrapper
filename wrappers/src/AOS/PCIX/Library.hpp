//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "ValueTypes/BaseClass.hpp"
#include "ValueTypes/BoardAttribute.hpp"

#include <optional>
#include <vector>
#include <variant>

namespace AOS::PCIX
{
    using BoardObject = void *;

    struct Board
    {
        BoardObject boardObject;

        unsigned long vendorId;
        unsigned long deviceId;
        unsigned long classId;
        std::optional<unsigned long> subsystemVendorId { std::nullopt };
        std::optional<unsigned long> subsystemId { std::nullopt };
        std::optional<unsigned long> subclassId { std::nullopt };

        struct
        {
            std::optional<unsigned char *> romAddress { std::nullopt };
            std::optional<unsigned long> romSize { std::nullopt };
        } attributes;
    };

    struct Library
    {
        /// @brief get all pci boards
        /// @param classes filter by base classes
        /// @return vector of boards
        static std::vector<Board> GetBoards(const std::vector<BaseClass> &classes = { }) noexcept;

        /// @brief pcix.library/PCIXGetBoardAttr
        static std::variant<unsigned long, unsigned char *> libGetBoardAttr(const Board &board, const BoardAttribute attr) noexcept;
    };
}

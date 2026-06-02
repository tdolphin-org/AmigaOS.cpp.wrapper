//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "ValueTypes/BaseClass.hpp"
#include "ValueTypes/BoardAttribute.hpp"

#include <variant>
#include <vector>

namespace AOS::PCIX
{
    using BoardObject = void *;

    struct Board
    {
        BoardObject boardObject;

        unsigned long vendorId;
        unsigned long deviceId;
        unsigned long classId;
        unsigned long subsystemVendorId;
        unsigned long subsystemId;
        unsigned long subclassId;

        struct
        {
            unsigned char *romAddress { nullptr };
            unsigned long romSize { 0 };
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

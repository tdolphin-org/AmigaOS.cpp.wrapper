//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "ValueTypes/BaseClass.hpp"
#include "ValueTypes/BoardAttribute.hpp"

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace AOS::PCIX
{
    using BoardObject = void *;

    struct BoardAttributes
    {
        unsigned long busNumber { 0 };
        std::string bridgeName { };
        unsigned long deviceNumber { 0 };
        unsigned long functionNumber { 0 };
        unsigned char *romAddress { nullptr };
        unsigned long romSize { 0 };
        unsigned long baseAddress0 { 0 };
        unsigned long baseAddress1 { 0 };
        unsigned long baseAddress2 { 0 };
        unsigned long baseAddress3 { 0 };
        unsigned long baseAddress4 { 0 };
        unsigned long baseAddress5 { 0 };
        unsigned long baseSize0 { 0 };
        unsigned long baseSize1 { 0 };
        unsigned long baseSize2 { 0 };
        unsigned long baseSize3 { 0 };
        unsigned long baseSize4 { 0 };
        unsigned long baseSize5 { 0 };
    };

    struct Board
    {
        BoardObject boardObject;

        unsigned long vendorId;
        unsigned long deviceId;
        unsigned long classId;
        unsigned long subsystemVendorId;
        unsigned long subsystemId;
        unsigned long subclassId;
    };

    struct Library
    {
        /// @brief get all pci boards
        /// @param classes filter by base classes
        /// @return vector of boards
        static std::vector<Board> GetBoards(const std::vector<BaseClass> &classes = { }) noexcept;

        /// @brief get board attributes
        /// @param board
        /// @return board attributes, or std::nullopt if the board is invalid
        static std::optional<BoardAttributes> GetBoardAttributes(const Board &board) noexcept;

        /// @brief calls pcix.library/PCIXGetBoardAttr
        static std::variant<unsigned long, unsigned char *, std::string> libGetBoardAttr(const Board &board,
                                                                                         const BoardAttribute attr) noexcept;
    };
}

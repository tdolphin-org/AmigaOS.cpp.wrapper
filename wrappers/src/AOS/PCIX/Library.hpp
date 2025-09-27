//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <vector>
#include <optional>

namespace AOS::PCIX
{
    struct Board
    {
        unsigned long vendorId;
        unsigned long deviceId;
        std::optional<unsigned long> subvendorId { std::nullopt };
        std::optional<unsigned long> subdeviceId { std::nullopt };
    };
    
    
    struct Library
    {
        /// @brief get alll pci boards
		static std::vector<Board> GetBoards() noexcept;
    };
}

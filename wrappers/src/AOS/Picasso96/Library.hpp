//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#ifdef __AROS__
#error "AOS::Picasso96 wrapper is not available on AROS - Picasso96 library does not exist on AROS"
#endif

#include "AOS/Common/ValueTypes/BoardID.hpp"

#include <string>
#include <vector>

namespace AOS::Picasso96
{
    struct Board
    {
        Common::BoardID id;
        std::string name;
        std::string chip;
        std::string memorySize;
        std::string usedMemory;
        long freeMemoryPercent;
        std::string memoryClock;
        std::vector<std::string> rgbFormats;
    };

    struct Library
    {
        static std::vector<Board> GetBoards() noexcept;
    };
}

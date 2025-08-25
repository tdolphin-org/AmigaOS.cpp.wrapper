//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

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

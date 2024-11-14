//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <string>
#include <vector>

namespace AOS::Picasso96
{
    struct Board
    {
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

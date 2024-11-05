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
        std::string memorySize;
        std::string memoryClock;
    };

    struct Library
    {
        static std::vector<Board> GetBoards() noexcept;
    };
}

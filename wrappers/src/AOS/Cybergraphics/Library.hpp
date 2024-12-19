//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "ValueTypes/BoardID.hpp"

#include <string>
#include <vector>

namespace AOS::Cybergraphics
{
    struct Library
    {
        static std::vector<BoardID> GetBoards() noexcept;

        /// @brief cgx:BestCModeIDTagList(boardID) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const enum BoardID boardID) noexcept;
    };
}

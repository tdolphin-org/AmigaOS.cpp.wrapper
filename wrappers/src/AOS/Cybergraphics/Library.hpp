//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "AOS/Common/ValueTypes/BoardID.hpp"

#include <string>
#include <vector>

namespace AOS::Cybergraphics
{
    struct Library
    {
        static std::vector<Common::BoardID> GetBoards() noexcept;

        /// @brief cgx:BestCModeIDTagList(monitorID) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const unsigned long monitorID) noexcept;
        /// @brief cgx:BestCModeIDTagList(boardName) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const std::string &boardName) noexcept;
    };
}

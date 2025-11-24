//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "AOS/Common/ValueTypes/BoardID.hpp"

#include <graphics/rastport.h>

#include <string>
#include <vector>

struct RastPort;

namespace AOS::Cybergraphics
{
    struct Library
    {
        static std::vector<Common::BoardID> GetBoards() noexcept;

        /// @brief cgx:FillPixelArray(rastPort, destX, destY, sizeX, sizeY, ARGB)
        /// fill a rectangular area with the supplied ARGB value starting at a specified x, y location and continuing through to another x,
        /// y location within a certain RastPort
        /// @param ARGB The desired color in AARRGGBB format for true color rastports or in indexed mode for CLUT rastports.
        /// For CLUT rastports only the blue component is used as an index value to a 256 colour lookup table
        /// @return The number of pixels filled
        static unsigned long libFillPixelArray(const RastPort &rastPort, const unsigned short destX, const unsigned short destY,
                                               const unsigned short sizeX, const unsigned short sizeY, const unsigned long ARGB) noexcept;

        /// @brief cgx:BestCModeIDTagList(monitorID) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const unsigned long monitorID) noexcept;
        /// @brief cgx:BestCModeIDTagList(boardName) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const std::string &boardName) noexcept;
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <string>
#include <vector>

namespace AOS::Cybergraphics
{
    enum class BoardID : unsigned long
    {
        CVision64 = 1,
        Piccolo = 2,
        PicassoII = 3,
        Spectrum = 4,
        Domino = 5,
        RetinaZ3_DraCoAltais = 6,
        PiccoSD64 = 7,
        A2410 = 8,
        CVision3D = 13,
        Inferno = 14,
        PicassoIV = 15,
        CyberVisonPPC = 16,
        BVisonPPC = 17,
    };

    struct Board
    {
        std::string name;
        std::string manufacturer;
        std::string chip;
        std::string memorySize;
        int premiere; // year
        std::string interface;
    };

    struct Library
    {
        static std::vector<Board> GetBoards() noexcept;

        /// @brief cgx:BestCModeIDTagList(boardID) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const enum BoardID boardID) noexcept;
    };
}

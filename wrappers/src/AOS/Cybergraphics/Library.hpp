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
    struct BoardName
    {
        static std::string CyberVision64;
        static std::string Piccolo;
        static std::string PicassoII;
        static std::string Spectrum;
        static std::string Domino;
        static std::string RetinaZ3;
        static std::string DraCoAltais;
        static std::string PiccoSD64;
        static std::string A2410;
        static std::string CyberVision3D;
        static std::string Inferno;
        static std::string PicassoIV;
        static std::string Pixel64;
        static std::string RainbowIII;
        static std::string CyberVisonPPC;
        static std::string BlizzardVisionPPC;
    };

    struct Library
    {
        static std::vector<BoardID> GetBoards() noexcept;

        /// @brief cgx:BestCModeIDTagList(monitorID) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const unsigned long monitorID) noexcept;
        /// @brief cgx:BestCModeIDTagList(boardName) and return mode id or 0 if not exists
        static unsigned long libBestCModeID(const std::string &boardName) noexcept;
    };
}

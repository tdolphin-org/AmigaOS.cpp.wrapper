//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include "AOS/TagsScope.hpp"

#include <cybergraphx/cybergraphics.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>

#include <map>

extern struct Library *CyberGfxBase;

namespace AOS::Cybergraphics
{
    std::string BoardName::CyberVision64 = "CVision64";
    std::string BoardName::Piccolo = "Piccolo";
    std::string BoardName::PicassoII = "PicassoII";
    std::string BoardName::Spectrum = "Spectrum";
    std::string BoardName::Domino = "Domino";
    std::string BoardName::RetinaZ3 = "RetinaZ3";
    std::string BoardName::DraCoAltais = "DraCoAltais";
    std::string BoardName::PiccoSD64 = "PiccoSD64";
    std::string BoardName::A2410 = "A2410";
    std::string BoardName::CyberVision3D = "CVision3D";
    std::string BoardName::Inferno = "Inferno";
    std::string BoardName::PicassoIV = "PicassoIV";
    std::string BoardName::Pixel64 = "Pixel64";
    std::string BoardName::RainbowIII = "RainbowIII";
    std::string BoardName::CyberVisonPPC = "CVisionPPC";
    std::string BoardName::BlizzardVisionPPC = "BVisionPPC";

    const std::map<BoardID, std::string &> allBoards {
        { BoardID::CyberVision64, BoardName::CyberVision64 },
        { BoardID::Piccolo, BoardName::Piccolo },
        { BoardID::PicassoII, BoardName::PicassoII },
        { BoardID::Spectrum, BoardName::Spectrum },
        { BoardID::Domino, BoardName::Domino },
        { BoardID::RetinaZ3, BoardName::RetinaZ3 },
        { BoardID::DraCoAltais, BoardName::DraCoAltais },
        { BoardID::PiccoSD64, BoardName::PiccoSD64 },
        { BoardID::A2410, BoardName::A2410 },
        { BoardID::CyberVision3D, BoardName::CyberVision3D },
        { BoardID::Inferno, BoardName::Inferno },
        { BoardID::PicassoIV, BoardName::PicassoIV },
        { BoardID::Pixel64, BoardName::Pixel64 },
        { BoardID::RainbowIII, BoardName::RainbowIII },
        { BoardID::CyberVisonPPC, BoardName::CyberVisonPPC },
        { BoardID::BlizzardVisionPPC, BoardName::BlizzardVisionPPC },
    };

    std::vector<BoardID> Library::GetBoards() noexcept
    {
        std::vector<BoardID> boards;
        for (const auto &board : allBoards)
            if (libBestCModeID(board.second) != (unsigned long)INVALID_ID)
                boards.push_back(board.first);

        return boards;
    }

    unsigned long Library::libBestCModeID(const unsigned long monitorID) noexcept
    {
        TagsScope tagsScope({ { CYBRBIDTG_MonitorID, monitorID } });
        return BestCModeIDTagList(tagsScope.tagItems());
    }

    unsigned long Library::libBestCModeID(const std::string &boardName) noexcept
    {
        TagsScope tagsScope({ { CYBRBIDTG_BoardName, boardName.c_str() } });
        return BestCModeIDTagList(tagsScope.tagItems());
    }
}

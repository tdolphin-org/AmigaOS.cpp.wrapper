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
    static std::string CyberVision64 = "CVision64";
    static std::string Piccolo = "Piccolo";
    static std::string PicassoII = "PicassoII";
    static std::string Spectrum = "Spectrum";
    static std::string Domino = "Domino";
    static std::string RetinaZ3 = "RetinaZ3";
    static std::string DraCoAltais = "DraCoAltais";
    static std::string PiccoSD64 = "PiccoSD64";
    static std::string A2410 = "A2410";
    static std::string CyberVision3D = "CVision3D";
    static std::string Inferno = "Inferno";
    static std::string PicassoIV = "PicassoIV";
    static std::string Pixel64 = "Pixel64";
    static std::string RainbowIII = "RainbowIII";
    static std::string CyberVisonPPC = "CVisionPPC";
    static std::string BlizzardVisionPPC = "BVisionPPC";

    static const std::map<Common::BoardID, std::string &> allBoards {
        { Common::BoardID::CyberVision64, CyberVision64 },
        { Common::BoardID::Piccolo, Piccolo },
        { Common::BoardID::PicassoII, PicassoII },
        { Common::BoardID::Spectrum, Spectrum },
        { Common::BoardID::Domino, Domino },
        { Common::BoardID::RetinaZ3, RetinaZ3 },
        { Common::BoardID::DraCoAltais, DraCoAltais },
        { Common::BoardID::PiccoloSD64, PiccoSD64 },
        { Common::BoardID::A2410, A2410 },
        { Common::BoardID::CyberVision3D, CyberVision3D },
        { Common::BoardID::Inferno, Inferno },
        { Common::BoardID::PicassoIV, PicassoIV },
        { Common::BoardID::Pixel64, Pixel64 },
        { Common::BoardID::RainbowIII, RainbowIII },
        { Common::BoardID::CyberVisionPPC, CyberVisonPPC },
        { Common::BoardID::BlizzardVisionPPC, BlizzardVisionPPC },
    };

    std::vector<Common::BoardID> Library::GetBoards() noexcept
    {
        // return { BoardID::Pixel64, BoardID::BlizzardVisionPPC, BoardID::RainbowIII };

        std::vector<Common::BoardID> boards;
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

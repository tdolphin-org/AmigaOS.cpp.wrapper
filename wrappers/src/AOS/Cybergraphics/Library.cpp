//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include "AOS/TagsScope.hpp"

#include <cybergraphx/cybergraphics.h>
#include <map>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>

extern struct Library *CyberGfxBase;

namespace AOS::Cybergraphics
{
    const std::map<BoardID, Board> id2board {
        { BoardID::CVision64,
          { "CyberVision 64", "Phase 5 Digital Products, Germany", "S3 86C764 Trio64", "2/4 MB VRAM", 1995, "Zorro III" } },
        { BoardID::Piccolo, { "Piccolo", "Ingenieurburo Helfrich, Germany", "Cirrus Logic GD5426", "1/2 MB VRAM", 1993, "Zorro II/III" } },
        { BoardID::PicassoII, { "Picasso II", "Village Tronic, Germany", "Cirrus Logic GD5426/GD5428", "1/2 MB VRAM", 1993, "Zorro II" } },
        { BoardID::Spectrum,
          { "EGS 28/24 Spectrum", "Great Valley Products, USA", "Cirrus Logic GD5426 or GD 5428", "1/2 MB VRAM", 1993, "Zorro II/III" } },
        { BoardID::Domino,
          { "Domino", "X-Pert Computer Services / Village Tronic, Germany", "Tseng Labs ET4000", "1 MB VRAM", 1992, "Zorro II" } },
        { BoardID::RetinaZ3_DraCoAltais, { "Retina BLT Z3", "MacroSystem, Germany", "NCR 77C32BLT", "4 MB VRAM", 1994, "Zorro III" } },
        { BoardID::PiccoSD64,
          { "Picco SD64", "Ingenieurburo Helfrich, Germany", "Cirrus Logic GD5434", "2/4 MB VRAM", 1995, "Zorro II/III" } },
        { BoardID::A2410, { "A2410", "Commodore, USA", "Texas Instruments TMS34010", "2 MB VRAM", 1991, "Zorro II" } },
        { BoardID::CVision3D, { "CyberVision 64/3D", "Phase 5 Digital Products, Germany", "S3 ViRGE", "4 MB VRAM", 1996, "Zorro II/III" } },
        { BoardID::Inferno, { "Inferno", "DKB, USA", "Cirrus Logic GD5446", "4 MB VRAM", 1997, "local PCI expansion bus" } },
        { BoardID::PicassoIV, { "Picasso IV", "Village Tronic, Germany", "Cirrus Logic GD5446", "4 MB VRAM", 1996, "Zorro II/III" } },
        { BoardID::CyberVisonPPC,
          { "CyberVison PPC", "Phase 5 Digital Products, Germany", "3D Labs & Texas Instruments: Permedia 2", "8 MB VRAM", 1998,
            "local PCI expansion bus" } },
        { BoardID::BVisonPPC,
          { "BlizzardVision PPC", "Phase 5 Digital Products, Germany", "3D Labs & Texas Instruments: Permedia 2", "8 MB VRAM", 1998,
            "local PCI expansion bus" } },
    };

    std::vector<Board> Library::GetBoards() noexcept
    {
        std::vector<Board> boards;
        for (const auto item : id2board)
            if (libBestCModeID(item.first) != 0)
                boards.push_back(item.second);
    }

    unsigned long Library::libBestCModeID(const enum BoardID boardID) noexcept
    {
        TagsScope tagsScope({ { CYBRBIDTG_MonitorID, (unsigned long)boardID } });
        return BestCModeIDTagList(tagsScope.tagItems());
    }
}

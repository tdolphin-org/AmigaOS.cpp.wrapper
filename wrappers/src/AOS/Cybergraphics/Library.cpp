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

extern struct Library *CyberGfxBase;

namespace AOS::Cybergraphics
{
    const std::vector<BoardID> allBoards {
        BoardID::CVision64, BoardID::Piccolo, BoardID::PicassoII, BoardID::Spectrum, BoardID::Domino,    BoardID::RetinaZ3_DraCoAltais,
        BoardID::PiccoSD64, BoardID::A2410,   BoardID::CVision3D, BoardID::Inferno,  BoardID::PicassoIV, BoardID::CyberVisonPPC,
        BoardID::BVisonPPC,
    };

    std::vector<BoardID> Library::GetBoards() noexcept
    {
        std::vector<BoardID> boards;
        for (const auto boardID : allBoards)
            if (libBestCModeID(boardID) != (unsigned long)INVALID_ID)
                boards.push_back(boardID);

        return boards;
    }

    unsigned long Library::libBestCModeID(const enum BoardID boardID) noexcept
    {
        TagsScope tagsScope({ { CYBRBIDTG_MonitorID, (unsigned long)boardID } });
        return BestCModeIDTagList(tagsScope.tagItems());
    }
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include <algorithm>
#include <libraries/pcix.h>
#include <proto/pcix.h>

#include "AOS/TagsScope.hpp"

namespace AOS::PCIX
{
    std::vector<Board> Library::GetBoards(const std::vector<BaseClass> &classes) noexcept
    {
        std::vector<Board> result;

        void *board = nullptr;
        TagsScope tagsScope(classes.empty() ? std::vector<TagItemObject> { } : [&]() -> std::vector<TagItemObject> {
            std::vector<TagItemObject> result;
            for_each(classes.begin(), classes.end(),
                     [&result](BaseClass cls) { result.push_back({ PCIXFINDTAG_CLASS, (unsigned long)cls }); });
            return result;
        }());

        while ((board = PCIXFindBoardTagList(board, tagsScope.tagItems())))
        {
            result.push_back({
                board,
                PCIXReadConfigWord(board, PCIXCONFIG_VENDOR),
                PCIXReadConfigWord(board, PCIXCONFIG_DEVICE),
                PCIXReadConfigByte(board, PCIXCONFIG_CLASS),
                PCIXReadConfigWord(board, PCIXCONFIG_SUBSYSTEMVENDORID),
                PCIXReadConfigWord(board, PCIXCONFIG_SUBSYSTEMID),
                PCIXReadConfigByte(board, PCIXCONFIG_SUBCLASS),
                {
                    reinterpret_cast<unsigned char *>(PCIXGetBoardAttr(board, PCIXTAG_ROMADDRESS)),
                    PCIXGetBoardAttr(board, PCIXTAG_ROMSIZE),
                },
            });
        }

        return result;
    }

    std::variant<unsigned long, unsigned char *> Library::libGetBoardAttr(const Board &board, const BoardAttribute attr) noexcept
    {
        switch (attr)
        {
            case BoardAttribute::RomAddress:
                return (unsigned char *)PCIXGetBoardAttr(board.boardObject, (unsigned long)attr);
            case BoardAttribute::RomSize:
                return PCIXGetBoardAttr(board.boardObject, (unsigned long)attr);
            default:
                return PCIXGetBoardAttr(board.boardObject, (unsigned long)attr);
        }
    }
}

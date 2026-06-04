//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
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
            });
        }

        return result;
    }

    std::optional<BoardAttributes> Library::GetBoardAttributes(const Board &board) noexcept
    {
        if (board.boardObject == nullptr)
            return std::nullopt;

        return BoardAttributes {
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BUS),
            std::string(reinterpret_cast<char *>(PCIXGetBoardAttr(board.boardObject, PCIXTAG_BRIDGENAME))),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_DEV),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_FUNCTION),
            reinterpret_cast<unsigned char *>(PCIXGetBoardAttr(board.boardObject, PCIXTAG_ROMADDRESS)),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_ROMSIZE),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASEADDRESS0),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASEADDRESS1),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASEADDRESS2),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASEADDRESS3),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASEADDRESS4),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASEADDRESS5),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASESIZE0),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASESIZE1),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASESIZE2),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASESIZE3),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASESIZE4),
            PCIXGetBoardAttr(board.boardObject, PCIXTAG_BASESIZE5),
        };
    }

    std::variant<unsigned long, unsigned char *, std::string> Library::libGetBoardAttr(const Board &board,
                                                                                       const BoardAttribute attr) noexcept
    {
        switch (attr)
        {
            case BoardAttribute::BridgeName:
                return std::string(reinterpret_cast<char *>(PCIXGetBoardAttr(board.boardObject, (unsigned long)attr)));
            case BoardAttribute::RomAddress:
                return (unsigned char *)PCIXGetBoardAttr(board.boardObject, (unsigned long)attr);
            case BoardAttribute::Bus:
            case BoardAttribute::Dev:
            case BoardAttribute::Function:
            case BoardAttribute::RomSize:
            case BoardAttribute::BaseAddress0:
            case BoardAttribute::BaseAddress1:
            case BoardAttribute::BaseAddress2:
            case BoardAttribute::BaseAddress3:
            case BoardAttribute::BaseAddress4:
            case BoardAttribute::BaseAddress5:
            case BoardAttribute::BaseSize0:
            case BoardAttribute::BaseSize1:
            case BoardAttribute::BaseSize2:
            case BoardAttribute::BaseSize3:
            case BoardAttribute::BaseSize4:
            case BoardAttribute::BaseSize5:
            default:
                return PCIXGetBoardAttr(board.boardObject, (unsigned long)attr);
        }
    }
}

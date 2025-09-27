//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include <proto/pcix.h>
#include <libraries/pcix.h>

#include "AOS/TagsScope.hpp"

namespace AOS::PCIX
{
    std::vector<Board> Library::GetBoards() noexcept
    {
        std::vector<Board> result;
        
        void *board = nullptr;
        TagsScope tagsScope({});
        
        while (board = PCIXFindBoardTagList(board, tagsScope.tagItems()))
        {
            result.push_back({
                PCIXReadConfigWord(board, PCIXCONFIG_VENDOR),
                PCIXReadConfigWord(board, PCIXCONFIG_DEVICE),
                PCIXReadConfigByte(board, PCIXCONFIG_CLASS),        
            });
        }
		
        return result;
    }
}

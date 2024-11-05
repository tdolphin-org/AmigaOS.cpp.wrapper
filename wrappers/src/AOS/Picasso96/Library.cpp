//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include <proto/Picasso96.h>

// some missing defines

// ************************************************************************
// * Tags for P96GetRTGDataTagList

#define P96RD_Dummy (TAG_USER + 0x40000 + 96)
#define P96RD_NumberOfBoards (P96RD_Dummy + 1)

// ************************************************************************
// * Tags for P96GetBoardDataTagList

#define P96BD_Dummy (TAG_USER + 0x50000 + 96)
#define P96BD_BoardName (P96BD_Dummy + 1)
#define P96BD_ChipName (P96BD_Dummy + 2)
#define P96BD_TotalMemory (P96BD_Dummy + 4)
#define P96BD_FreeMemory (P96BD_Dummy + 5)
#define P96BD_LargestFreeMemory (P96BD_Dummy + 6)
#define P96BD_MonitorSwitch (P96BD_Dummy + 7)
#define P96BD_RGBFormats (P96BD_Dummy + 8)
#define P96BD_MemoryClock (P96BD_Dummy + 9)

namespace AOS::Picasso96
{
    std::vector<Board> Library::GetBoards() noexcept
    {
        std::vector<Board> boards;

        ULONG boardsNumber;
        if (p96GetRTGDataTags(P96RD_NumberOfBoards, (unsigned long)&boardsNumber, TAG_END) == 1)
        {
            for (auto i = 0; i < boardsNumber; i++)
            {
                char *boardName;
                ULONG memorySize, memoryClock;

                p96GetBoardDataTags(i, P96BD_BoardName, (unsigned long)&boardName, P96BD_TotalMemory, (unsigned long)&memorySize,
                                    P96BD_MemoryClock, (unsigned long)&memoryClock, TAG_END);

                boards.push_back({ boardName,
                                   [=]() {
                                       if (memorySize % (1024 * 1024) == 0)
                                           return std::to_string(memorySize / (1024 * 1024)) + " MiB VRAM";
                                       else if (memorySize % 1024 == 0)
                                           return std::to_string(memorySize / 1024) + " KiB VRAM";
                                       else
                                           return std::to_string(memorySize) + " Bytes VRAM";
                                   }(),
                                   [=]() {
                                       int clock = (memoryClock + 50000) / 100000;
                                       return std::to_string(clock / 10) + "." + std::to_string(clock % 10) + " MHz";
                                   }() });
            }
        }

        return boards;
    }
}
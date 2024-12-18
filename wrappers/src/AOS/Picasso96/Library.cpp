//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include <libraries/Picasso96.h>
#include <proto/Picasso96.h>

namespace AOS::Picasso96
{
    std::vector<Board> Library::GetBoards() noexcept
    {
        std::vector<Board> boards;

        auto videoMemoryValue = [=](unsigned long value, bool round = false) {
            if ((round && value > 1024 * 1024) || value % (1024 * 1024) == 0)
                return std::to_string(value / (1024 * 1024)) + " MB VRAM";
            else
                return std::to_string(value / 1024) + " KB VRAM";
        };

        ULONG boardsNumber;
        if (p96GetRTGDataTags(P96RD_NumberOfBoards, (unsigned long)&boardsNumber, TAG_END) == 1)
        {
            for (auto i = 0UL; i < boardsNumber; i++)
            {
                char *boardName, *chipName;
                ULONG memorySize, freeMemory, memoryClock, rgbFormats;

                p96GetBoardDataTags(i, P96BD_BoardName, (unsigned long)&boardName, P96BD_ChipName, (unsigned long)&chipName,
                                    P96BD_TotalMemory, (unsigned long)&memorySize, P96BD_FreeMemory, (unsigned long)&freeMemory,
                                    P96BD_MemoryClock, (unsigned long)&memoryClock, P96BD_RGBFormats, (unsigned long)&rgbFormats, TAG_END);

                boards.push_back({ boardName, chipName, videoMemoryValue(memorySize), videoMemoryValue(memorySize - freeMemory),
                                   (long) { (long)((100.0f * (float)freeMemory) / (float)memorySize) },
                                   [=]() {
                                       int clock = (memoryClock + 50000) / 100000;
                                       return std::to_string(clock / 10) + "." + std::to_string(clock % 10) + " MHz";
                                   }(),
                                   [=]() {
                                       std::vector<std::string> formats;
                                       if (rgbFormats & RGBFF_NONE)
                                           formats.push_back("PLANAR");
                                       if (rgbFormats & RGBFF_CLUT)
                                           formats.push_back("CHUNKY");
                                       if (rgbFormats & RGBFF_R5G5B5)
                                           formats.push_back("R5G5B5");
                                       if (rgbFormats & RGBFF_R5G5B5PC)
                                           formats.push_back("R5G5B5PC");
                                       if (rgbFormats & RGBFF_B5G5R5PC)
                                           formats.push_back("B5G5R5PC");
                                       if (rgbFormats & RGBFF_R5G6B5)
                                           formats.push_back("R5G6B5");
                                       if (rgbFormats & RGBFF_R5G6B5PC)
                                           formats.push_back("R5G6B5PC");
                                       if (rgbFormats & RGBFF_B5G6R5PC)
                                           formats.push_back("B5G6R5PC");
                                       if (rgbFormats & RGBFF_R8G8B8)
                                           formats.push_back("R8G8B8");
                                       if (rgbFormats & RGBFF_B8G8R8)
                                           formats.push_back("B8G8R8");
                                       if (rgbFormats & RGBFF_A8R8G8B8)
                                           formats.push_back("A8R8G8B8");
                                       if (rgbFormats & RGBFF_A8B8G8R8)
                                           formats.push_back("A8B8G8R8");
                                       if (rgbFormats & RGBFF_R8G8B8A8)
                                           formats.push_back("R8G8B8A8");
                                       if (rgbFormats & RGBFF_B8G8R8A8)
                                           formats.push_back("B8G8R8A8");
                                       if (rgbFormats & RGBFF_Y4U2V2)
                                           formats.push_back("Y4U2V2");
                                       if (rgbFormats & RGBFF_Y4U1V1)
                                           formats.push_back("Y4U1V1");
                                       return formats;
                                   }() });
            }
        }

        return boards;
    }
}
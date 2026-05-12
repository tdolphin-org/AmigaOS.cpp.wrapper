//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/iffparse.h>

namespace AOS::IFFParse
{
    enum class IFFCommand : int32_t
    {
        Init = IFFCMD_INIT,
        Cleanup = IFFCMD_CLEANUP,
        Read = IFFCMD_READ,
        Write = IFFCMD_WRITE,
        Seek = IFFCMD_SEEK,
        Entry = IFFCMD_ENTRY,
        Exit = IFFCMD_EXIT,
        PurgeLCI = IFFCMD_PURGELCI,
    };
}

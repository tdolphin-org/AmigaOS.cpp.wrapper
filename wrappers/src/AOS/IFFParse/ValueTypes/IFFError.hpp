//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/iffparse.h>

namespace AOS::IFFParse
{
    enum class IFFError : int32_t
    {
        Ok = 0,
        EndOfFile = IFFERR_EOF,
        EndOfContext = IFFERR_EOC,
        NoScope = IFFERR_NOSCOPE,
        NoMemory = IFFERR_NOMEM,
        ReadError = IFFERR_READ,
        WriteError = IFFERR_WRITE,
        SeekError = IFFERR_SEEK,
        Mangled = IFFERR_MANGLED,
        SyntaxError = IFFERR_SYNTAX,
        NotIFF = IFFERR_NOTIFF,
        NoHook = IFFERR_NOHOOK,
        ReturnToClient = IFF_RETURN2CLIENT,
    };
}

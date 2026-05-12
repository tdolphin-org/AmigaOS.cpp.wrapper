//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/iffparse.h>

namespace AOS::IFFParse
{
    enum class IFF : uint32_t
    {
        ReadError = IFFF_READ,
        WriteError = IFFF_WRITE,
        RwBitsError = IFFF_RWBITS,
        FSeekError = IFFF_FSEEK,
        RSeekError = IFFF_RSEEK,
        Reserved = IFFF_RESERVED,
    };
}

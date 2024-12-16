//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/memory.h>

namespace AOS::Exec
{
    enum class MEMF_Type : unsigned long
    {
        ANY = MEMF_ANY,
        PUBLIC = MEMF_PUBLIC,
        CHIP = MEMF_CHIP,
        FAST = MEMF_FAST,
        LOCAL = MEMF_LOCAL,
        _24BITDMA = MEMF_24BITDMA,
    };

    enum class MEMF_Alloc : unsigned long
    {
        CLEAR = MEMF_CLEAR,
        REVERSE = MEMF_REVERSE,
        NO_EXPUNGE = MEMF_NO_EXPUNGE,
    };

    enum class MEMF_Avail : unsigned long
    {
        LARGEST = MEMF_LARGEST,
        TOTAL = MEMF_TOTAL,
    };
}
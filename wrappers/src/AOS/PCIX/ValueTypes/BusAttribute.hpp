//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/pcix.h>

namespace AOS::PCIX
{
    enum class BusAttribute : uint32_t
    {
        Slots = PCIXTAG_SLOTS,
        IOBase = PCIXTAG_IOBASE
    };
}

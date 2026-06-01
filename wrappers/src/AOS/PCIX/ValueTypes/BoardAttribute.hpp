//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/pcix.h>

namespace AOS::PCIX
{
    enum class BoardAttribute : unsigned long
    {
        Bus = PCIXTAG_BUS,
        BridgeName = PCIXTAG_BRIDGENAME,
        Dev = PCIXTAG_DEV,
        Function = PCIXTAG_FUNCTION,
        RomAddress = PCIXTAG_ROMADDRESS,
        RomSize = PCIXTAG_ROMSIZE,
        BaseAddress0 = PCIXTAG_BASEADDRESS0,
        BaseAddress1 = PCIXTAG_BASEADDRESS1,
        BaseAddress2 = PCIXTAG_BASEADDRESS2,
        BaseAddress3 = PCIXTAG_BASEADDRESS3,
        BaseAddress4 = PCIXTAG_BASEADDRESS4,
        BaseAddress5 = PCIXTAG_BASEADDRESS5,
        BaseSize0 = PCIXTAG_BASESIZE0,
        BaseSize1 = PCIXTAG_BASESIZE1,
        BaseSize2 = PCIXTAG_BASESIZE2,
        BaseSize3 = PCIXTAG_BASESIZE3,
        BaseSize4 = PCIXTAG_BASESIZE4,
        BaseSize5 = PCIXTAG_BASESIZE5
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/iffparse.h>

namespace AOS::IFFParse
{
    enum class IFFParse : int32_t
    {
        Scan = IFFPARSE_SCAN,
        Step = IFFPARSE_STEP,
        RawStep = IFFPARSE_RAWSTEP,
    };
}

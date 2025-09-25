//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <libraries/identify.h>

namespace AOS::Identify
{
    enum class IDGOS
    {
        AMIGAOS = IDGOS_AMIGAOS,
        EGS = IDGOS_EGS,
        RETINA = IDGOS_RETINA,
        GRAFFITI = IDGOS_GRAFFITI,
        TIGA = IDGOS_TIGA,
        PROBENCH = IDGOS_PROBENCH,
        PICASSO = IDGOS_PICASSO,
        CGX = IDGOS_CGX,
        CGX3 = IDGOS_CGX3,
        PICASSO96 = IDGOS_PICASSO96,
        CGX4 = IDGOS_CGX4,
    };
}

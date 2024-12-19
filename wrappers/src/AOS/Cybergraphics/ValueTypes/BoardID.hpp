//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

namespace AOS::Cybergraphics
{
    enum class BoardID : unsigned long
    {
        CVision64 = 1,
        Piccolo = 2,
        PicassoII = 3,
        Spectrum = 4,
        Domino = 5,
        RetinaZ3_DraCoAltais = 6,
        PiccoSD64 = 7,
        A2410 = 8,
        CVision3D = 13,
        Inferno = 14,
        PicassoIV = 15,
        CyberVisonPPC = 18, // unverified
        BVisonPPC = 19, // unverified
    };
}

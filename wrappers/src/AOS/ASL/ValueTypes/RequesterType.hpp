//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/asl.h>

namespace AOS::ASL
{
    enum class RequesterType : uint32_t
    {
        File = ASL_FileRequest,
        Font = ASL_FontRequest,
        ScreenMode = ASL_ScreenModeRequest
    };
}

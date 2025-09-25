//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <dos/var.h>

namespace AOS::Dos
{
    enum class GVF
    {
        Var = LV_VAR,
        Alias = LV_ALIAS,
        Ignore = LVF_IGNORE,
        System = GVB_GLOBAL_ONLY,
        Local = GVB_LOCAL_ONLY,
        Binary = GVB_BINARY_VAR,
        NoNullTerm = GVB_DONT_NULL_TERM,
        Save = GVB_SAVE_VAR,
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <string>
#include <set>

namespace AOS::Graphics
{
    struct Library
    {
        static std::set<std::string> GetMonitors();
    };
}

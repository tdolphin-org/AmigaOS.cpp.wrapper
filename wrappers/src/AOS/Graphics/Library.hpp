//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
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

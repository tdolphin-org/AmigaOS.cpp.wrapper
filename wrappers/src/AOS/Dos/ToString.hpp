//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <dos/dos.h>
#include <string>

namespace AOS::Dos
{
    class ToString
    {
      public:
        static std::string FromLock(const BPTR lock);
    };
}

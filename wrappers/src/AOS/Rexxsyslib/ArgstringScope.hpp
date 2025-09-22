//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <string>

namespace AOS::Rexxsyslib
{
    class ArgstringScope
    {
        char *mpArgstring { nullptr };

      public:
        ArgstringScope(const std::string &string, bool exceptionOnError = true);
        ~ArgstringScope();

        char *argstring() const
        {
            return mpArgstring;
        }
    };
}
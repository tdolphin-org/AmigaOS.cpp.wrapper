//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "ArgstringScope.hpp"

#include <proto/rexxsyslib.h>
#include <stdexcept>

static constexpr size_t ArgstringLimit = 65535;

namespace AOS::Rexxsyslib
{
    ArgstringScope::ArgstringScope(const std::string &string, bool exceptionOnError)
    {
        if (string.length() > ArgstringLimit)
        {
            if (!exceptionOnError)
                return;

            auto error = std::string { __PRETTY_FUNCTION__ } + " string length is greater than " + std::to_string(ArgstringLimit) + "!";
            throw std::runtime_error(error);
        }

        mpArgstring = (char *)CreateArgstring(string.c_str(), string.length());
        if (!mpArgstring && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreateArgstring(...) failed!";
            throw std::runtime_error(error);
        }
    }

    ArgstringScope::~ArgstringScope()
    {
        if (mpArgstring)
            DeleteArgstring((char *)mpArgstring);
    }
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
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

#ifdef __AROS__
        mpArgstring = (char *)CreateArgstring((const UBYTE *)string.c_str(), string.length());
#else
        mpArgstring = (char *)CreateArgstring(string.c_str(), string.length());
#endif
        if (!mpArgstring && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreateArgstring(...) failed!";
            throw std::runtime_error(error);
        }
    }

    ArgstringScope::~ArgstringScope()
    {
        if (mpArgstring)
        {
#ifdef __MORPHOS__
            DeleteArgstring((char *)mpArgstring);
#else
            DeleteArgstring((UBYTE *)mpArgstring);
#endif
        }
    }
}

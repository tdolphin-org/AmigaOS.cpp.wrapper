//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "ToString.hpp"

#include <proto/dos.h>

namespace AOS::Dos
{
    std::string ToString::FromLock(const BPTR lock)
    {
        const unsigned int len = 256;
        char buffer[len];

        if (!NameFromLock(lock, buffer, len))
            return {};
        buffer[len - 1] = '\0';

        return buffer;
    }
}

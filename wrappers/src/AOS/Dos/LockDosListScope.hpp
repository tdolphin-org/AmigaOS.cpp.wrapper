//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "DosObjectScope.hpp"

#include <dos/dosextens.h>

namespace AOS::Dos
{
    class LockDosListScope
    {
        struct DosList *mpDosList;
        unsigned long mFlags;

      public:
        LockDosListScope(const unsigned long flags);
        ~LockDosListScope();

        struct DosList *lockDosList() const
        {
            return mpDosList;
        }
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "LockDosListScope.hpp"

#include <proto/dos.h>

namespace AOS::Dos
{
    LockDosListScope::LockDosListScope(const unsigned long flags)
      : mFlags(flags)
    {
        mpDosList = LockDosList(mFlags);
    }

    LockDosListScope::~LockDosListScope()
    {
        if (mpDosList)
            UnLockDosList(mFlags);
    }
}

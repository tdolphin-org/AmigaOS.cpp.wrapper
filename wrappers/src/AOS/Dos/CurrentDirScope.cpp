//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "CurrentDirScope.hpp"

#include <proto/dos.h>

namespace AOS::Dos
{
    CurrentDirScope::CurrentDirScope(BPTR newLock)
    {
        mOldLock = CurrentDir(newLock);
    }

    CurrentDirScope::~CurrentDirScope()
    {
        CurrentDir(mOldLock);
    }
}

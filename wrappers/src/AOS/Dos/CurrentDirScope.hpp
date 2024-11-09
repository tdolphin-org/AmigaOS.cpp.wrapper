//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <dos/dos.h>

namespace AOS::Dos
{
    class CurrentDirScope
    {
        BPTR mOldLock;

      public:
        /// @param directory name
        CurrentDirScope(BPTR newLock);
        ~CurrentDirScope();
    };
}

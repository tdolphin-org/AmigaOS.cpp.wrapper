//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <string>

#include <dos/dos.h>

namespace AOS::Dos
{
    class ProgramDirScope
    {
        std::string mPath;
        BPTR mLock;
        BPTR mProgramDirLock;

      public:
        ProgramDirScope(const std::string &path, bool exceptionOnError = true);
        ~ProgramDirScope();
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <dos/dos.h>
#include <string>

namespace AOS::Dos
{
    class CurrentDirNameScope
    {
        std::string mPath;
        std::string mOldCurrentDirName;

      public:
        CurrentDirNameScope(const std::string &path, bool exceptionOnError = true);
        ~CurrentDirNameScope();
    };
}

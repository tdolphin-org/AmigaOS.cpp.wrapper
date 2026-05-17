//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "CurrentDirNameScope.hpp"

#include "Library.hpp"

#include <cstdio>
#include <proto/dos.h>
#include <stdexcept>

namespace AOS::Dos
{
    CurrentDirNameScope::CurrentDirNameScope(const std::string &path, bool exceptionOnError)
      : mPath(path)
    {
#ifdef TRACE_AMIGAOS
        std::fprintf(stdout, "%s %s\n", __PRETTY_FUNCTION__, path.c_str());
#endif

        mOldCurrentDirName = Library::libGetCurrentDirName();

        if (!SetCurrentDirName(mPath.c_str()))
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " SetCurrentDirName(" + path + ") failed!";
            if (exceptionOnError)
                throw std::runtime_error(error);
            else
                std::fprintf(stderr, "%s\n", error.c_str());
            return;
        }

#ifdef TRACE_AMIGAOS
        std::fprintf(stdout, "oldDirName: %s\n", mOldCurrentDirName.c_str());
        std::fprintf(stdout, "currentDirName: %s\n", Library::libGetCurrentDirName().c_str());
#endif
    }

    CurrentDirNameScope::~CurrentDirNameScope()
    {
        if (!mOldCurrentDirName.empty())
            SetCurrentDirName(mOldCurrentDirName.c_str());
    }
}

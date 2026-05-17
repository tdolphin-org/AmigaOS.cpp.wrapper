//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "ProgramDirScope.hpp"

#include <cstdio>
#include <proto/dos.h>
#include <stdexcept>

#ifdef TRACE_AMIGAOS
#include "Library.hpp"
#include "ToString.hpp"
#endif

namespace AOS::Dos
{
    ProgramDirScope::ProgramDirScope(const std::string &path, bool exceptionOnError)
      : mPath(path)
      , mLock(0)
      , mProgramDirLock(0)
    {
#ifdef TRACE_AMIGAOS
        std::fprintf(stdout, "%s %s\n", __PRETTY_FUNCTION__, path.c_str());
#endif

        mLock = Lock(mPath.c_str(), ACCESS_READ);
        if (mLock == 0)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " Lock(" + path + ", ACCESS_READ) failed!";
            if (exceptionOnError)
                throw std::runtime_error(error);
            else
                std::fprintf(stderr, "%s\n", error.c_str());
            return;
        }

        mProgramDirLock = SetProgramDir(mLock);

#ifdef TRACE_AMIGAOS
        std::fprintf(stdout, "currentDirName: %s\n", Library::libGetCurrentDirName().c_str());
        std::fprintf(stdout, "lock: %s\n", ToString::FromLock(mLock).c_str());
        std::fprintf(stdout, "programLock: %s\n", ToString::FromLock(mProgramDirLock).c_str());
#endif
    }

    ProgramDirScope::~ProgramDirScope()
    {
        if (mProgramDirLock != 0)
            SetProgramDir(mProgramDirLock);
        if (mLock != 0)
            UnLock(mLock);
    }
}

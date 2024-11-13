//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "ProgramDirScope.hpp"

#include <iostream>
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
        std::cout << __PRETTY_FUNCTION__ << " " << path << std::endl;
#endif

        mLock = Lock(mPath.c_str(), ACCESS_READ);
        if (mLock == 0)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " Lock(" + path + ", ACCESS_READ) failed!";
            if (exceptionOnError)
                throw std::runtime_error(error);
            else
                std::cerr << error << std::endl;
            return;
        }

        mProgramDirLock = SetProgramDir(mLock);

#ifdef TRACE_AMIGAOS
        std::cout << "currentDirName: " << Library::libGetCurrentDirName() << std::endl;
        std::cout << "lock: " << ToString::FromLock(mLock) << std::endl;
        std::cout << "programLock: " << ToString::FromLock(mProgramDirLock) << std::endl;
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

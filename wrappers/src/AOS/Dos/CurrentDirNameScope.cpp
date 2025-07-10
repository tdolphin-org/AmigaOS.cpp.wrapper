//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "CurrentDirNameScope.hpp"

#include "Library.hpp"

#include "amiga_std_light/iostream.hpp"
#include <proto/dos.h>
#include <stdexcept>

namespace AOS::Dos
{
    CurrentDirNameScope::CurrentDirNameScope(const std::string &path, bool exceptionOnError)
      : mPath(path)
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << " " << path << std::endl;
#endif

        mOldCurrentDirName = Library::libGetCurrentDirName();

        if (!SetCurrentDirName(mPath.c_str()))
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " SetCurrentDirName(" + path + ") failed!";
            if (exceptionOnError)
                throw std::runtime_error(error);
            else
                std::cerr << error << std::endl;
            return;
        }

#ifdef TRACE_AMIGAOS
        std::cout << "oldDirName: " << mOldCurrentDirName << std::endl;
        std::cout << "currentDirName: " << Library::libGetCurrentDirName() << std::endl;
#endif
    }

    CurrentDirNameScope::~CurrentDirNameScope()
    {
        if (!mOldCurrentDirName.empty())
            SetCurrentDirName(mOldCurrentDirName.c_str());
    }
}

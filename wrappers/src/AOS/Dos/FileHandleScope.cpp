//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "FileHandleScope.hpp"

#include <proto/dos.h>
#include <stdexcept>

#undef Close

namespace AOS::Dos
{
    FileHandleScope::FileHandleScope(const std::string &name, const enum OpenMode openMode, bool exceptionOnError)
    {
        mFileHandle = Open(name.c_str(), (long)openMode);
        if (exceptionOnError && !mFileHandle)
        {
            std::string error
                = std::string { __PRETTY_FUNCTION__ } + " Open(" + name + "," + std::to_string((unsigned long)openMode) + ") failed!";
            throw std::runtime_error(error);
        }
    }

    FileHandleScope::~FileHandleScope()
    {
        if (mFileHandle)
            ::Close(mFileHandle);
    }

    void FileHandleScope::Invalidate()
    {
        mFileHandle = (BPTR) nullptr;
    }

    void FileHandleScope::Close()
    {
        if (mFileHandle)
        {
            ::Close(mFileHandle);
            Invalidate();
        }
    }
}
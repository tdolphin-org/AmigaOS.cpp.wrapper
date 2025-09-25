//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <dos/dos.h>
#include <string>

#undef Close

namespace AOS::Dos
{
    enum class OpenMode
    {
        /// @brief existing file read/write positioned at beginning of file
        OldFile = MODE_OLDFILE,
        /// @brief freshly created file (delete old file) read/write, exclusive lock
        NewFile = MODE_NEWFILE,
        /// @brief old file w/shared lock, creates file if doesn't exist
        ReadWrite = MODE_READWRITE
    };

    class FileHandleScope
    {
        BPTR mFileHandle;

      public:
        FileHandleScope(const std::string &name, const enum OpenMode openMode, bool exceptionOnError = true);
        ~FileHandleScope();

        /// @brief invalidate handler, no close on destructor
        void Invalidate();
        /// @brief close handler and invalidate, no close on destructor
        void Close();

        BPTR fileHandle()
        {
            return mFileHandle;
        }
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "DosObjectScope.hpp"

#include <string>

namespace AOS::Dos
{
    class LockScope
    {
        BPTR mpLock;
        bool mExamineResult;
        DosObjectScope mFileInfoBlockScope;
        bool mIsFile;
        bool mIsDrawer;
        bool mIsEmpty;
        std::string mName;

      public:
        /// @param name file or directory name
        LockScope(const std::string &name, bool exceptionOnError = true);
        /// @param pLock lock to file or directory
        LockScope(const BPTR pLock, bool exceptionOnError = true);
        ~LockScope();

        /// @brief invalidate handler, no UnLock on destructor
        void Invalidate();

        BPTR lock() const
        {
            return mpLock;
        }

        std::string name()
        {
            return mName;
        }

        bool isValid() const
        {
            return mpLock != 0 && mExamineResult;
        }

        /// @brief remember to check also isValid() if exceptionOnError = false
        bool isFile() const
        {
            return mIsFile;
        }

        /// @brief remember to check also isValid() if exceptionOnError = false
        bool isDirectory() const
        {
            return mIsDrawer;
        }

        /// @brief same as isDirectory; remember to check also isValid() if exceptionOnError = false
        bool isDrawer() const
        {
            return mIsDrawer;
        }

        /// @brief for file return true if sized = 0, for drawer return true if folder is empty
        /// remember to check also isValid() if exceptionOnError = false
        bool isEmpty()
        {
            return mIsEmpty;
        }
    };
}

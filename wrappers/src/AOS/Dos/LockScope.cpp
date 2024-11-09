//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "LockScope.hpp"

#include <proto/dos.h>
#include <stdexcept>

namespace AOS::Dos
{
    LockScope::LockScope(const std::string &name, bool exceptionOnError)
      : mFileInfoBlockScope(DOS_FIB)
      , mIsEmpty(false)
      , mIsFile(false)
      , mIsDrawer(false)
      , mName(name)
    {
        mpLock = Lock(mName.c_str(), SHARED_LOCK);
        if (mpLock == 0)
        {
            if (exceptionOnError)
            {
                auto error = std::string { __PRETTY_FUNCTION__ } + " Lock(\"" + name + "\", SHARED_LOCK) failed!";
                throw std::runtime_error(error);
            }

            return;
        }

        mExamineResult = Examine(mpLock, mFileInfoBlockScope.fileInfoBlock());
        if (!mExamineResult)
        {
            if (exceptionOnError)
            {
                auto error = std::string { __PRETTY_FUNCTION__ } + " Examine(..) failed!";
                throw std::runtime_error(error);
            }

            return;
        }

        mIsFile = mFileInfoBlockScope.fileInfoBlock()->fib_DirEntryType < 0;
        mIsDrawer = mFileInfoBlockScope.fileInfoBlock()->fib_DirEntryType > 0;

        if (isFile())
            mIsEmpty = mFileInfoBlockScope.fileInfoBlock()->fib_Size == 0;
        else if (isDrawer())
            mIsEmpty = !ExNext(mpLock, mFileInfoBlockScope.fileInfoBlock());
    }

    LockScope::LockScope(const BPTR pLock, bool exceptionOnError)
      : mFileInfoBlockScope(DOS_FIB)
      , mIsEmpty(false)
      , mIsFile(false)
      , mIsDrawer(false)
      , mpLock(pLock)
    {
        if (mpLock == 0)
        {
            if (exceptionOnError)
            {
                auto error = std::string { __PRETTY_FUNCTION__ } + " pointer to lock is null!";
                throw std::runtime_error(error);
            }

            return;
        }

        mExamineResult = Examine(mpLock, mFileInfoBlockScope.fileInfoBlock());
        if (!mExamineResult)
        {
            if (exceptionOnError)
            {
                auto error = std::string { __PRETTY_FUNCTION__ } + " Examine(..) failed!";
                throw std::runtime_error(error);
            }

            return;
        }

        mIsFile = mFileInfoBlockScope.fileInfoBlock()->fib_DirEntryType < 0;
        mIsDrawer = mFileInfoBlockScope.fileInfoBlock()->fib_DirEntryType > 0;

        if (isFile())
            mIsEmpty = mFileInfoBlockScope.fileInfoBlock()->fib_Size == 0;
        else if (isDrawer())
            mIsEmpty = !ExNext(mpLock, mFileInfoBlockScope.fileInfoBlock());
    }

    LockScope::~LockScope()
    {
        if (mpLock)
            UnLock(mpLock);
    }

    void LockScope::Invalidate()
    {
        mpLock = (BPTR) nullptr;
    }
}
//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "FileRequesterScope.hpp"

#include <proto/asl.h>

namespace AOS::ASL
{
    FileRequesterScope::FileRequesterScope()
    {
        mFileRequester = AllocFileRequest();
        if (mFileRequester == nullptr)
            throw std::bad_alloc();
    }

    FileRequesterScope::~FileRequesterScope()
    {
        FreeFileRequest(mFileRequester);
    }

    bool FileRequesterScope::FileRequest()
    {
        return ::RequestFile(mFileRequester);
    }

    std::optional<std::string> FileRequesterScope::file() const
    {
        if (mFileRequester->fr_File)
            return std::string(mFileRequester->fr_File);
        return std::nullopt;
    }

    std::optional<std::string> FileRequesterScope::drawer() const
    {
        if (mFileRequester->fr_Drawer)
            return std::string(mFileRequester->fr_Drawer);
        return std::nullopt;
    }
}

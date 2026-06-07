//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/asl.h>

#include <optional>
#include <string>

namespace AOS::ASL
{
    class FileRequesterScope
    {
        struct FileRequester *mFileRequester { nullptr };

      public:
        FileRequesterScope();
        ~FileRequesterScope();

        bool FileRequest();

        struct FileRequester *fileRequester() const
        {
            return mFileRequester;
        }

        std::optional<std::string> file() const;

        std::optional<std::string> drawer() const;
    };
}

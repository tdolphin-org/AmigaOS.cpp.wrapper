//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <string>

struct DiskObject;

namespace AOS::Icon
{
    class DiskObjectScope
    {
        struct DiskObject *mpDiskObject;

      public:
        DiskObjectScope(const std::string &diskObjectName, bool exceptionOnError = true);
        ~DiskObjectScope();

        std::string FindToolTypeAsString(const std::string &toolTypeName);
        bool FindToolTypeAsBool(const std::string &toolTypeName);

        // may be nullptr if exceptionOnError = false and GetDiskObject() failed
        struct DiskObject *diskObject() const
        {
            return mpDiskObject;
        }
    };
}

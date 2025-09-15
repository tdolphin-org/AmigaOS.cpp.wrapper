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
        DiskObjectScope(const std::string &diskObjectName);
        ~DiskObjectScope();

        std::string FindToolTypeAsString(const std::string &toolTypeName);
        bool FindToolTypeAsBool(const std::string &toolTypeName);

        struct DiskObject *diskObject() const
        {
            return mpDiskObject;
        }
    };
}

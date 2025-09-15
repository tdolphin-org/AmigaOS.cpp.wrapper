//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "DiskObjectScope.hpp"

#include <proto/icon.h>
#include <stdexcept>
#include <workbench/workbench.h>

namespace AOS::Icon
{
    DiskObjectScope::DiskObjectScope(const std::string &diskObjectName, bool exceptionOnError)
    {
        mpDiskObject = (struct DiskObject *)GetDiskObject((STRPTR)diskObjectName.c_str());
        if (!mpDiskObject && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " GetDiskObject(" + diskObjectName + ") failed!";
            throw std::runtime_error(error);
        }
    }

    DiskObjectScope::~DiskObjectScope()
    {
        if (mpDiskObject)
            FreeDiskObject(mpDiskObject);
    }

    std::string DiskObjectScope::FindToolTypeAsString(const std::string &toolTypeName)
    {
#ifdef __MORPHOS__
        auto value = FindToolType((char *const *)mpDiskObject->do_ToolTypes, (STRPTR)toolTypeName.c_str());
#else
        auto value = FindToolType((CONST_STRPTR *)mpDiskObject->do_ToolTypes, (STRPTR)toolTypeName.c_str());
#endif
        if (value)
            return std::string { (char *)value };

        return {};
    }

    bool DiskObjectScope::FindToolTypeAsBool(const std::string &toolTypeName)
    {
#ifdef __MORPHOS__
        auto value = FindToolType((char *const *)mpDiskObject->do_ToolTypes, (STRPTR)toolTypeName.c_str());
#else
        auto value = FindToolType((CONST_STRPTR *)mpDiskObject->do_ToolTypes, (STRPTR)toolTypeName.c_str());
#endif
        return (value != nullptr);
    }
};

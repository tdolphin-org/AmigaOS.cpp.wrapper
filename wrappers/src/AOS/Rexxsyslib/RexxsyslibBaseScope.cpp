//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "RexxsyslibBaseScope.hpp"

#include <proto/rexxsyslib.h>
#include <proto/exec.h>
#include <stdexcept>

struct Library *RexxSysBase = nullptr;

RexxsyslibBaseScope::RexxsyslibBaseScope(const bool optional)
{
    if (RexxSysBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + "Rexxsyslib already open!";
        throw std::runtime_error(error);
    }

    if (!(RexxSysBase = OpenLibrary(RXSNAME, 0)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + RXSNAME;
        throw std::runtime_error(error);
    }
}

RexxsyslibBaseScope::~RexxsyslibBaseScope()
{
    if (RexxSysBase != nullptr)
    {
        CloseLibrary((struct Library *)RexxSysBase);
        RexxSysBase = nullptr;
    }
}

bool RexxsyslibBaseScope::isOpen() const
{
    return RexxSysBase != nullptr;
}

struct Library *RexxsyslibBaseScope::library() const
{
    return RexxSysBase;
}

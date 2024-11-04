//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "IdentifyBaseScope.hpp"

#include <clib/identify_protos.h>
#include <libraries/identify.h>
#include <proto/exec.h>
#include <stdexcept>

struct Library *IdentifyBase = nullptr;

IdentifyBaseScope::IdentifyBaseScope(const bool optional)
{
    if (IdentifyBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + " identify.library already open!";
        throw std::runtime_error(error);
    }

    if (!(IdentifyBase = OpenLibrary("identify.library", IDENTIFYVERSION)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open identify.library";
        throw std::runtime_error(error);
    }
}

IdentifyBaseScope::~IdentifyBaseScope()
{
    if (IdentifyBase != nullptr)
    {
        CloseLibrary(IdentifyBase);
        IdentifyBase = nullptr;
    }
}

bool IdentifyBaseScope::isOpen() const
{
    return IdentifyBase != nullptr;
}

Library *IdentifyBaseScope::library() const
{
    return IdentifyBase;
}

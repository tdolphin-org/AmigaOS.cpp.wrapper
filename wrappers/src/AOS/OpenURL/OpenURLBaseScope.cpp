//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "OpenURLBaseScope.hpp"

#include <proto/exec.h>
#include <proto/openurl.h>
#include <stdexcept>

struct Library *OpenURLBase = nullptr;

OpenURLBaseScope::OpenURLBaseScope(const bool optional)
{
    if (OpenURLBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + " " + OPENURLNAME + " already open!";
        throw std::runtime_error(error);
    }

    if (!(OpenURLBase = OpenLibrary(OPENURLNAME, OPENURLVER)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + OPENURLNAME;
        throw std::runtime_error(error);
    }
}

OpenURLBaseScope::~OpenURLBaseScope()
{
    if (OpenURLBase != nullptr)
    {
        CloseLibrary(OpenURLBase);
        OpenURLBase = nullptr;
    }
}

bool OpenURLBaseScope::isOpen() const
{
    return OpenURLBase != nullptr;
}

Library *OpenURLBaseScope::library() const
{
    return OpenURLBase;
}

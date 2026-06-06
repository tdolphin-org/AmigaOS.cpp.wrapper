//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "ASLBaseScope.hpp"

#include <libraries/asl.h>
#include <proto/exec.h>
#include <stdexcept>

struct Library *ASLBase = nullptr;

ASLBaseScope::ASLBaseScope(const bool optional)
{
    if (ASLBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + AslName " already open!";
        throw std::runtime_error(error);
    }

    if (!(ASLBase = OpenLibrary("asl.library", 0)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + AslName;
        throw std::runtime_error(error);
    }
}

ASLBaseScope::~ASLBaseScope()
{
    if (ASLBase != nullptr)
    {
        CloseLibrary((struct Library *)ASLBase);
        ASLBase = nullptr;
    }
}

bool ASLBaseScope::isOpen() const
{
    return ASLBase != nullptr;
}

struct Library *ASLBaseScope::library() const
{
    return ASLBase;
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "DosBaseScope.hpp"

#include <dos/dos.h>
#include <proto/exec.h>
#include <stdexcept>

#define DOSNAME "dos.library"

struct Library *DosBase = nullptr;

DosBaseScope::DosBaseScope(const bool optional)
{
    if (DosBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + DOSNAME " already open!";
        throw std::runtime_error(error);
    }

    if (!(DosBase = OpenLibrary(DOSNAME, 39))) // 39 = AmigaOS 3.0
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + DOSNAME;
        throw std::runtime_error(error);
    }
}

DosBaseScope::~DosBaseScope()
{
    if (DosBase != nullptr)
    {
        CloseLibrary(DosBase);
        DosBase = nullptr;
    }
}

bool DosBaseScope::isOpen() const
{
    return DosBase != nullptr;
}

struct Library *DosBaseScope::library() const
{
    return DosBase;
}

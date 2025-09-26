//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "PCIXBaseScope.hpp"

#include <proto/exec.h>
#include <stdexcept>

struct Library *PCIXBase = nullptr;

#define PCIXNAME "pcix.library"

PCIXBaseScope::PCIXBaseScope(const bool optional)
{
    if (PCIXBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + PCIXNAME " already open!";
        throw std::runtime_error(error);
    }

    if (!(PCIXBase = OpenLibrary(PCIXNAME, 51)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + PCIXNAME;
        throw std::runtime_error(error);
    }
}

PCIXBaseScope::~PCIXBaseScope()
{
    if (PCIXBase != nullptr)
    {
        CloseLibrary((struct Library *)PCIXBase);
        PCIXBase = nullptr;
    }
}

bool PCIXBaseScope::isOpen() const
{
    return PCIXBase != nullptr;
}

struct Library *PCIXBaseScope::library() const
{
    return PCIXBase;
}

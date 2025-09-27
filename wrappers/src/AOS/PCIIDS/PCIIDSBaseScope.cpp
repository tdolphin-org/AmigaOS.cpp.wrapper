//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "PCIIDSBaseScope.hpp"

#include <proto/exec.h>
#include <stdexcept>

struct Library *PCIIDSBase = nullptr;

#define PCIIDSNAME "pciids.library"

PCIIDSBaseScope::PCIIDSBaseScope(const bool optional)
{
    if (PCIIDSBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + PCIIDSNAME " already open!";
        throw std::runtime_error(error);
    }

    if (!(PCIIDSBase = OpenLibrary(PCIIDSNAME, 50)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + PCIIDSNAME;
        throw std::runtime_error(error);
    }
}

PCIIDSBaseScope::~PCIIDSBaseScope()
{
    if (PCIIDSBase != nullptr)
    {
        CloseLibrary((struct Library *)PCIIDSBase);
        PCIIDSBase = nullptr;
    }
}

bool PCIIDSBaseScope::isOpen() const
{
    return PCIIDSBase != nullptr;
}

struct Library *PCIIDSBaseScope::library() const
{
    return PCIIDSBase;
}

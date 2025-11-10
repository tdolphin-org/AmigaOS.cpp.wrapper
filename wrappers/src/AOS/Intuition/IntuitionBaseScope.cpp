//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "IntuitionBaseScope.hpp"

#include <intuition/intuitionbase.h>
#include <proto/exec.h>
#include <stdexcept>

#define INTUITIONNAME "intuition.library"

struct IntuitionBase *IntuitionBase = nullptr;

IntuitionBaseScope::IntuitionBaseScope(const bool optional)
{
    if (IntuitionBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + INTUITIONNAME " already open!";
        throw std::runtime_error(error);
    }

    if (!(IntuitionBase = (struct IntuitionBase *)OpenLibrary(INTUITIONNAME, 39))) // 39 = AmigaOS 3.0
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + INTUITIONNAME;
        throw std::runtime_error(error);
    }
}

IntuitionBaseScope::~IntuitionBaseScope()
{
    if (IntuitionBase != nullptr)
    {
        CloseLibrary((struct Library *)IntuitionBase);
        IntuitionBase = nullptr;
    }
}

bool IntuitionBaseScope::isOpen() const
{
    return IntuitionBase != nullptr;
}

struct IntuitionBase *IntuitionBaseScope::library() const
{
    return IntuitionBase;
}

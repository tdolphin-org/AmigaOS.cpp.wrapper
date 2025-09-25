//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "ExpansionBaseScope.hpp"

#include <libraries/expansion.h>
#include <proto/exec.h>
#include <proto/expansion.h>
#include <stdexcept>

struct ExpansionBase *ExpansionBase = nullptr;

ExpansionBaseScope::ExpansionBaseScope(const bool optional)
{
    if (ExpansionBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + EXPANSIONNAME " already open!";
        throw std::runtime_error(error);
    }

    if (!(ExpansionBase = (struct ExpansionBase *)OpenLibrary(EXPANSIONNAME, 0)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + EXPANSIONNAME;
        throw std::runtime_error(error);
    }
}

ExpansionBaseScope::~ExpansionBaseScope()
{
    if (ExpansionBase != nullptr)
    {
        CloseLibrary((struct Library *)ExpansionBase);
        ExpansionBase = nullptr;
    }
}

bool ExpansionBaseScope::isOpen() const
{
    return ExpansionBase != nullptr;
}

struct ExpansionBase *ExpansionBaseScope::library() const
{
    return ExpansionBase;
}

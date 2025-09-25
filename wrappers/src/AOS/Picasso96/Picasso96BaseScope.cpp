//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Picasso96BaseScope.hpp"

#include <proto/exec.h>
#include <proto/Picasso96.h>
#include <stdexcept>

struct Library *P96Base = nullptr;

Picasso96BaseScope::Picasso96BaseScope(const bool optional)
{
    if (P96Base != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + " " + P96NAME + " already open!";
        throw std::runtime_error(error);
    }

    if (!(P96Base = OpenLibrary(P96NAME, 2)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + P96NAME;
        throw std::runtime_error(error);
    }
}

Picasso96BaseScope::~Picasso96BaseScope()
{
    if (P96Base != nullptr)
    {
        CloseLibrary(P96Base);
        P96Base = nullptr;
    }
}

bool Picasso96BaseScope::isOpen() const
{
    return P96Base != nullptr;
}

Library *Picasso96BaseScope::library() const
{
    return P96Base;
}

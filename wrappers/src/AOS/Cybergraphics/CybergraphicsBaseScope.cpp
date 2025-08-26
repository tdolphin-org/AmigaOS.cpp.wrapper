//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "CybergraphicsBaseScope.hpp"

#include <cybergraphx/cybergraphics.h>
#include <proto/exec.h>
#include <stdexcept>

struct Library *CyberGfxBase = nullptr;

CybergraphicsBaseScope::CybergraphicsBaseScope(const bool optional)
{
    if (CyberGfxBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + CYBERGFXNAME " already open!";
        throw std::runtime_error(error);
    }

    if (!(CyberGfxBase = OpenLibrary(CYBERGFXNAME, CYBERGFX_INCLUDE_VERSION)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + CYBERGFXNAME;
        throw std::runtime_error(error);
    }
}

CybergraphicsBaseScope::~CybergraphicsBaseScope()
{
    if (CyberGfxBase != nullptr)
    {
        CloseLibrary((struct Library *)CyberGfxBase);
        CyberGfxBase = nullptr;
    }
}

bool CybergraphicsBaseScope::isOpen() const
{
    return CyberGfxBase != nullptr;
}

struct Library *CybergraphicsBaseScope::library() const
{
    return CyberGfxBase;
}

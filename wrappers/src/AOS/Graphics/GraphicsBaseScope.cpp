//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "GraphicsBaseScope.hpp"

#include <graphics/gfxbase.h>
#include <proto/exec.h>
#include <stdexcept>

struct GfxBase *GfxBase = nullptr;

GraphicsBaseScope::GraphicsBaseScope(const bool optional)
{
    if (GfxBase != nullptr)
    {
        auto error = std::string { __PRETTY_FUNCTION__ } + GRAPHICSNAME " already open!";
        throw std::runtime_error(error);
    }

    if (!(GfxBase = (struct GfxBase *)OpenLibrary(GRAPHICSNAME, 37)))
    {
        if (optional)
            return;

        auto error = std::string { __PRETTY_FUNCTION__ } + " failed to open " + GRAPHICSNAME;
        throw std::runtime_error(error);
    }
}

GraphicsBaseScope::~GraphicsBaseScope()
{
    if (GfxBase != nullptr)
    {
        CloseLibrary((struct Library *)GfxBase);
        GfxBase = nullptr;
    }
}

bool GraphicsBaseScope::isOpen() const
{
    return GfxBase != nullptr;
}

struct GfxBase *GraphicsBaseScope::library() const
{
    return GfxBase;
}

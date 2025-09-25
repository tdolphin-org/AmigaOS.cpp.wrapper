//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <exec/libraries.h>

struct GfxBase;

class GraphicsBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    GraphicsBaseScope(const bool optional = false);
    ~GraphicsBaseScope();

    bool isOpen() const;
    struct GfxBase *library() const;
};

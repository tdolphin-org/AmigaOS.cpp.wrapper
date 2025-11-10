//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <exec/libraries.h>

struct IntuitionBase;

class IntuitionBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    IntuitionBaseScope(const bool optional = false);
    ~IntuitionBaseScope();

    bool isOpen() const;
    struct IntuitionBase *library() const;
};

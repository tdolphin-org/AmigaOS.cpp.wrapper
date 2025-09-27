//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <exec/libraries.h>

class PCIIDSBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    PCIIDSBaseScope(const bool optional = false);
    ~PCIIDSBaseScope();

    bool isOpen() const;
    struct Library *library() const;
};

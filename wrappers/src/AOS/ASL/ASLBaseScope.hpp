//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <exec/libraries.h>

class ASLBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    ASLBaseScope(const bool optional = false);
    ~ASLBaseScope();

    bool isOpen() const;
    struct Library *library() const;
};

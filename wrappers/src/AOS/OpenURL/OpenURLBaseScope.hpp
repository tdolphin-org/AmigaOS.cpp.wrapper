//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/libraries.h>

class OpenURLBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    OpenURLBaseScope(const bool optional = false);
    ~OpenURLBaseScope();

    bool isOpen() const;
    Library *library() const;
};

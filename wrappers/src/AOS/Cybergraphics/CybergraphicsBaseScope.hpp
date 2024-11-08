//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/libraries.h>

class CybergraphicsBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    CybergraphicsBaseScope(const bool optional = false);
    ~CybergraphicsBaseScope();

    bool isOpen() const;
    struct Library *library() const;
};

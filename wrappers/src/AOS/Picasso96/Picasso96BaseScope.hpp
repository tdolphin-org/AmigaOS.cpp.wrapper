//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#ifdef __AROS__
#error "AOS::Picasso96 wrapper is not available on AROS - Picasso96 library does not exist on AROS"
#endif

#include <exec/libraries.h>

class Picasso96BaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    Picasso96BaseScope(const bool optional = false);
    ~Picasso96BaseScope();

    bool isOpen() const;
    Library *library() const;
};

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#ifdef __AROS__
#error "AOS::Identify wrapper is not available on AROS - openpci.library does not exist on AROS"
#endif

#include <exec/libraries.h>

class IdentifyBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    IdentifyBaseScope(const bool optional = false);
    ~IdentifyBaseScope();

    bool isOpen() const;
    Library *library() const;
};

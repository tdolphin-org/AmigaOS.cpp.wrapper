//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <exec/libraries.h>

struct DosLibrary;

class DosBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    DosBaseScope(const bool optional = false);
    ~DosBaseScope();

    bool isOpen() const;
    struct DosLibrary *library() const;
};

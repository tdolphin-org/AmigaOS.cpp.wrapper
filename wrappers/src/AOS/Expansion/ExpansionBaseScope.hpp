//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/libraries.h>

struct ExpansionBase;

class ExpansionBaseScope
{
  public:
    /// @brief constructor, opens library, opening can be optional (so means try to open)
    /// @param optional true if open is optional, than get will return nullptr
    ExpansionBaseScope(const bool optional = false);
    ~ExpansionBaseScope();

    bool isOpen() const;
    struct ExpansionBase *library() const;
};

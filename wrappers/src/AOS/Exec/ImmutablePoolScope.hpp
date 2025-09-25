//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "PoolScope.hpp"

#include <string>
#include <vector>

namespace AOS::Exec
{
    class ImmutablePoolScope : private PoolScope
    {
        char **mpItemsList;

      public:
        /// @brief CreatePool(MEMF_PUBLIC, puddleSize = vector.total.size + some.margin, treshSize);
        ImmutablePoolScope(const std::vector<std::string> &vector, const unsigned long treshSize);
        ~ImmutablePoolScope();

        char **itemsList() const
        {
            return mpItemsList;
        }
    };
}

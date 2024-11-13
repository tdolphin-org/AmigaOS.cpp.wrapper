//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "ImmutablePoolScope.hpp"

#include <proto/exec.h>
#include <stdexcept>

namespace AOS::Exec
{
    ImmutablePoolScope::ImmutablePoolScope(const std::vector<std::string> &vector, const unsigned long treshSize)
      : PoolScope([&]() {
          auto totalSize = 0ul;
          for (const auto &item : vector)
              totalSize += item.length() + 1; // 1 byte for each end of string '\0'
          return totalSize;
      }())
    {
        mpItemsList = new char *[vector.size() + 1];

        // fill pool
        auto i = 0;
        for (const auto &elem : vector)
        {
            auto pstr = (char *)Alloc(elem.length() + 1);
            CopyMem((APTR)elem.c_str(), pstr, elem.length() + 1);
            mpItemsList[i++] = pstr;
        }
        mpItemsList[i] = nullptr; // end of list
    }

    ImmutablePoolScope::~ImmutablePoolScope()
    {
        delete[] mpItemsList;
    }
}

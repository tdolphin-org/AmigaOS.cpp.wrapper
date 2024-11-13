//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "PoolScope.hpp"

#include <proto/exec.h>
#include <stdexcept>
#include <string>

namespace AOS::Exec
{
    PoolScope::PoolScope(const unsigned long puddleSize, const unsigned long treshSize)
    {
        mPool = CreatePool(MEMF_PUBLIC, puddleSize, treshSize);
        if (mPool == nullptr)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreatePool(MEMF_PUBLIC," + std::to_string(puddleSize) + ","
                + std::to_string(treshSize) + ") failed!";
            throw std::runtime_error(error);
        }
    }

    PoolScope::PoolScope(const unsigned long puddleSize)
      : PoolScope(puddleSize, puddleSize)
    {
    }

    PoolScope::~PoolScope()
    {
        DeletePool(mPool);
    }

    APTR PoolScope::Alloc(const unsigned long memSize)
    {
        return AllocPooled(mPool, memSize);
    }

    void PoolScope::Free(const APTR memory, const unsigned long memSize)
    {
        FreePooled(mPool, memory, memSize);
    }
}

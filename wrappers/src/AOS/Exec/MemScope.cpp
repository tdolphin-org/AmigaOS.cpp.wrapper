//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "MemScope.hpp"

#include <proto/exec.h>
#include <stdexcept>
#include <string>

namespace AOS::Exec
{
    MemScope::MemScope(const unsigned long byteSize, const unsigned long attributes /* = MEMF_ANY */)
    {
        if (byteSize != 0)
        {
            mMem = AllocMem(byteSize, attributes); // TODO create wrapper class for methods (like AOS::Exec::libAllocMem)
            if (mMem == nullptr)
            {
                auto error = std::string { __PRETTY_FUNCTION__ } + " AllocMem(" + std::to_string(byteSize) + ","
                    + std::to_string(attributes) + ") failed!";
                throw std::runtime_error(error);
            }
        }
        else
            mMem = nullptr;

        mSize = byteSize;
    }

    MemScope::~MemScope()
    {
        if (mMem)
            FreeMem(mMem, mSize);
    }
}

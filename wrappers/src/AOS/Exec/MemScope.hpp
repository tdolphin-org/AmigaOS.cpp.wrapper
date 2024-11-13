//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/memory.h>
#include <exec/types.h>

namespace AOS::Exec
{
    class MemScope
    {
        APTR mMem;
        unsigned long mSize;

      public:
        /// @brief AllocMem(byteSize, attributes) - Allocate memory given certain requirements
        /// https://amigadev.elowar.com/read/ADCD_2.1/Includes_and_Autodocs_2._guide/node0332.html
        /// byteSize - the size of the desired block in bytes. (The operating system will automatically round this number to a multiple of
        ///            the system memory chunk size)
        /// attributes - If no flags are set (MEMF_ANY = 0), the system will return the best available memory block.  For expanded systems,
        ///              the fast memory pool is searched first.
        MemScope(const unsigned long byteSize, const unsigned long attributes = MEMF_ANY);

        /// @brief FreeMem(memoryBlock, byteSize)
        ~MemScope();

        APTR mem() const
        {
            return mMem;
        }

        unsigned long size() const
        {
            return mSize;
        }
    };
}

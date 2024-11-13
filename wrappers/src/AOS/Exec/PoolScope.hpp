//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/types.h>

namespace AOS::Exec
{
    class PoolScope
    {
        APTR mPool;

      public:
        /// @brief CreatePool(MEMF_PUBLIC, puddleSize, treshSize) - Generate a private memory pool header (V39)
        /// http://amigadev.elowar.com/read/ADCD_2.1/Includes_and_Autodocs_3._guide/node01FD.html
        /// puddleSize - the size of Puddles...
        /// threshSize - the largest allocation that goes into normal puddles
        ///              This *MUST* be less than or equal to puddleSize
        ///              (CreatePool() will fail if it is not)
        PoolScope(const unsigned long puddleSize, const unsigned long treshSize);
        PoolScope(const unsigned long puddleSize);
        ~PoolScope();

        /// @brief AllocPooled(poolHeader, memSize)
        APTR Alloc(const unsigned long memSize);

        /// @brief FreePooled(poolHeader, memory, memSize)
        void Free(const APTR memory, const unsigned long memSize);

        APTR pool() const
        {
            return mPool;
        }
    };
}

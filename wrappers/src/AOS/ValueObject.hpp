//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <intuition/classusr.h>

namespace AOS
{
// Type of a tag value (tag.ti_Data). It is IPTR (64-bit) on AROS x86_64, while on
// classic AmigaOS/MorphOS IPTR is either not available in the SDK or equals ULONG.
#ifdef __AROS__
    using TagData = IPTR;
#else
    using TagData = ULONG;
#endif

    class ValueObject
    {
        enum class ValueType
        {
            ValueULong,
            ValueLong,
            ValuePointer,
            ValuePtrArray,
        };

        const ValueType mType;
        union Value
        {
            const APTR pointer;
            const ULONG ulong;
            const LONG slong;
            const APTR *pArray;

            Value(const APTR pointer)
              : pointer(pointer)
            {
            }
            Value(const ULONG ulong)
              : ulong(ulong)
            {
            }
            Value(const LONG slong)
              : slong(slong)
            {
            }
            Value(const APTR *pArray)
              : pArray(pArray)
            {
            }
        } mValue;

      public:
        ValueObject(const void *pointer);
        ValueObject(const unsigned long ulong);
        ValueObject(const long slong);
        ValueObject(const void **pArray);
        ValueObject(const bool boolval);

        TagData value() const;
    };
}

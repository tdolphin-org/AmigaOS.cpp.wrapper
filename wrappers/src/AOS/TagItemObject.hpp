//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "ValueObject.hpp"

#include <utility/tagitem.h>

namespace AOS
{
    class TagItemObject
    {
        const unsigned long mTagName;
        ValueObject mValueObject;

      public:
        TagItemObject(const unsigned long tagName, const void *pointer);
        TagItemObject(const unsigned long tagName, const unsigned long ulong);
        TagItemObject(const unsigned long tagName, const long slong);
        TagItemObject(const unsigned long tagName, const void **pArray);

        struct TagItem object() const;
    };
}

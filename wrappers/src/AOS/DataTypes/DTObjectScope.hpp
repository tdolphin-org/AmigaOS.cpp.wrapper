//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <datatypes/datatypes.h>
#include <intuition/classusr.h>
#include <string>

namespace AOS::DataTypes
{
    class DTObjectScope
    {
        std::string mName;
        Object *mDataTypeObject;

      public:
        DTObjectScope(const std::string &name, bool exceptionOnError = true);
        ~DTObjectScope();

        Object *object() const
        {
            return mDataTypeObject;
        }
    };
}

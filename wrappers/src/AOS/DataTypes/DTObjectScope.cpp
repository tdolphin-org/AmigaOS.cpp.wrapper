//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "DTObjectScope.hpp"

#include <proto/datatypes.h>
#include <stdexcept>

#ifdef TRACE_AMIGAOS
#include <iostream>
#endif

namespace AOS::DataTypes
{
    DTObjectScope::DTObjectScope(const std::string &name, bool exceptionOnError)
      : mName(name)
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << " (" << name << "," << exceptionOnError << ")" << std::endl;
#endif

#ifdef __MORPHOS__
        mDataTypeObject = NewDTObject((APTR)name.c_str(), TAG_END);
#else
        mDataTypeObject = NewDTObject(name.c_str(), TAG_END);
#endif
        if (!mDataTypeObject && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " NewDTObject(" + name + ") failed!";
            throw std::runtime_error(error);
        }
    }

    DTObjectScope::~DTObjectScope()
    {
        if (mDataTypeObject)
            DisposeDTObject(mDataTypeObject);
    }
}

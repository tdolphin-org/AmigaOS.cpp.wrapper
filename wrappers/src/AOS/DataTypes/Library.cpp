//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include "ToString.hpp"

#include <proto/datatypes.h>

#ifdef TRACE_AMIGAOS
#include <iostream>
#endif

namespace AOS::DataTypes
{
    ObtainDataTypeResult::ObtainDataTypeResult(const enum GroupID groupID, const std::string &baseName)
      : mGroupID(groupID)
      , mBaseName(baseName)
    {
    }

    ObtainDataTypeResult Library::libObtainDataType(const AOS::Dos::LockScope &lockScope) noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif

        if (lockScope.isValid())
        {
            struct DataTypeHeader *dth = nullptr;
            struct DataType *dtn = nullptr;

            if (dtn = ObtainDataTypeA(DTST_FILE, (APTR)lockScope.lock(), nullptr))
            {
                dth = dtn->dtn_Header;
                ReleaseDataType(dtn);
                return ObtainDataTypeResult((const enum GroupID)dth->dth_GroupID, dth->dth_BaseName);
            }
        }

        return ObtainDataTypeResult();
    }

    ObtainDataTypeResult Library::libObtainDataType(const std::string &fileName) noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << " (" << fileName << ")" << std::endl;
#endif

        AOS::Dos::LockScope fileLockScope(fileName, false);
        return libObtainDataType(fileLockScope);
    }
}

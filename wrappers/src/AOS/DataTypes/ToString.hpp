//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/types.h>
#include <string>

namespace AOS::DataTypes
{
    class ToString
    {
      public:
        /// @brief from DataTypeHeader::dth_GroupID
        /// @param groupID
        static std::string FromGroup(const unsigned long groupID);
    };
}

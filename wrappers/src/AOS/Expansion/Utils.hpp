//
//  AmigaOS C++ wrapper
//
//  _c 2024 TDolphin
//

#pragma once

#include "ValueTypes/ManufacturerID.hpp"

#include <string>

namespace AOS::Expansion
{
    class Utils
    {
      public:
        static std::string GetManufacturerName(const enum ManufacturerID manufacturerID);
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
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

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <string>

namespace AOS::PCIIDS
{
    struct Library
    {
        /// @brief pciids.libraray/PCIIDS_GetVendorName
        static std::string libGetVendorName(const unsigned long vendorId) noexcept;
        /// @brief pciids.libraray/PCIIDS_GetDeviceName
        static std::string libGetDeviceName(const unsigned long vendorId, const unsigned long deviceId) noexcept;
        /// @brief pciids.libraray/PCIIDS_GetClassName
        static std::string libGetClassName(const unsigned long classId) noexcept;
    };
}

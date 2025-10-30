//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include <proto/pciids.h>

namespace AOS::PCIIDS
{
    std::string Library::libGetVendorName(const unsigned long vendorId) noexcept
    {
        auto name = PCIIDS_GetVendorName(vendorId);
        return name ? name : "Unknown";
    }

    std::string Library::libGetDeviceName(const unsigned long vendorId, const unsigned long deviceId) noexcept
    {
        auto name = PCIIDS_GetDeviceName(vendorId, deviceId);
        return name ? name : "Unknown";
    }

    std::string Library::libGetClassName(const unsigned long classId) noexcept
    {
        auto name = PCIIDS_GetClassName(classId);
        return name ? name : "Unknown";
    }
}

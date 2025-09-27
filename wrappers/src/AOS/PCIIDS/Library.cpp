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
        return PCIIDS_GetVendorName(vendorId);
    }

    std::string Library::libGetDeviceName(const unsigned long vendorId, const unsigned long deviceId) noexcept
    {
        return PCIIDS_GetDeviceName(vendorId, deviceId);
    }

    std::string Library::libGetClassName(const unsigned long classId) noexcept
    {
        return PCIIDS_GetClassName(classId);
    }
}

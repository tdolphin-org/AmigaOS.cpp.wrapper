//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "Core/Singleton.hpp"

#include "ClipboardDeviceScope.hpp"

#include <string>

namespace AOS::Devices
{
    class ClipboardDeviceCore
    {
        friend class td::Singleton<ClipboardDeviceCore>;

        ClipboardDeviceScope mClipboardDeviceScope;

        ClipboardDeviceCore();

        bool Write(const void *pData, const unsigned long size) const;
        bool WriteLong(const LONG *pData) const;
        bool WriteLong(const char pData[4]) const;

        bool Update() const;

      public:
        void Copy(const std::string &content) const;
    };

    /// @brief main ClipboardDevice (singleton) object
    typedef class td::Singleton<ClipboardDeviceCore> ClipboardDevice;
}

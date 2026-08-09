//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "Library.hpp"

#include <intuition/monitorclass.h>
#include <proto/intuition.h>

// GetAttr stores the value through @storagePtr: AROS declares it as IPTR* (pointer
// sized), AmigaOS/MorphOS as ULONG*. Cast the address of a const char* to the
// platform's storage type so the SDK-required pointer type matches exactly.
#ifdef __AROS__
#define AOS_GETATTR_STORAGE IPTR
#else
#define AOS_GETATTR_STORAGE ULONG
#endif

namespace AOS::Intuition
{
    std::vector<Monitor> Library::libGetMonitorList(const bool removeMultiMonitor)
    {
        Object **pMonitorsArray = GetMonitorList(nullptr);
        if (!pMonitorsArray)
            return {};

        std::vector<Monitor> result;

        auto i = 0;
        while (pMonitorsArray[i] != nullptr)
        {
            const char *pMonitorName = nullptr;
            const char *pDriverName = nullptr;
            const char *pManufacturerName = nullptr;
            unsigned long manufacturerId = 0, productId = 0;
            unsigned long memorySize = 0;
            unsigned long memoryClock = 0;
            unsigned long engineClock = 0; // gpu clock

            GetAttr(MA_MonitorName, pMonitorsArray[i], (AOS_GETATTR_STORAGE *)&pMonitorName);

            if (removeMultiMonitor) // check for multi-monitor setups, so .1, .2 suffixes
            {
                std::string monitorNameStr(pMonitorName);
                auto dotPos = monitorNameStr.rfind('.');
                auto suffixLength = monitorNameStr.length() - dotPos - 1;
                if (suffixLength > 0 && suffixLength <= 2)
                {
                    // suffix looks like .1 or .x, consider this a multi-monitor entry
                    i++;
                    continue;
                }
            }

            GetAttr(MA_Manufacturer, pMonitorsArray[i], (AOS_GETATTR_STORAGE *)&pManufacturerName);
            GetAttr(MA_DriverName, pMonitorsArray[i], (AOS_GETATTR_STORAGE *)&pDriverName);
            GetAttr(MA_ManufacturerID, pMonitorsArray[i], &manufacturerId);
            GetAttr(MA_MemorySize, pMonitorsArray[i], &memorySize);
            GetAttr(MA_ProductID, pMonitorsArray[i], &productId);
            GetAttr(MA_MemoryClock, pMonitorsArray[i], &memoryClock);
#ifdef MA_EngineClock
            GetAttr(MA_EngineClock, pMonitorsArray[i], &engineClock);
#endif

            result.push_back({ pMonitorName, pDriverName, pManufacturerName, manufacturerId, productId, memorySize,
                               memoryClock ? std::optional<unsigned long>(memoryClock) : std::nullopt,
                               engineClock ? std::optional<unsigned long>(engineClock) : std::nullopt });

            i++;
        }

        FreeMonitorList(pMonitorsArray);

        return result;
    }
}

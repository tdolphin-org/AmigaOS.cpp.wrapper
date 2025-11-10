//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include <intuition/monitorclass.h>
#include <proto/intuition.h>

namespace AOS::Intuition
{
    std::vector<Monitor> Library::libGetMonitorList()
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

            GetAttr(MA_MonitorName, pMonitorsArray[i], (ULONG *)&pMonitorName);
            GetAttr(MA_Manufacturer, pMonitorsArray[i], (ULONG *)&pManufacturerName);
            GetAttr(MA_DriverName, pMonitorsArray[i], (ULONG *)&pDriverName);
            GetAttr(MA_ManufacturerID, pMonitorsArray[i], &manufacturerId);
            GetAttr(MA_MemorySize, pMonitorsArray[i], &memorySize);
            GetAttr(MA_ProductID, pMonitorsArray[i], &productId);
            GetAttr(MA_MemoryClock, pMonitorsArray[i], &memoryClock);
            GetAttr(MA_EngineClock, pMonitorsArray[i], &engineClock);

            result.push_back({ pMonitorName, pDriverName, pManufacturerName, manufacturerId, productId, memorySize,
                               memoryClock ? std::optional<unsigned long>(memoryClock) : std::nullopt,
                               engineClock ? std::optional<unsigned long>(engineClock) : std::nullopt });
            i++;
        }

        FreeMonitorList(pMonitorsArray);

        return result;
    }
}

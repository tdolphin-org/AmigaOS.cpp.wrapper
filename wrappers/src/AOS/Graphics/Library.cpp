//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include <proto/cybergraphics.h>
#include <proto/graphics.h>

namespace AOS::Graphics
{
    std::set<std::string> Library::GetMonitors()
    {
        DisplayInfoHandle handle;
        MonitorInfo monitorInfo;

        std::set<std::string> monitors;

        auto id = INVALID_ID;
        while ((id = NextDisplayInfo(id)) != INVALID_ID)
        {
            handle = FindDisplayInfo(id);
            if (!handle)
                continue;

            if (!GetDisplayInfoData(handle, (UBYTE *)&monitorInfo, sizeof(MonitorInfo), DTAG_MNTR, INVALID_ID))
                continue;

            if ((monitorInfo.Mspc) && (monitorInfo.Mspc->ms_Node.xln_Name))
            {
                std::string fullName { monitorInfo.Mspc->ms_Node.xln_Name };
                if (fullName.find('.') != std::string::npos)
                    monitors.insert(fullName);
            }
        }

        return monitors;
    }
}

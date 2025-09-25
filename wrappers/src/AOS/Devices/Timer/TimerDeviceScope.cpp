//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "TimerDeviceScope.hpp"

#include "TimerGlobals.hpp"

#include <proto/exec.h>
#include <stdexcept>

namespace AOS
{
    TimerDeviceScope::TimerDeviceScope(bool exceptionOnError)
    {
        mpTimerIO = (struct timerequest *)AllocMem(sizeof(struct timerequest), MEMF_CLEAR | MEMF_PUBLIC);
        if (!mpTimerIO && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " AllocMem() failed!";
            throw std::runtime_error(error);
        }

        mOpenResult = OpenDevice(TIMERNAME, UNIT_MICROHZ, (IORequest *)mpTimerIO, 0);
        if (mOpenResult != 0 && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " OpenDevice(\"" TIMERNAME "\", ...) failed!";
            throw std::runtime_error(error);
        }

        TimerBase = (struct Device *)mpTimerIO->tr_node.io_Device;
    }

    TimerDeviceScope::~TimerDeviceScope()
    {
        if (mOpenResult == 0)
            CloseDevice((IORequest *)mpTimerIO);

        if (mpTimerIO)
            FreeMem(mpTimerIO, sizeof(struct timerequest));

        TimerBase = nullptr;
    }
}

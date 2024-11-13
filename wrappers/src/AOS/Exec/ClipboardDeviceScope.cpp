//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "ClipboardDeviceScope.hpp"

#include <clib/exec_protos.h>
#include <stdexcept>

namespace AOS::Exec
{
    ClipboardDeviceScope::ClipboardDeviceScope(bool exceptionOnError)
      : mIOClipReqScope(mPortScope.msgPort())
    {
        mOpenResult = OpenDevice("clipboard.device", 0L, (IORequest *)mIOClipReqScope.ioClipReq(), 0);
        if (mOpenResult != 0 && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " OpenDevice(\"clipboard.device\", ...) failed!";
            throw std::runtime_error(error);
        }
    }

    ClipboardDeviceScope::~ClipboardDeviceScope()
    {
        if (mOpenResult == 0)
            CloseDevice((IORequest *)mIOClipReqScope.ioClipReq());
    }
}

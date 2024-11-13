//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "AOS/AmigaLib/IOClipReqScope.hpp"
#include "AOS/AmigaLib/MsgPortScope.hpp"

namespace AOS::Exec
{
    class ClipboardDeviceScope
    {
        AmigaLib::MsgPortScope mPortScope;
        AmigaLib::IOClipReqScope mIOClipReqScope;

        char mOpenResult;

      public:
        ClipboardDeviceScope(bool exceptionOnError = true);
        ~ClipboardDeviceScope();

        IOClipReq *ioClipReq() const
        {
            return mIOClipReqScope.ioClipReq();
        }
    };
}

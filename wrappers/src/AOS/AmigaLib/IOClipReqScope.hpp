//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <devices/clipboard.h>

namespace AOS::AmigaLib
{
    class IOClipReqScope
    {
        IOClipReq *mpIOClipReq;

      public:
        IOClipReqScope(MsgPort *msgPort, bool exceptionOnError = true);
        ~IOClipReqScope();

        IOClipReq *ioClipReq() const
        {
            return mpIOClipReq;
        }
    };
}

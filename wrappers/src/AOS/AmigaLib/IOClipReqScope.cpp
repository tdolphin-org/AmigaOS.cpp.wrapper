//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "IOClipReqScope.hpp"

#include <clib/alib_protos.h>
#include <devices/clipboard.h>
#include <stdexcept>

namespace AOS::AmigaLib
{
    IOClipReqScope::IOClipReqScope(MsgPort *msgPort, bool exceptionOnError)
    {
        mpIOClipReq = (IOClipReq *)CreateExtIO(msgPort, sizeof(IOClipReq));
        if (mpIOClipReq == nullptr && exceptionOnError)
        {
            auto error = std::string { __PRETTY_FUNCTION__ } + " CreateExtIO(..) failed!";
            throw std::runtime_error(error);
        }
    }

    IOClipReqScope::~IOClipReqScope()
    {
        if (mpIOClipReq)
            DeleteExtIO((IORequest *)mpIOClipReq);
    }
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <exec/ports.h>

namespace AOS::AmigaLib
{
    class MsgPortScope
    {
        MsgPort *mpMsgPort;

      public:
        MsgPortScope(bool exceptionOnError = true);
        ~MsgPortScope();

        MsgPort *msgPort() const
        {
            return mpMsgPort;
        }
    };
}

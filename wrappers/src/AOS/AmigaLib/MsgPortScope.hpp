//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <exec/ports.h>
#include <string>

namespace AOS::AmigaLib
{
    class MsgPortScope
    {
        MsgPort *mpMsgPort { nullptr };

      public:
        MsgPortScope(bool exceptionOnError = true);
        MsgPortScope(const std::string &name, bool exceptionOnError = true);
        ~MsgPortScope();

        MsgPort *msgPort() const
        {
            return mpMsgPort;
        }
    };
}

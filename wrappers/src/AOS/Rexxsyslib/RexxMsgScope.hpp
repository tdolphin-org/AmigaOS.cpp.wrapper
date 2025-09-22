//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include "AOS/AmigaLib/MsgPortScope.hpp"

#include <rexx/storage.h>

namespace AOS::Rexxsyslib
{
    // scope for a RexxMsg and its MsgPort
    // uses MsgPortScope, CreateRexxMsg() and DeleteRexxMsg()
    class RexxMsgScope
    {
        AmigaLib::MsgPortScope mMsgPortScope;
        struct RexxMsg *mpRexxMsg { nullptr };

      public:
        RexxMsgScope(const std::string &name, bool exceptionOnError = true);
        RexxMsgScope(bool exceptionOnError = true);
        ~RexxMsgScope();

        struct RexxMsg *rexxMsg() const
        {
            return mpRexxMsg;
        }

        struct MsgPort *msgPort() const
        {
            return mMsgPortScope.msgPort();
        }
    };
}
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
    class RexxMsgScope
    {
        AmigaLib::MsgPortScope mMsgPortScope;
        struct RexxMsg *mpRexxMsg;

      public:
        RexxMsgScope(const std::string &name, bool exceptionOnError = true);
        ~RexxMsgScope();

        struct RexxMsg *rexxMsg() const
        {
            return mpRexxMsg;
        }
    };
}
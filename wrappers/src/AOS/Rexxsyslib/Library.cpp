//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include "RexxMsgScope.hpp"

#include <proto/exec.h>
#include <proto/rexxsyslib.h>

namespace AOS::Rexxsyslib
{
    RexxMsg *Library::GetRexxMsg(const RexxMsgScope &scope) noexcept
    {
        return (struct RexxMsg *)GetMsg(scope.msgPort());
    }

    unsigned char *Library::libCreateArgstring(const std::string &string) noexcept
    {
        return CreateArgstring(string.c_str(), string.length());
    }

    void Library::libDeleteArgstring(unsigned char *argstring) noexcept
    {
        DeleteArgstring((char *)argstring);
    }

    struct RexxMsg *Library::libCreateRexxMsg(const struct MsgPort &port, const std::string &extension, const std::string &host) noexcept
    {
        return CreateRexxMsg(&port, extension.c_str(), host.c_str());
    }

    void Library::libDeleteRexxMsg(struct RexxMsg &msg) noexcept
    {
        DeleteRexxMsg(&msg);
    }

    void Library::libClearRexxMsg(struct RexxMsg &rexxMsg, const unsigned long count) noexcept
    {
        ClearRexxMsg(&rexxMsg, count);
    }

    bool Library::libFillRexxMsg(RexxMsg &rexxMsg, const unsigned long count, const unsigned long mask) noexcept
    {
        return (bool)FillRexxMsg(&rexxMsg, count, mask);
    }

    bool Library::libIsRexxMsg(const RexxMsg &rexxMsg) noexcept
    {
        return (bool)IsRexxMsg(&rexxMsg);
    }
}

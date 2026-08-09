//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
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
#ifdef __AROS__
        return CreateArgstring((const UBYTE *)string.c_str(), string.length());
#else
        return CreateArgstring(string.c_str(), string.length());
#endif
    }

    void Library::libDeleteArgstring(unsigned char *argstring) noexcept
    {
#ifdef __MORPHOS__
        DeleteArgstring((char *)argstring);
#else
        DeleteArgstring((UBYTE *)argstring);
#endif
    }

    RexxMsg *Library::libCreateRexxMsg(const MsgPort &port, const std::string &extension, const std::string &host) noexcept
    {
#ifdef __AROS__
        return CreateRexxMsg((MsgPort *)&port, (UBYTE *)extension.c_str(), (UBYTE *)host.c_str());
#else
        return CreateRexxMsg((MsgPort *)&port, extension.c_str(), host.c_str());
#endif
    }

    void Library::libDeleteRexxMsg(RexxMsg &msg) noexcept
    {
        DeleteRexxMsg(&msg);
    }

    void Library::libClearRexxMsg(RexxMsg &rexxMsg, const unsigned long count) noexcept
    {
        ClearRexxMsg(&rexxMsg, count);
    }

    bool Library::libFillRexxMsg(RexxMsg &rexxMsg, const unsigned long count, const unsigned long mask) noexcept
    {
        return (bool)FillRexxMsg(&rexxMsg, count, mask);
    }

    bool Library::libIsRexxMsg(const RexxMsg &rexxMsg) noexcept
    {
        return (bool)IsRexxMsg((RexxMsg *)&rexxMsg);
    }
}

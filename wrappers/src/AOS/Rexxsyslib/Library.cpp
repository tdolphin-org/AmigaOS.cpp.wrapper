//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include <proto/rexxsyslib.h>

namespace AOS::Rexxsyslib
{
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
}

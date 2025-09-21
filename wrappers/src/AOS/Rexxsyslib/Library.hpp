//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <rexx/storage.h>
#include <string>

namespace AOS::Rexxsyslib
{
    struct Library
    {
        /// @brief rexxsyslib.library/CreateRexxMsg
        static struct RexxMsg *libCreateRexxMsg(const struct MsgPort &port, const std::string &extension, const std::string &host) noexcept;
        /// @brief rexxsyslib.library/DeleteRexxMsg
        static void libDeleteRexxMsg(struct RexxMsg &rexxMsg) noexcept;
        /// @brief rexxsyslib.library/ClearRexxMsg
        static void libClearRexxMsg(struct RexxMsg &rexxMsg, const unsigned long count) noexcept;
    };
}

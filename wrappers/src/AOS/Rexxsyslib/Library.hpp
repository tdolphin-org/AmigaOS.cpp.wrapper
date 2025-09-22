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
        /// @brief rexxsyslib.library/CreateArgstring
        static unsigned char *libCreateArgstring(const std::string &string) noexcept;
        /// @brief rexxsyslib.library/DeleteArgstring
        /// @param argstring pointer to buffer returned by CreateArgstring
        static void libDeleteArgstring(unsigned char *argstring) noexcept;
        /// @brief rexxsyslib.library/CreateRexxMsg
        static struct RexxMsg *libCreateRexxMsg(const struct MsgPort &port, const std::string &extension, const std::string &host) noexcept;
        /// @brief rexxsyslib.library/DeleteRexxMsg
        static void libDeleteRexxMsg(struct RexxMsg &rexxMsg) noexcept;
        /// @brief rexxsyslib.library/ClearRexxMsg
        static void libClearRexxMsg(struct RexxMsg &rexxMsg, const unsigned long count) noexcept;
        /// @brief rexxsyslib.library/FillRexxMsg
        static bool libFillRexxMsg(struct RexxMsg &rexxMsg, const unsigned long count, const unsigned long mask) noexcept;
        /// @brief rexxsyslib.library/IsRexxMsg
        static bool libIsRexxMsg(const struct RexxMsg &rexxMsg) noexcept;
    };
}

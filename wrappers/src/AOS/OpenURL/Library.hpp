//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "AOS/TagBuilderRoot.hpp"

#include <string>

namespace AOS::OpenURL
{
    struct Library
    {
        /// @brief openurl:Open()
        static bool libOpen(const std::string &url) noexcept;

        /// @brief builder for openurl:OpenA()
        struct OpenBuilder : public TagBuilderRoot
        {
            /// @brief [ @b URL_BringToFront ]
            OpenBuilder &tagBringToFront(const bool bringToFront);
            /// @brief [ @b URL_Launch ]
            OpenBuilder &tagLaunch(const bool launch);
            /// @brief [ @b URL_NewWindow ]
            OpenBuilder &tagNewWindow(const bool newWindow);
            /// @brief [ @b URL_Show ]
            OpenBuilder &tagShow(const bool show);

            bool call(const std::string &url);
        };
    };
}

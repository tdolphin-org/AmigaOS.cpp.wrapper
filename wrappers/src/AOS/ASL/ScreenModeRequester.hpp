//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "RequesterRoot.hpp"

#include <cstdint>

namespace AOS::ASL
{
    class ScreenModeRequesterTagsBuilder;

    class ScreenModeRequesterScope : public RequesterScopeRoot
    {
      public:
        ScreenModeRequesterScope();
        explicit ScreenModeRequesterScope(const ScreenModeRequesterTagsBuilder &tags);

        bool request() const;

        const struct ScreenModeRequester *screenModeRequester() const
        {
            return static_cast<const struct ScreenModeRequester *>(aslRequest());
        }
    };

    class ScreenModeRequesterTagsBuilder : public RequesterTagsBuilderRoot
    {
      public:
        /// @brief [ @b ASLSM_InitialDisplayID ]
        ScreenModeRequesterTagsBuilder &tagInitialDisplayID(const uint32_t displayId);
        /// @brief [ @b ASLSM_InitialDisplayWidth ]
        ScreenModeRequesterTagsBuilder &tagInitialDisplayWidth(const uint32_t width);
        /// @brief [ @b ASLSM_InitialDisplayHeight ]
        ScreenModeRequesterTagsBuilder &tagInitialDisplayHeight(const uint32_t height);
        /// @brief [ @b ASLSM_InitialDisplayDepth ]
        ScreenModeRequesterTagsBuilder &tagInitialDisplayDepth(const uint16_t depth);
        /// @brief [ @b ASLSM_InitialOverscanType ]
        ScreenModeRequesterTagsBuilder &tagInitialOverscanType(const uint16_t overscanType);
        /// @brief [ @b ASLSM_InitialAutoScroll ]
        ScreenModeRequesterTagsBuilder &tagInitialAutoScroll(const bool enabled);
        /// @brief [ @b ASLSM_InitialInfoOpened ]
        ScreenModeRequesterTagsBuilder &tagInitialInfoOpened(const bool opened);
        /// @brief [ @b ASLSM_InitialInfoLeftEdge ]
        ScreenModeRequesterTagsBuilder &tagInitialInfoLeftEdge(const int16_t leftEdge);
        /// @brief [ @b ASLSM_InitialInfoTopEdge ]
        ScreenModeRequesterTagsBuilder &tagInitialInfoTopEdge(const int16_t topEdge);

        /// @brief [ @b ASLSM_DoWidth ]
        ScreenModeRequesterTagsBuilder &tagDoWidth(const bool enabled);
        /// @brief [ @b ASLSM_DoHeight ]
        ScreenModeRequesterTagsBuilder &tagDoHeight(const bool enabled);
        /// @brief [ @b ASLSM_DoDepth ]
        ScreenModeRequesterTagsBuilder &tagDoDepth(const bool enabled);
        /// @brief [ @b ASLSM_DoOverscanType ]
        ScreenModeRequesterTagsBuilder &tagDoOverscanType(const bool enabled);
        /// @brief [ @b ASLSM_DoAutoScroll ]
        ScreenModeRequesterTagsBuilder &tagDoAutoScroll(const bool enabled);

        /// @brief [ @b ASLSM_PropertyFlags ]
        ScreenModeRequesterTagsBuilder &tagPropertyFlags(const uint32_t flags);
        /// @brief [ @b ASLSM_PropertyMask ]
        ScreenModeRequesterTagsBuilder &tagPropertyMask(const uint32_t mask);
        /// @brief [ @b ASLSM_MinWidth ]
        ScreenModeRequesterTagsBuilder &tagMinWidth(const uint32_t width);
        /// @brief [ @b ASLSM_MaxWidth ]
        ScreenModeRequesterTagsBuilder &tagMaxWidth(const uint32_t width);
        /// @brief [ @b ASLSM_MinHeight ]
        ScreenModeRequesterTagsBuilder &tagMinHeight(const uint32_t height);
        /// @brief [ @b ASLSM_MaxHeight ]
        ScreenModeRequesterTagsBuilder &tagMaxHeight(const uint32_t height);
        /// @brief [ @b ASLSM_MinDepth ]
        ScreenModeRequesterTagsBuilder &tagMinDepth(const uint32_t depth);
        /// @brief [ @b ASLSM_MaxDepth ]
        ScreenModeRequesterTagsBuilder &tagMaxDepth(const uint32_t depth);

        /// @brief [ @b ASLSM_FilterFunc ]
        ScreenModeRequesterTagsBuilder &tagFilterFunc(const void *pFilterFunc);
        /// @brief [ @b ASLSM_CustomSMList ]
        ScreenModeRequesterTagsBuilder &tagCustomSMList(const void *pCustomSMList);
    };
}

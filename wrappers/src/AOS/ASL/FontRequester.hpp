//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "RequesterRoot.hpp"

#include <cstdint>
#include <string>

namespace AOS::ASL
{
    class FontRequesterTagsBuilder;

    class FontRequesterScope : public RequesterScopeRoot
    {
      public:
        FontRequesterScope();
        explicit FontRequesterScope(const FontRequesterTagsBuilder &tags);

        bool request() const;

        const struct FontRequester *fontRequester() const
        {
            return static_cast<const struct FontRequester *>(aslRequest());
        }
    };

    class FontRequesterTagsBuilder : public RequesterTagsBuilderRoot
    {
      public:
        using HookFunc = void (*)();
        using FilterFunc = void (*)();

        /// @brief [ @b ASLFO_HookFunc ]
        FontRequesterTagsBuilder &tagHookFunc(const HookFunc pHookFunc);
        /// @brief [ @b ASLFO_InitialName ]
        FontRequesterTagsBuilder &tagInitialName(const std::string &name);
        /// @brief [ @b ASLFO_InitialSize ]
        FontRequesterTagsBuilder &tagInitialSize(const uint16_t size);
        /// @brief [ @b ASLFO_InitialStyle ]
        FontRequesterTagsBuilder &tagInitialStyle(const uint8_t style);
        /// @brief [ @b ASLFO_InitialFlags ]
        FontRequesterTagsBuilder &tagInitialFlags(const uint8_t flags);
        /// @brief [ @b ASLFO_InitialFrontPen ]
        FontRequesterTagsBuilder &tagInitialFrontPen(const uint8_t frontPen);
        /// @brief [ @b ASLFO_InitialBackPen ]
        FontRequesterTagsBuilder &tagInitialBackPen(const uint8_t backPen);
        /// @brief [ @b ASLFO_MinHeight ]
        FontRequesterTagsBuilder &tagMinHeight(const uint16_t minHeight);
        /// @brief [ @b ASLFO_MaxHeight ]
        FontRequesterTagsBuilder &tagMaxHeight(const uint16_t maxHeight);
        /// @brief [ @b ASLFO_Flags ]
        FontRequesterTagsBuilder &tagFlags(const uint32_t flags);
        /// @brief [ @b ASLFO_ModeList ]
        FontRequesterTagsBuilder &tagModeList(const void *pModeList);
        /// @brief [ @b ASLFO_DoFrontPen ]
        FontRequesterTagsBuilder &tagDoFrontPen(const bool enabled);
        /// @brief [ @b ASLFO_DoBackPen ]
        FontRequesterTagsBuilder &tagDoBackPen(const bool enabled);
        /// @brief [ @b ASLFO_DoStyle ]
        FontRequesterTagsBuilder &tagDoStyle(const bool enabled);
        /// @brief [ @b ASLFO_DoDrawMode ]
        FontRequesterTagsBuilder &tagDoDrawMode(const bool enabled);
        /// @brief [ @b ASLFO_FixedWidthOnly ]
        FontRequesterTagsBuilder &tagFixedWidthOnly(const bool enabled);
        /// @brief [ @b ASLFO_FilterFunc ]
        FontRequesterTagsBuilder &tagFilterFunc(const FilterFunc pFilterFunc);
        /// @brief [ @b ASLFO_InitialDrawMode ]
        FontRequesterTagsBuilder &tagInitialDrawMode(const uint8_t drawMode);
        /// @brief [ @b ASLFO_FrontPens ]
        FontRequesterTagsBuilder &tagFrontPens(const void *pPens);
        /// @brief [ @b ASLFO_BackPens ]
        FontRequesterTagsBuilder &tagBackPens(const void *pPens);
        /// @brief [ @b ASLFO_MaxFrontPen ]
        FontRequesterTagsBuilder &tagMaxFrontPen(const uint8_t maxFrontPen);
        /// @brief [ @b ASLFO_MaxBackPen ]
        FontRequesterTagsBuilder &tagMaxBackPen(const uint8_t maxBackPen);
        /// @brief [ @b ASLFO_SampleText ]
        FontRequesterTagsBuilder &tagSampleText(const std::string &text);
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "TagBuilderRoot.hpp"
#include "TagsScope.hpp"
#include "ValueTypes/RequesterType.hpp"

#include <optional>
#include <string>

namespace AOS::ASL
{
    // base class for ASL requesters, like FileRequester, FontRequester, ScreenModeRequester
    class RequesterScopeRoot
    {
        void *mAllocAsl { nullptr };

      protected:
        RequesterScopeRoot(const RequesterType type, const std::vector<AOS::TagItemObject> &tags);
        ~RequesterScopeRoot();

        void *aslRequest() const
        {
            return mAllocAsl;
        }
    };

    class RequesterTagsBuilderRoot : public TagBuilderRoot
    {
      public:
        RequesterTagsBuilderRoot() = default;

        /// @brief [ @b ASLFR_TitleText, @b ASLFO_TitleText, @b ASLSM_TitleText ]
        RequesterTagsBuilderRoot &tagTitleText(const std::string &title);

        /// @brief [ @b ASLFR_Window, @b ASLFO_Window, @b ASLSM_Window ]
        RequesterTagsBuilderRoot &tagWindow(const struct Window *pWindow);
        /// @brief [ @b ASLFR_InitialLeftEdge, @b ASLFO_InitialLeftEdge, @b ASLSM_InitialLeftEdge ]
        RequesterTagsBuilderRoot &tagInitialLeftEdge(const int16_t leftEdge);
        /// @brief [ @b ASLFR_InitialTopEdge, @b ASLFO_InitialTopEdge, @b ASLSM_InitialTopEdge ]
        RequesterTagsBuilderRoot &tagInitialTopEdge(const int16_t topEdge);
        /// @brief [ @b ASLFR_InitialWidth, @b ASLFO_InitialWidth, @b ASLSM_InitialWidth ]
        RequesterTagsBuilderRoot &tagInitialWidth(const int16_t width);
        /// @brief [ @b ASLFR_InitialHeight, @b ASLFO_InitialHeight, @b ASLSM_InitialHeight ]
        RequesterTagsBuilderRoot &tagInitialHeight(const int16_t height);
    };
}

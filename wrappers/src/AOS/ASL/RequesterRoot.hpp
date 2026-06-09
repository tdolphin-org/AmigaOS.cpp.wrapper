//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "AOS/TagBuilderRoot.hpp"
#include "AOS/TagsScope.hpp"
#include "ValueTypes/RequesterType.hpp"

#include <optional>
#include <string>

struct Screen;
struct Window;
struct TextAttr;
struct Locale;

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
        using IntuiMsgFunc = void (*)();

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

        /// @brief [ @b ASLFR_PositiveText, @b ASLFO_PositiveText, @b ASLSM_PositiveText ]
        RequesterTagsBuilderRoot &tagPositiveText(const std::string &text);
        /// @brief [ @b ASLFR_NegativeText, @b ASLFO_NegativeText, @b ASLSM_NegativeText ]
        RequesterTagsBuilderRoot &tagNegativeText(const std::string &text);

        /// @brief [ @b ASLFR_Screen, @b ASLFO_Screen, @b ASLSM_Screen ]
        RequesterTagsBuilderRoot &tagScreen(const struct Screen *pScreen);
        /// @brief [ @b ASLFR_PubScreenName, @b ASLFO_PubScreenName, @b ASLSM_PubScreenName ]
        RequesterTagsBuilderRoot &tagPubScreenName(const std::string &name);
        /// @brief [ @b ASLFR_PrivateIDCMP, @b ASLFO_PrivateIDCMP, @b ASLSM_PrivateIDCMP ]
        RequesterTagsBuilderRoot &tagPrivateIDCMP(const bool enabled);
        /// @brief [ @b ASLFR_SleepWindow, @b ASLFO_SleepWindow, @b ASLSM_SleepWindow ]
        RequesterTagsBuilderRoot &tagSleepWindow(const bool enabled);

        /// @brief [ @b ASLFR_Locale, @b ASLFO_Locale, @b ASLSM_Locale ]
        RequesterTagsBuilderRoot &tagLocale(const struct Locale *pLocale);
        /// @brief [ @b ASLFR_TextAttr, @b ASLFO_TextAttr, @b ASLSM_TextAttr ]
        RequesterTagsBuilderRoot &tagTextAttr(const struct TextAttr *pTextAttr);
        /// @brief [ @b ASLFR_UserData, @b ASLFO_UserData, @b ASLSM_UserData ]
        RequesterTagsBuilderRoot &tagUserData(const void *pUserData);
        /// @brief [ @b ASLFR_IntuiMsgFunc, @b ASLFO_IntuiMsgFunc, @b ASLSM_IntuiMsgFunc ]
        RequesterTagsBuilderRoot &tagIntuiMsgFunc(const IntuiMsgFunc pIntuiMsgFunc);

        /// @brief [ @b ASLFR_PopToFront, @b ASLFO_PopToFront, @b ASLSM_PopToFront ] (V44+)
        RequesterTagsBuilderRoot &tagPopToFront(const bool enabled);
        /// @brief [ @b ASLFR_Activate, @b ASLFO_Activate, @b ASLSM_Activate ] (V45+)
        RequesterTagsBuilderRoot &tagActivate(const bool enabled);
    };
}

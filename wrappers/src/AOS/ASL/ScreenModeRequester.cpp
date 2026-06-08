//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "ScreenModeRequester.hpp"

#include <proto/asl.h>

namespace AOS::ASL
{
    ScreenModeRequesterScope::ScreenModeRequesterScope()
      : RequesterScopeRoot(RequesterType::ScreenMode, { })
    {
    }

    ScreenModeRequesterScope::ScreenModeRequesterScope(const ScreenModeRequesterTagsBuilder &tags)
      : RequesterScopeRoot(RequesterType::ScreenMode, tags.getTags())
    {
    }

    bool ScreenModeRequesterScope::request() const
    {
        return ::AslRequest(aslRequest(), nullptr);
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialDisplayID(const uint32_t displayId)
    {
        PushTag(ASLSM_InitialDisplayID, static_cast<unsigned long>(displayId));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialDisplayWidth(const uint32_t width)
    {
        PushTag(ASLSM_InitialDisplayWidth, static_cast<unsigned long>(width));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialDisplayHeight(const uint32_t height)
    {
        PushTag(ASLSM_InitialDisplayHeight, static_cast<unsigned long>(height));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialDisplayDepth(const uint16_t depth)
    {
        PushTag(ASLSM_InitialDisplayDepth, static_cast<unsigned long>(depth));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialOverscanType(const uint16_t overscanType)
    {
        PushTag(ASLSM_InitialOverscanType, static_cast<unsigned long>(overscanType));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialAutoScroll(const bool enabled)
    {
        PushTag(ASLSM_InitialAutoScroll, enabled);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialInfoOpened(const bool opened)
    {
        PushTag(ASLSM_InitialInfoOpened, opened);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialInfoLeftEdge(const int16_t leftEdge)
    {
        PushTag(ASLSM_InitialInfoLeftEdge, static_cast<long>(leftEdge));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagInitialInfoTopEdge(const int16_t topEdge)
    {
        PushTag(ASLSM_InitialInfoTopEdge, static_cast<long>(topEdge));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagDoWidth(const bool enabled)
    {
        PushTag(ASLSM_DoWidth, enabled);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagDoHeight(const bool enabled)
    {
        PushTag(ASLSM_DoHeight, enabled);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagDoDepth(const bool enabled)
    {
        PushTag(ASLSM_DoDepth, enabled);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagDoOverscanType(const bool enabled)
    {
        PushTag(ASLSM_DoOverscanType, enabled);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagDoAutoScroll(const bool enabled)
    {
        PushTag(ASLSM_DoAutoScroll, enabled);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagPropertyFlags(const uint32_t flags)
    {
        PushTag(ASLSM_PropertyFlags, static_cast<unsigned long>(flags));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagPropertyMask(const uint32_t mask)
    {
        PushTag(ASLSM_PropertyMask, static_cast<unsigned long>(mask));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagMinWidth(const uint32_t width)
    {
        PushTag(ASLSM_MinWidth, static_cast<unsigned long>(width));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagMaxWidth(const uint32_t width)
    {
        PushTag(ASLSM_MaxWidth, static_cast<unsigned long>(width));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagMinHeight(const uint32_t height)
    {
        PushTag(ASLSM_MinHeight, static_cast<unsigned long>(height));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagMaxHeight(const uint32_t height)
    {
        PushTag(ASLSM_MaxHeight, static_cast<unsigned long>(height));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagMinDepth(const uint32_t depth)
    {
        PushTag(ASLSM_MinDepth, static_cast<unsigned long>(depth));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagMaxDepth(const uint32_t depth)
    {
        PushTag(ASLSM_MaxDepth, static_cast<unsigned long>(depth));
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagFilterFunc(const void *pFilterFunc)
    {
        PushTag(ASLSM_FilterFunc, pFilterFunc);
        return *this;
    }

    ScreenModeRequesterTagsBuilder &ScreenModeRequesterTagsBuilder::tagCustomSMList(const void *pCustomSMList)
    {
        PushTag(ASLSM_CustomSMList, pCustomSMList);
        return *this;
    }
}

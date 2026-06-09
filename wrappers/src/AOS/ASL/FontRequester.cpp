//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "FontRequester.hpp"

#include <proto/asl.h>

namespace AOS::ASL
{
    FontRequesterScope::FontRequesterScope()
      : RequesterScopeRoot(RequesterType::Font, { })
    {
    }

    FontRequesterScope::FontRequesterScope(const FontRequesterTagsBuilder &tags)
      : RequesterScopeRoot(RequesterType::Font, tags.getTags())
    {
    }

    bool FontRequesterScope::request() const
    {
        return ::AslRequest(aslRequest(), nullptr);
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagHookFunc(const HookFunc pHookFunc)
    {
        PushTag(ASLFO_HookFunc, reinterpret_cast<const void *>(pHookFunc));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagInitialName(const std::string &name)
    {
        PushTag(ASLFO_InitialName, name);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagInitialSize(const uint16_t size)
    {
        PushTag(ASLFO_InitialSize, static_cast<unsigned long>(size));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagInitialStyle(const uint8_t style)
    {
        PushTag(ASLFO_InitialStyle, static_cast<unsigned long>(style));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagInitialFlags(const uint8_t flags)
    {
        PushTag(ASLFO_InitialFlags, static_cast<unsigned long>(flags));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagInitialFrontPen(const uint8_t frontPen)
    {
        PushTag(ASLFO_InitialFrontPen, static_cast<unsigned long>(frontPen));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagInitialBackPen(const uint8_t backPen)
    {
        PushTag(ASLFO_InitialBackPen, static_cast<unsigned long>(backPen));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagMinHeight(const uint16_t minHeight)
    {
        PushTag(ASLFO_MinHeight, static_cast<unsigned long>(minHeight));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagMaxHeight(const uint16_t maxHeight)
    {
        PushTag(ASLFO_MaxHeight, static_cast<unsigned long>(maxHeight));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagFlags(const uint32_t flags)
    {
        PushTag(ASLFO_Flags, static_cast<unsigned long>(flags));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagModeList(const void *pModeList)
    {
        PushTag(ASLFO_ModeList, pModeList);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagDoFrontPen(const bool enabled)
    {
        PushTag(ASLFO_DoFrontPen, enabled);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagDoBackPen(const bool enabled)
    {
        PushTag(ASLFO_DoBackPen, enabled);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagDoStyle(const bool enabled)
    {
        PushTag(ASLFO_DoStyle, enabled);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagDoDrawMode(const bool enabled)
    {
        PushTag(ASLFO_DoDrawMode, enabled);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagFixedWidthOnly(const bool enabled)
    {
        PushTag(ASLFO_FixedWidthOnly, enabled);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagFilterFunc(const FilterFunc pFilterFunc)
    {
        PushTag(ASLFO_FilterFunc, reinterpret_cast<const void *>(pFilterFunc));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagInitialDrawMode(const uint8_t drawMode)
    {
        PushTag(ASLFO_InitialDrawMode, static_cast<unsigned long>(drawMode));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagFrontPens(const void *pPens)
    {
        PushTag(ASLFO_FrontPens, pPens);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagBackPens(const void *pPens)
    {
        PushTag(ASLFO_BackPens, pPens);
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagMaxFrontPen(const uint8_t maxFrontPen)
    {
        PushTag(ASLFO_MaxFrontPen, static_cast<unsigned long>(maxFrontPen));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagMaxBackPen(const uint8_t maxBackPen)
    {
        PushTag(ASLFO_MaxBackPen, static_cast<unsigned long>(maxBackPen));
        return *this;
    }

    FontRequesterTagsBuilder &FontRequesterTagsBuilder::tagSampleText(const std::string &text)
    {
        PushTag(ASLFO_SampleText, text);
        return *this;
    }
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "RequesterRoot.hpp"

#include <proto/asl.h>

namespace AOS::ASL
{
    RequesterScopeRoot::RequesterScopeRoot(const RequesterType type, const std::vector<AOS::TagItemObject> &tags)
    {
        TagsScope tagsScope(tags);
        mAllocAsl = ::AllocAslRequest(static_cast<unsigned long>(type), tagsScope.tagItems());
        if (mAllocAsl == nullptr)
            throw std::bad_alloc();
    }

    RequesterScopeRoot::~RequesterScopeRoot()
    {
        ::FreeAslRequest(mAllocAsl);
    }

    RequesterTagsBuilderRoot &RequesterTagsBuilderRoot::tagTitleText(const std::string &title)
    {
        PushTag(ASLFO_TitleText, title);
        return *this;
    }

    RequesterTagsBuilderRoot &RequesterTagsBuilderRoot::tagWindow(const Window *pWindow)
    {
        PushTag(ASLFO_Window, pWindow);
        return *this;
    }

    RequesterTagsBuilderRoot &RequesterTagsBuilderRoot::tagInitialLeftEdge(const int16_t leftEdge)
    {
        PushTag(ASLFO_InitialLeftEdge, static_cast<long>(leftEdge));
        return *this;
    }

    RequesterTagsBuilderRoot &RequesterTagsBuilderRoot::tagInitialTopEdge(const int16_t topEdge)
    {
        PushTag(ASLFO_InitialTopEdge, static_cast<long>(topEdge));
        return *this;
    }

    RequesterTagsBuilderRoot &RequesterTagsBuilderRoot::tagInitialWidth(const int16_t width)
    {
        PushTag(ASLFO_InitialWidth, static_cast<long>(width));
        return *this;
    }

    RequesterTagsBuilderRoot &RequesterTagsBuilderRoot::tagInitialHeight(const int16_t height)
    {
        PushTag(ASLFO_InitialHeight, static_cast<long>(height));
        return *this;
    }
}

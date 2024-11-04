//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include "AOS/TagsScope.hpp"

#include <proto/openurl.h>

namespace AOS::OpenURL
{
    bool Library::libOpen(const std::string &url) noexcept
    {
        return URL_Open((STRPTR)url.c_str(), TAG_END);
    }

    Library::OpenBuilder &Library::OpenBuilder::tagBringToFront(const bool bringToFront)
    {
        PushTag(URL_BringToFront, bringToFront);
        return *this;
    }

    Library::OpenBuilder &Library::OpenBuilder::tagLaunch(const bool launch)
    {
        PushTag(URL_Launch, launch);
        return *this;
    }

    Library::OpenBuilder &Library::OpenBuilder::tagNewWindow(const bool newWindow)
    {
        PushTag(URL_NewWindow, newWindow);
        return *this;
    }

    Library::OpenBuilder &Library::OpenBuilder::tagShow(const bool show)
    {
        PushTag(URL_Show, show);
        return *this;
    }

    bool Library::OpenBuilder::call(const std::string &url)
    {
        TagsScope tagsScope(getTags());
        return URL_OpenA((STRPTR)url.c_str(), tagsScope.tagItems());
    }
}
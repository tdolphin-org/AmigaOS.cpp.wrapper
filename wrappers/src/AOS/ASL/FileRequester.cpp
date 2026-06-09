//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "FileRequester.hpp"

#include <proto/asl.h>

namespace AOS::ASL
{
    FileRequesterScope::FileRequesterScope()
      : RequesterScopeRoot(RequesterType::File, { })
    {
    }

    FileRequesterScope::FileRequesterScope(const FileRequesterTagsBuilder &tags)
      : RequesterScopeRoot(RequesterType::File, tags.getTags())
    {
    }

    bool FileRequesterScope::request() const
    {
        return ::AslRequest(aslRequest(), nullptr);
    }

    std::optional<std::string> FileRequesterScope::file() const
    {
        const auto *req = fileRequester();
        if (req != nullptr && req->fr_File != nullptr)
            return std::string(req->fr_File);
        return std::nullopt;
    }

    std::optional<std::string> FileRequesterScope::drawer() const
    {
        const auto *req = fileRequester();
        if (req != nullptr && req->fr_Drawer != nullptr)
            return std::string(req->fr_Drawer);
        return std::nullopt;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagHookFunc(const HookFunc pHookFunc)
    {
        PushTag(ASLFR_HookFunc, reinterpret_cast<const void *>(pHookFunc));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagInitialFile(const std::string &file)
    {
        PushTag(ASLFR_InitialFile, file);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagInitialDrawer(const std::string &drawer)
    {
        PushTag(ASLFR_InitialDrawer, drawer);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagInitialPattern(const std::string &pattern)
    {
        PushTag(ASLFR_InitialPattern, pattern);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagFlags1(const uint32_t flags)
    {
        PushTag(ASLFR_Flags1, static_cast<unsigned long>(flags));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagFlags2(const uint32_t flags)
    {
        PushTag(ASLFR_Flags2, static_cast<unsigned long>(flags));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagDoSaveMode(const bool enabled)
    {
        PushTag(ASLFR_DoSaveMode, enabled);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagDoMultiSelect(const bool enabled)
    {
        PushTag(ASLFR_DoMultiSelect, enabled);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagDoPatterns(const bool enabled)
    {
        PushTag(ASLFR_DoPatterns, enabled);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagDrawersOnly(const bool enabled)
    {
        PushTag(ASLFR_DrawersOnly, enabled);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagFilterFunc(const FilterFunc pFilterFunc)
    {
        PushTag(ASLFR_FilterFunc, reinterpret_cast<const void *>(pFilterFunc));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagRejectIcons(const bool enabled)
    {
        PushTag(ASLFR_RejectIcons, enabled);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagRejectPattern(const std::string &pattern)
    {
        PushTag(ASLFR_RejectPattern, pattern);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagAcceptPattern(const std::string &pattern)
    {
        PushTag(ASLFR_AcceptPattern, pattern);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagFilterDrawers(const bool enabled)
    {
        PushTag(ASLFR_FilterDrawers, enabled);
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagIntuiMsgFunc(const IntuiMsgFunc pIntuiMsgFunc)
    {
        PushTag(ASLFR_IntuiMsgFunc, reinterpret_cast<const void *>(pIntuiMsgFunc));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagSetSortBy(const uint32_t sortBy)
    {
        PushTag(ASLFR_SetSortBy, static_cast<unsigned long>(sortBy));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagSetSortDrawers(const uint32_t sortDrawers)
    {
        PushTag(ASLFR_SetSortDrawers, static_cast<unsigned long>(sortDrawers));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagSetSortOrder(const uint32_t sortOrder)
    {
        PushTag(ASLFR_SetSortOrder, static_cast<unsigned long>(sortOrder));
        return *this;
    }

    FileRequesterTagsBuilder &FileRequesterTagsBuilder::tagInitialShowVolumes(const bool enabled)
    {
        PushTag(ASLFR_InitialShowVolumes, enabled);
        return *this;
    }
}

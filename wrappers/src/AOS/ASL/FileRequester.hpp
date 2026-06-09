//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "RequesterRoot.hpp"

#include <cstdint>
#include <optional>
#include <string>

namespace AOS::ASL
{
    class FileRequesterTagsBuilder;

    // New generic ASL-based file requester wrapper.
    // It intentionally coexists with legacy FileRequesterScope.
    class FileRequesterScope : public RequesterScopeRoot
    {
      public:
        FileRequesterScope();
        explicit FileRequesterScope(const FileRequesterTagsBuilder &tags);

        bool request() const;

        const struct FileRequester *fileRequester() const
        {
            return static_cast<const struct FileRequester *>(aslRequest());
        }

        std::optional<std::string> file() const;
        std::optional<std::string> drawer() const;
    };

    class FileRequesterTagsBuilder : public RequesterTagsBuilderRoot
    {
      public:
        using HookFunc = void (*)();
        using FilterFunc = void (*)();
        using IntuiMsgFunc = RequesterTagsBuilderRoot::IntuiMsgFunc;

        /// @brief [ @b ASLFR_HookFunc ]
        FileRequesterTagsBuilder &tagHookFunc(const HookFunc pHookFunc);
        /// @brief [ @b ASLFR_InitialFile ]
        FileRequesterTagsBuilder &tagInitialFile(const std::string &file);
        /// @brief [ @b ASLFR_InitialDrawer ]
        FileRequesterTagsBuilder &tagInitialDrawer(const std::string &drawer);
        /// @brief [ @b ASLFR_InitialPattern ]
        FileRequesterTagsBuilder &tagInitialPattern(const std::string &pattern);

        /// @brief [ @b ASLFR_Flags1 ]
        FileRequesterTagsBuilder &tagFlags1(const uint32_t flags);
        /// @brief [ @b ASLFR_Flags2 ]
        FileRequesterTagsBuilder &tagFlags2(const uint32_t flags);

        /// @brief [ @b ASLFR_DoSaveMode ]
        FileRequesterTagsBuilder &tagDoSaveMode(const bool enabled);
        /// @brief [ @b ASLFR_DoMultiSelect ]
        FileRequesterTagsBuilder &tagDoMultiSelect(const bool enabled);
        /// @brief [ @b ASLFR_DoPatterns ]
        FileRequesterTagsBuilder &tagDoPatterns(const bool enabled);

        /// @brief [ @b ASLFR_DrawersOnly ]
        FileRequesterTagsBuilder &tagDrawersOnly(const bool enabled);
        /// @brief [ @b ASLFR_FilterFunc ]
        FileRequesterTagsBuilder &tagFilterFunc(const FilterFunc pFilterFunc);
        /// @brief [ @b ASLFR_RejectIcons ]
        FileRequesterTagsBuilder &tagRejectIcons(const bool enabled);
        /// @brief [ @b ASLFR_RejectPattern ]
        FileRequesterTagsBuilder &tagRejectPattern(const std::string &pattern);
        /// @brief [ @b ASLFR_AcceptPattern ]
        FileRequesterTagsBuilder &tagAcceptPattern(const std::string &pattern);
        /// @brief [ @b ASLFR_FilterDrawers ]
        FileRequesterTagsBuilder &tagFilterDrawers(const bool enabled);

        /// @brief [ @b ASLFR_IntuiMsgFunc ]
        FileRequesterTagsBuilder &tagIntuiMsgFunc(const IntuiMsgFunc pIntuiMsgFunc);
        /// @brief [ @b ASLFR_SetSortBy ]
        FileRequesterTagsBuilder &tagSetSortBy(const uint32_t sortBy);
        /// @brief [ @b ASLFR_SetSortDrawers ]
        FileRequesterTagsBuilder &tagSetSortDrawers(const uint32_t sortDrawers);
        /// @brief [ @b ASLFR_SetSortOrder ]
        FileRequesterTagsBuilder &tagSetSortOrder(const uint32_t sortOrder);

        /// @brief [ @b ASLFR_InitialShowVolumes ] (V44+)
        FileRequesterTagsBuilder &tagInitialShowVolumes(const bool enabled);
    };
}

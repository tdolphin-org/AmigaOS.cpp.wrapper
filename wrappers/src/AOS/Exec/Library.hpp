//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <string>
#include <vector>

namespace AOS::Exec
{
    struct LibInfo
    {
        std::string libName;
        std::string version;
    };

    struct Library
    {
        /// @brief exec:FindTask(NULL) and return ptr
        static std::string CurrentTaskPid();

        /// @brief retirn list of all loaded libraries, datatypes, etc
        static std::vector<LibInfo> GetAllLibraryNames() noexcept;

        /// @brief exec:FindTask(NULL) and return ptr to struct Task
        static struct Task *libFindTask() noexcept;
        /// @brief exec:FindTask(name) and return ptr to struct Task
        static struct Task *libFindTask(const std::string &name) noexcept;
    };
}

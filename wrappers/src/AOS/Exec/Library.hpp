//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <string>

namespace AOS::Exec
{
    struct Library
    {
        /// @brief exec:FindTask(NULL) and return ptr
        static std::string CurrentTaskPid();

        /// @brief exec:FindTask(NULL) and return ptr to struct Task
        static struct Task *libFindTask() noexcept;
        /// @brief exec:FindTask(name) and return ptr to struct Task
        static struct Task *libFindTask(const std::string &name) noexcept;
    };
}

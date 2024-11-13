//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include "Core/ToString.hpp"

#include <proto/exec.h>

namespace AOS::Exec
{
    std::string Library::CurrentTaskPid()
    {
        auto task = FindTask((char *)nullptr);
        return ToString::FromDataPointer(task);
    }

    Task *Library::libFindTask() noexcept
    {
        return FindTask((char *)nullptr);
    }

    Task *Library::libFindTask(const std::string &name) noexcept
    {
        return FindTask(name.c_str());
    }
}

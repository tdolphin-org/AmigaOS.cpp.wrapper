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

    std::vector<LibInfo> Library::GetAllLibraryNames() noexcept
    {
        struct ::Library *lib;
        struct List *list = &SysBase->LibList;

        std::vector<LibInfo> result;

        Forbid();
        for (struct Node *node = list->lh_Head; node->ln_Succ; node = node->ln_Succ)
        {
            lib = (struct ::Library *)node;
            result.push_back({ lib->lib_Node.ln_Name, std::to_string(lib->lib_Version) + "." + std::to_string(lib->lib_Revision) });
        }
        Permit();

        return result;
    }

    Task *Library::libFindTask() noexcept
    {
        return FindTask((char *)nullptr);
    }

    Task *Library::libFindTask(const std::string &name) noexcept
    {
        return FindTask(name.c_str());
    }

    unsigned long Library::libAvailMem(const MEMF_Type type, const MEMF_Avail avail) noexcept
    {
        return AvailMem((unsigned long)type | (unsigned long)avail);
    }
}

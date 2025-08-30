//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include "Core/ToString.hpp"

#ifdef __MORPHOS__
#include <exec/execbase.h>
#endif
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

    void Library::libForbid() noexcept
    {
        Forbid();
    }

    void Library::libPermit() noexcept
    {
        Permit();
    }

    Task *Library::libFindTask() noexcept
    {
        return FindTask((char *)nullptr);
    }

    Task *Library::libFindTask(const std::string &name) noexcept
    {
        return FindTask(name.c_str());
    }

    unsigned long Library::libAvailMem(const enum MEMF_Type type, const enum MEMF_Avail avail) noexcept
    {
        return AvailMem((unsigned long)type | (unsigned long)avail);
    }

#ifdef __MORPHOS__
    std::variant<std::string, unsigned long, unsigned long long, bool> Library::libNewGetSystemAttrs(const enum SYSTEMINFOTYPE type,
                                                                                                     std::optional<unsigned long> cpuIdx)
    {
        char buffer[256];

        if (cpuIdx.has_value())
        {
            struct TagItem MyTags[] = { { SYSTEMINFOTAG_CPUINDEX, cpuIdx.value() }, { TAG_END, 0 } };
            NewGetSystemAttrsA(buffer, sizeof(buffer), (unsigned long)type, MyTags);
        }
        else
        {
            struct TagItem MyTags[] = { { TAG_END, 0 } };
            NewGetSystemAttrsA(buffer, sizeof(buffer), (unsigned long)type, MyTags);
        }

        return std::string(buffer);
    }
#endif
}

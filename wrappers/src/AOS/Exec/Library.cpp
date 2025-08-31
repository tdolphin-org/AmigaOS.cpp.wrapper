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

    std::vector<CPUInfo> Library::GetAllCPUs() noexcept
    {
        std::vector<CPUInfo> result;

        for (unsigned long i = 0; i < libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::CPUCOUNT); i++)
        {
            result.push_back({
                libNewGetSystemAttrsAsString(SYSTEMINFOTYPE::CPUFAMILYNAME, i),
                libNewGetSystemAttrsAsString(SYSTEMINFOTYPE::CPUNAME, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_CPUVERSION, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_CPUREVISION, i),
                libNewGetSystemAttrsAsUnsignedLongLong(SYSTEMINFOTYPE::PPC_CPUCLOCK, i),
                libNewGetSystemAttrsAsUnsignedLongLong(SYSTEMINFOTYPE::PPC_BUSCLOCK, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_ICACHEL1SIZE, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_DCACHEL1SIZE, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_ICACHEL2SIZE, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_DCACHEL2SIZE, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_ICACHEL3SIZE, i),
                libNewGetSystemAttrsAsUnsignedLong(SYSTEMINFOTYPE::PPC_DCACHEL3SIZE, i),
                libNewGetSystemAttrsAsBool(SYSTEMINFOTYPE::PPC_FPU, i),
                libNewGetSystemAttrsAsBool(SYSTEMINFOTYPE::PPC_ALTIVEC, i),
            });
        }

        return result;
    }

    std::variant<std::string, unsigned long, unsigned long long, bool> Library::libNewGetSystemAttrs(const enum SYSTEMINFOTYPE type,
                                                                                                     std::optional<unsigned long> cpuIdx)
    {
        switch (type)
        {
            case SYSTEMINFOTYPE::SYSTEM:
            case SYSTEMINFOTYPE::VENDOR:
            case SYSTEMINFOTYPE::REVISION:
            case SYSTEMINFOTYPE::CPUFAMILYNAME:
            case SYSTEMINFOTYPE::CPUNAME:
            case SYSTEMINFOTYPE::PPC_CPUTEMP:
                return libNewGetSystemAttrsAsString(type, cpuIdx);
            case SYSTEMINFOTYPE::MACHINE:
            case SYSTEMINFOTYPE::CPUCOUNT:
            case SYSTEMINFOTYPE::PPC_CPUVERSION:
            case SYSTEMINFOTYPE::PPC_CPUREVISION:
            case SYSTEMINFOTYPE::PPC_FPU:
            case SYSTEMINFOTYPE::PPC_ALTIVEC:
            case SYSTEMINFOTYPE::PPC_PERFMONITOR:
            case SYSTEMINFOTYPE::PPC_DATASTREAM:
            case SYSTEMINFOTYPE::PPC_ICACHEL1SIZE:
            case SYSTEMINFOTYPE::PPC_DCACHEL1SIZE:
            case SYSTEMINFOTYPE::PPC_ICACHEL2SIZE:
            case SYSTEMINFOTYPE::PPC_DCACHEL2SIZE:
            case SYSTEMINFOTYPE::PPC_ICACHEL3SIZE:
            case SYSTEMINFOTYPE::PPC_DCACHEL3SIZE:
                return libNewGetSystemAttrsAsUnsignedLong(type, cpuIdx);
            case SYSTEMINFOTYPE::PPC_BUSCLOCK:
            case SYSTEMINFOTYPE::PPC_CPUCLOCK:
                return libNewGetSystemAttrsAsUnsignedLongLong(type, cpuIdx);
            default:
                return libNewGetSystemAttrsAsUnsignedLong(type, cpuIdx);
        }
    }

    std::string Library::libNewGetSystemAttrsAsString(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx)
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

    bool Library::libNewGetSystemAttrsAsBool(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx)
    {
        return libNewGetSystemAttrsAsUnsignedLong(type, cpuIdx) != 0;
    }

    unsigned long Library::libNewGetSystemAttrsAsUnsignedLong(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx)
    {
        unsigned long result = 0;
        if (cpuIdx.has_value())
        {
            struct TagItem MyTags[] = { { SYSTEMINFOTAG_CPUINDEX, cpuIdx.value() }, { TAG_END, 0 } };
            NewGetSystemAttrsA(&result, sizeof(result), (unsigned long)type, MyTags);
        }
        else
        {
            struct TagItem MyTags[] = { { TAG_END, 0 } };
            NewGetSystemAttrsA(&result, sizeof(result), (unsigned long)type, MyTags);
        }

        return result;
    }

    unsigned long long Library::libNewGetSystemAttrsAsUnsignedLongLong(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx)
    {
        unsigned long long result = 0;
        if (cpuIdx.has_value())
        {
            struct TagItem MyTags[] = { { SYSTEMINFOTAG_CPUINDEX, cpuIdx.value() }, { TAG_END, 0 } };
            NewGetSystemAttrsA(&result, sizeof(result), (unsigned long)type, MyTags);
        }
        else
        {
            struct TagItem MyTags[] = { { TAG_END, 0 } };
            NewGetSystemAttrsA(&result, sizeof(result), (unsigned long)type, MyTags);
        }

        return result;
    }

#endif
}

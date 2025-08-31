//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "ValueTypes/MEMF.hpp"
#include "ValueTypes/SYSTEMINFOTYPE.hpp"

#ifdef __MORPHOS__
#include <optional>
#include <variant>
#endif
#include <string>
#include <vector>

namespace AOS::Exec
{
    struct LibInfo
    {
        std::string libName;
        std::string version;
    };

#ifdef __MORPHOS__
    struct CPUInfo
    {
        std::string family;
        std::string name;
        unsigned long version;
        unsigned long revision;
        unsigned long long clock;
        unsigned long long busClock;
        unsigned long l1InstructionCache; // level 1 instruction cache
        unsigned long l1DataCache; // level 1 data cache
        unsigned long l2InstructionCache; // level 2 instruction cache
        unsigned long l2DataCache; // level 2 data cache
        unsigned long l3InstructionCache; // level 3 instruction cache
        unsigned long l3DataCache; // level 3 data cache
        bool hasFPU;
        bool hasAltivec;
    };
#endif

    struct Library
    {
        /// @brief calls exec:FindTask(NULL) and return ptr
        static std::string CurrentTaskPid();

        /// @brief return list of all loaded libraries, datatypes, etc
        static std::vector<LibInfo> GetAllLibraryNames() noexcept;

        /// @brief exec/Forbid()
        static void libForbid() noexcept;
        /// @brief exec/Permit()
        static void libPermit() noexcept;

        /// @brief exec/FindTask(NULL) and return ptr to struct Task
        static struct Task *libFindTask() noexcept;
        /// @brief exec/FindTask(name) and return ptr to struct Task
        static struct Task *libFindTask(const std::string &name) noexcept;

        /// @brief exec/AvailMem(name) and returns the amount of free memory given certain attributes
        static unsigned long libAvailMem(const enum MEMF_Type type, const enum MEMF_Avail avail) noexcept;

#ifdef __MORPHOS__
        static std::vector<CPUInfo> GetAllCPUs() noexcept;

        static std::variant<std::string, unsigned long, unsigned long long, bool>
        libNewGetSystemAttrs(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx = std::nullopt);

        static std::string libNewGetSystemAttrsAsString(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx = std::nullopt);
        static bool libNewGetSystemAttrsAsBool(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx = std::nullopt);
        static unsigned long libNewGetSystemAttrsAsUnsignedLong(const enum SYSTEMINFOTYPE type,
                                                                std::optional<unsigned long> cpuIdx = std::nullopt);
        static unsigned long long libNewGetSystemAttrsAsUnsignedLongLong(const enum SYSTEMINFOTYPE type,
                                                                         std::optional<unsigned long> cpuIdx = std::nullopt);
#endif
    };
}

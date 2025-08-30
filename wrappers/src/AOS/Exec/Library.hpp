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
        std::string libNewGetSystemAttrs(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx = std::nullopt);
#endif
    };
}

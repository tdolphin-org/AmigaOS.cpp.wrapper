//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include "ValueTypes/GVF.hpp"

#include "std/optional.hpp"
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <string>
#include <vector>

namespace AOS::Dos
{
    struct Library
    {
        /// @brief calls exec:FindProcess(NULL), check type (NT_PROCESS) and return casted struct Task* to struct Process*
        static struct Process *FindProcess() noexcept;
        /// @brief calls exec:FindProcess(name), check type (NT_PROCESS) and return casted struct Task* to struct Process*
        static struct Process *FindProcess(const std::string &name) noexcept;

        /// @brief calls dos.library/Cli(void)
        static struct CommandLineInterface *libCli() noexcept;

        /// @brief calls dos.library/NameFromLock(lock) .. name from lock
        static std::string libNameFromLock(BPTR lock) noexcept;

        /// @brief calls dos.library/CreateDir()
        static BPTR libCreateDir(const std::string &name) noexcept;
        /// @brief calls dos.library/DeleteFile()
        static bool libDeleteFile(const std::string &fileName) noexcept;
        /// @brief calls dos.library/Rename()
        static bool libRename(const std::string &oldName, std::string &newName) noexcept;

        /// @brief calls dos.library/GetCurrentDirName (returns the current directory name)
        static std::string libGetCurrentDirName() noexcept;

        /// @brief calls dos.library/ExAll (Examine an entire directory)
        static std::vector<std::string> libExAll(const std::string &path, const std::string &pattern = "",
                                                 const bool files = true) noexcept;

        /// @brief calls dos.library/FindDosEntry (Finds a specific Dos List entry)
        static struct DosList *libFindDosEntry(const std::string &name, const unsigned long flags) noexcept;

        /// @brief calls dos.library/AssignAdd(name, lock) .. lock from path
        static bool libAssignAdd(const std::string &name, const std::string &path) noexcept;

        /// @brief calls dos.library/AddPart (Add a part to a path)
        /// @param path base path
        /// @param part part to add to the path
        /// @return The resulting path after adding the part or an empty optional if the operation failed
        static std::optional<std::string> libAddPart(const std::string &path, const std::string &part) noexcept;

        /// @brief calls dos.library/GetVar (Get a system or local variable)
        /// The default is to try to get a local variable first, then
        /// to try to get a global environment variable.
        static std::optional<std::string> libGetVar(const std::string &name, const enum AOS::Dos::GVF type = AOS::Dos::GVF::Var) noexcept;
    };
}

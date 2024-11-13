//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

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

        /// @brief dos.library/Cli(void)
        static struct CommandLineInterface *libCli() noexcept;

        /// @brief dos.library/NameFromLock(lock) .. name from lock
        static std::string libNameFromLock(BPTR lock) noexcept;

        /// @brief dos.library/CreateDir()
        static BPTR libCreateDir(const std::string &name) noexcept;
        /// @brief dos.library/DeleteFile()
        static bool libDeleteFile(const std::string &fileName) noexcept;
        /// @brief dos.library/Rename()
        static bool libRename(const std::string &oldName, std::string &newName) noexcept;

        /// @brief dos.library/GetCurrentDirName (returns the current directory name)
        static std::string libGetCurrentDirName() noexcept;

        /// @brief dos.library/ExAll (Examine an entire directory)
        static std::vector<std::string> libExAll(const std::string &path, const std::string &pattern = "",
                                                 const bool files = true) noexcept;

        /// @brief dos.library/FindDosEntry (Finds a specific Dos List entry)
        static struct DosList *libFindDosEntry(const std::string &name, const unsigned long flags) noexcept;

        /// @brief dos.library/AssignAdd(name, lock) .. lock from path
        static bool libAssignAdd(const std::string &name, const std::string &path) noexcept;
    };
}

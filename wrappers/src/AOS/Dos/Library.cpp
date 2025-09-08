//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "Library.hpp"

#include "AOS/Exec/Library.hpp"
#include "AOS/Exec/MemScope.hpp"
#include "Core/Random.hpp"
#include "Core/StringUtils.hpp"
#include "FileHandleScope.hpp"
#include "LockDosListScope.hpp"
#include "LockScope.hpp"

#include "amiga_std_light/iostream.hpp"
#include <dos/dostags.h>
#include <proto/dos.h>
#include <sstream>

namespace AOS::Dos
{
    Process *Library::FindProcess() noexcept
    {
        auto pTask = Exec::Library::libFindTask();
        if (pTask != nullptr && pTask->tc_Node.ln_Type == NT_PROCESS)
            return (Process *)pTask;
        return nullptr;
    }

    Process *Library::FindProcess(const std::string &name) noexcept
    {
        auto pTask = Exec::Library::libFindTask(name);
        if (pTask != nullptr && pTask->tc_Node.ln_Type == NT_PROCESS)
            return (Process *)pTask;
        return nullptr;
    }

    CommandLineInterface *Library::libCli() noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "()" << std::endl;
#endif

        // check if it is process
        if (Library::FindProcess() == nullptr)
            return nullptr;

        return Cli();
    }

    std::string Library::libNameFromLock(BPTR lock) noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "()" << std::endl;
#endif

        char buffer[512];
        if (NameFromLock(lock, buffer, sizeof(buffer)))
            return buffer;

        return {};
    }

    BPTR Library::libCreateDir(const std::string &name) noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "(" << name << ")" << std::endl;
#endif

        return CreateDir(name.c_str());
    }

    bool Library::libDeleteFile(const std::string &fileName) noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "(" << fileName << ")" << std::endl;
#endif

        return DeleteFile(fileName.c_str()) == TRUE;
    }

    bool Library::libRename(const std::string &oldName, std::string &newName) noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "(" << oldName << "," << newName << ")" << std::endl;
#endif

        return Rename(oldName.c_str(), newName.c_str()) == TRUE;
    }

    std::string Library::libGetCurrentDirName() noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        const unsigned int len = 256;
        char buffer[len];

        if (!GetCurrentDirName(buffer, len))
            return {};
        buffer[len - 1] = '\0';

        return buffer;
    }

    std::vector<std::string> Library::libExAll(const std::string &path, const std::string &pattern /*= ""*/,
                                               const bool files /*= true*/) noexcept
    {
#ifdef TRACE_AMIGAOS
        std::cout << __PRETTY_FUNCTION__ << "(" << path << "," << pattern << ")" << std::endl;
#endif

        std::vector<std::string> result;

        LockScope lockScope(path, false);

        if (lockScope.isValid())
        {
            try
            {
                AOS::Exec::MemScope buffer(16 * 1024);
                DosObjectScope dosObjectScope(DOS_EXALLCONTROL);

                // buffer for possible ParsePatternNoCase()
                // http://amigadev.elowar.com/read/ADCD_2.1/Includes_and_Autodocs_3._guide/node019C.html
                AOS::Exec::MemScope matchBuffer(pattern.empty() ? 0 : pattern.length() * 2 + 2);
                if (!pattern.empty())
                {
                    ParsePatternNoCase((char *)pattern.c_str(), (UBYTE *)matchBuffer.mem(), matchBuffer.size());
                    dosObjectScope.exAllControl()->eac_MatchString = (decltype(ExAllControl::eac_MatchString))matchBuffer.mem();
                }

                ExAll(lockScope.lock(), (struct ExAllData *)buffer.mem(), buffer.size(), ED_TYPE, dosObjectScope.exAllControl());
                if (dosObjectScope.exAllControl()->eac_Entries != 0)
                {
                    for (auto exAllData = (struct ExAllData *)buffer.mem(); exAllData != nullptr; exAllData = exAllData->ed_Next)
                        if ((files && exAllData->ed_Type < 0) || (!files && exAllData->ed_Type >= 0))
                            result.push_back((char *)exAllData->ed_Name);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        return result;
    }

    DosList *Library::libFindDosEntry(const std::string &name, const unsigned long flags) noexcept
    {
        LockDosListScope lockDosListScope(flags | LDF_READ);

        auto lockDosList = lockDosListScope.lockDosList();

        return lockDosList ? FindDosEntry(lockDosList, name.c_str(), flags) : nullptr;
    }

    bool Library::libAssignAdd(const std::string &name, const std::string &path) noexcept
    {
        LockScope lockScope(path, false);
        if (!lockScope.isValid())
            return false;

        auto result = AssignAdd(name.c_str(), lockScope.lock());
        if (result == FALSE)
            return false;

        lockScope.Invalidate();

        return true;
    }

    std::optional<std::string> Library::libGetVar(const std::string &name, const enum AOS::Dos::GVF type) noexcept
    {
        char buffer[256];

        auto result = GetVar(name.c_str(), buffer, sizeof(buffer), (unsigned long)type);
        if (result >= 0)
            return std::optional<std::string>(buffer);

        /// -1 indicates that the variable was not defined

        return std::nullopt;
    }
}

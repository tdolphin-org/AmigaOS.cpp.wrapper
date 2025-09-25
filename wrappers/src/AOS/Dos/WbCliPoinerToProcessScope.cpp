//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "WbCliPoinerToProcessScope.hpp"

#include "AOS/Dos/Library.hpp"
#include <dos/dosextens.h>
#include <proto/exec.h>

namespace AOS::Dos
{
    WbCliPoinerToProcessScope::WbCliPoinerToProcessScope()
    {
        mpProcess = AOS::Dos::Library::FindProcess();
        if (!mpProcess)
            return;

        if (mpProcess->pr_CLI) // not expecting pointer to CommandLineInterface
        {
            mpProcess = nullptr;
            return;
        }

        Forbid();
        auto pWorkbench = AOS::Dos::Library::FindProcess("Workbench");
        if (pWorkbench)
            mpProcess->pr_CLI = pWorkbench->pr_CLI; // copy pointer to CommandLineInterface, will be set back to null on destructor
        Permit();
    }

    WbCliPoinerToProcessScope::~WbCliPoinerToProcessScope()
    {
        if (!mpProcess)
            return;

        mpProcess->pr_CLI = MKBADDR(nullptr);
    }
}

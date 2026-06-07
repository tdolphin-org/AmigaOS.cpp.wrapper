//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <libraries/asl.h>

namespace AOS::ASL
{
    struct Library
    {
        /// @brief calls asl:AllocFileRequest()
        static struct FileRequester *libAllocFileRequest();

        /// @brief calls asl:FreeFileRequest()
        static void libFreeFileRequest(struct FileRequester *fileReq);
    };
}

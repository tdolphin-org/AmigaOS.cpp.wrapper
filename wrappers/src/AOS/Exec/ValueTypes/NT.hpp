//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <exec/nodes.h>

namespace AOS::Exec
{
    // node type
    enum class NT_Type : unsigned char
    {
        UNKNOWN = NT_UNKNOWN,
        TASK = NT_TASK,
        INTERRUPT = NT_INTERRUPT,
        DEVICE = NT_DEVICE,
        MSGPORT = NT_MSGPORT,
        MESSAGE = NT_MESSAGE,
        FREEMSG = NT_FREEMSG,
        REPLYMSG = NT_REPLYMSG,
        RESOURCE = NT_RESOURCE,
        LIBRARY = NT_LIBRARY,
        MEMORY = NT_MEMORY,
        SOFTINT = NT_SOFTINT,
        FONT = NT_FONT,
        PROCESS = NT_PROCESS,
        SEMAPHORE = NT_SEMAPHORE,
        SIGNALSEM = NT_SIGNALSEM,
        BOOTNODE = NT_BOOTNODE,
        KICKMEM = NT_KICKMEM,
        GRAPHICS = NT_GRAPHICS,
        DEATHMESSAGE = NT_DEATHMESSAGE,
        USER = NT_USER,
        EXTENDED = NT_EXTENDED,
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <libraries/pcix.h>

namespace AOS::PCIX
{
    enum class BaseClass
    {
        Storage = PCI_BASE_CLASS_STORAGE,
        Network = PCI_BASE_CLASS_NETWORK,
        Display = PCI_BASE_CLASS_DISPLAY,
        Multimedia = PCI_BASE_CLASS_MULTIMEDIA,
        Memory = PCI_BASE_CLASS_MEMORY,
        Bridge = PCI_BASE_CLASS_BRIDGE,
        Communication = PCI_BASE_CLASS_COMMUNICATION,
        System = PCI_BASE_CLASS_SYSTEM,
        Input = PCI_BASE_CLASS_INPUT,
        Docking = PCI_BASE_CLASS_DOCKING,
        Processor = PCI_BASE_CLASS_PROCESSOR,
        Serial = PCI_BASE_CLASS_SERIAL,
    };
}

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <libraries/pcix.h>

namespace AOS::PCIX
{
    enum class SubClass
    {
        NotDefined = PCI_CLASS_NOT_DEFINED,
        NotDefinedVga = PCI_CLASS_NOT_DEFINED_VGA,
        StorageScsi = PCI_CLASS_STORAGE_SCSI,
        StorageIde = PCI_CLASS_STORAGE_IDE,
        StorageFloppy = PCI_CLASS_STORAGE_FLOPPY,
        StorageIpi = PCI_CLASS_STORAGE_IPI,
        StorageRaid = PCI_CLASS_STORAGE_RAID,
        StorageOther = PCI_CLASS_STORAGE_OTHER,
        NetworkEthernet = PCI_CLASS_NETWORK_ETHERNET,
        NetworkTokenRing = PCI_CLASS_NETWORK_TOKEN_RING,
        NetworkFddi = PCI_CLASS_NETWORK_FDDI,
        NetworkAtm = PCI_CLASS_NETWORK_ATM,
        NetworkOther = PCI_CLASS_NETWORK_OTHER,
        DisplayVga = PCI_CLASS_DISPLAY_VGA,
        DisplayXga = PCI_CLASS_DISPLAY_XGA,
        DisplayOther = PCI_CLASS_DISPLAY_OTHER,
        MultimediaVideo = PCI_CLASS_MULTIMEDIA_VIDEO,
        MultimediaAudio = PCI_CLASS_MULTIMEDIA_AUDIO,
        MultimediaOther = PCI_CLASS_MULTIMEDIA_OTHER,
        MemoryRam = PCI_CLASS_MEMORY_RAM,
        MemoryFlash = PCI_CLASS_MEMORY_FLASH,
        MemoryOther = PCI_CLASS_MEMORY_OTHER,
        BridgeHost = PCI_CLASS_BRIDGE_HOST,
        BridgeIsa = PCI_CLASS_BRIDGE_ISA,
        BridgeEisa = PCI_CLASS_BRIDGE_EISA,
        BridgeMc = PCI_CLASS_BRIDGE_MC,
        BridgePci = PCI_CLASS_BRIDGE_PCI,
        BridgePcmcia = PCI_CLASS_BRIDGE_PCMCIA,
        BridgeNubus = PCI_CLASS_BRIDGE_NUBUS,
        BridgeCardbus = PCI_CLASS_BRIDGE_CARDBUS,
        BridgeOther = PCI_CLASS_BRIDGE_OTHER,
        CommunicationSerial = PCI_CLASS_COMMUNICATION_SERIAL,
        CommunicationParallel = PCI_CLASS_COMMUNICATION_PARALLEL,
        CommunicationOther = PCI_CLASS_COMMUNICATION_OTHER,
        SystemPic = PCI_CLASS_SYSTEM_PIC,
        SystemDma = PCI_CLASS_SYSTEM_DMA,
        SystemTimer = PCI_CLASS_SYSTEM_TIMER,
        SystemRtc = PCI_CLASS_SYSTEM_RTC,
        SystemOther = PCI_CLASS_SYSTEM_OTHER,
        InputKeyboard = PCI_CLASS_INPUT_KEYBOARD,
        InputPen = PCI_CLASS_INPUT_PEN,
        InputMouse = PCI_CLASS_INPUT_MOUSE,
        InputOther = PCI_CLASS_INPUT_OTHER,
        DockingGeneric = PCI_CLASS_DOCKING_GENERIC,
        DockingOther = PCI_CLASS_DOCKING_OTHER,
        Processor386 = PCI_CLASS_PROCESSOR_386,
        Processor486 = PCI_CLASS_PROCESSOR_486,
        ProcessorPentium = PCI_CLASS_PROCESSOR_PENTIUM,
        ProcessorAlpha = PCI_CLASS_PROCESSOR_ALPHA,
        ProcessorPowerpc = PCI_CLASS_PROCESSOR_POWERPC,
        ProcessorCo = PCI_CLASS_PROCESSOR_CO,
        SerialFirewire = PCI_CLASS_SERIAL_FIREWIRE,
        SerialAccess = PCI_CLASS_SERIAL_ACCESS,
        SerialSsa = PCI_CLASS_SERIAL_SSA,
        SerialUsb = PCI_CLASS_SERIAL_USB,
        SerialFiber = PCI_CLASS_SERIAL_FIBER,
        Others = PCI_CLASS_OTHERS,
    };
}

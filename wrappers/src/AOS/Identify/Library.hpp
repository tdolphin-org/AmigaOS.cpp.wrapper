//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "ValueTypes/ClassID.hpp"
#include "ValueTypes/IDCPU.hpp"
#include "ValueTypes/IDFPU.hpp"
#include "ValueTypes/IDGOS.hpp"
#include "ValueTypes/IDHW.hpp"
#include "ValueTypes/IDMMU.hpp"
#include "ValueTypes/IDPPC.hpp"

#include <libraries/configvars.h>
#include <string>
#include <vector>

namespace AOS::Identify
{
    enum class CpuType
    {
        MC68k,
        PowerPC,
    };

    struct CpuInfo
    {
        CpuType type;
        union
        {
            enum IDCPU m68k;
            enum IDPPC ppc;
        } model;
        std::string modelName;
        std::string revision;
        std::string clock;
        std::vector<std::string> additionalUnits;
    };

    struct Expansion
    {
        ConfigDev *configDev;
        uint16_t manufacturerId;
        std::string manufacturerName;
        uint8_t productId;
        std::string productName;
        std::string productClass;
        std::vector<std::string> additionalInfo;
    };

    struct PciExpansion
    {
        uint16_t manufacturerId;
        std::string manufacturerName;
        uint16_t productId;
        std::string productName;
        std::string productClass;
        std::vector<std::string> additionalInfo;
    };

    enum class PciExpansionsResultCode
    {
        Success = IDERR_OKAY,
        NoPciLib = IDERR_NOPCILIB, // No openpci.library or PCI bridge found
        NoPciDb = IDERR_NOPCIDB, // No PCI database file found
        BadPciDb = IDERR_BADPCIDB, // Bad PCI database file
        Missing45 = -127, // identify.library version < 45
        UnknownError = -128, // Any other error
    };

    struct Library
    {
        /// @brief get opened identify.library version
        /// @return version as a string, e.g. "45.0"
        static std::string GetVersion() noexcept;

        static std::vector<CpuInfo> GetAllCPUs();

        static enum IDCPU GetCPU() noexcept;
        static enum IDFPU GetFPU() noexcept;
        static enum IDMMU GetMMU() noexcept;
        static enum IDPPC GetPowerPC() noexcept;
        static enum IDGOS GetGraphicOS() noexcept;

        static std::vector<Expansion> GetExpansions(const enum ClassID filterByClassId = ClassID::NONE) noexcept;
        static std::pair<PciExpansionsResultCode, std::vector<PciExpansion>> GetPciExpansions() noexcept;

        /// @brief identify:IdHardware()
        static std::string libIdHardware(const enum IDHW idhw) noexcept;

        /// @brief identify:IdHardwareNum()
        static uint32_t libIdHardwareNum(const enum IDHW idhw) noexcept;
    };
}

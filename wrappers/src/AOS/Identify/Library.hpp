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
        unsigned short manufacturerId;
        std::string manufacturer;
        unsigned char productId;
        std::string product;
        std::string productClass;
        std::vector<std::string> additionalInfo;
    };

    struct Library
    {
        static std::vector<CpuInfo> GetAllCPUs();

        static enum IDCPU GetCPU() noexcept;
        static enum IDFPU GetFPU() noexcept;
        static enum IDMMU GetMMU() noexcept;
        static enum IDPPC GetPowerPC() noexcept;
        static enum IDGOS GetGraphicOS() noexcept;

        static std::vector<Expansion> GetExpansions(const enum ClassID filterByClassId = ClassID::NONE) noexcept;

        /// @brief identify:IdHardware()
        static std::string libIdHardware(const enum IDHW idhw) noexcept;

        /// @brief identify:IdHardwareNum()
        static unsigned long libIdHardwareNum(const enum IDHW idhw) noexcept;
    };
}

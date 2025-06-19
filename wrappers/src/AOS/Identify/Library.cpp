//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Library.hpp"

#include <libraries/identify.h>
#include <libraries/openpci.h>
#include <proto/identify.h>
#include <set>

#include <iostream>
#include <sstream>

extern struct Library *IdentifyBase;

namespace AOS::Identify
{
    std::string Library::GetVersion() noexcept
    {
        std::stringstream versionStream;
        versionStream << IdentifyBase->lib_Version << "." << IdentifyBase->lib_Revision;
        return versionStream.str();
    }

    std::vector<CpuInfo> Library::GetAllCPUs()
    {
        return { CpuInfo { CpuType::MC68k,
                           { .m68k = GetCPU() },
                           IdHardware(IDHW_CPU, nullptr),
                           IdHardware(IDHW_CPUREV, nullptr),
                           IdHardware(IDHW_CPUCLOCK, nullptr),
                           {
                               std::string("FPU:") + IdHardware(IDHW_FPU, nullptr) +
                                   []() {
                                       std::string fpuClock = IdHardware(IDHW_FPUCLOCK, nullptr);
                                       return fpuClock == "N/A" ? "" : "@" + fpuClock;
                                   }(),
                               std::string("MMU:") + IdHardware(IDHW_MMU, nullptr),
                           } },
                 CpuInfo {
                     CpuType::PowerPC,
                     { .ppc = GetPowerPC() },
                     IdHardware(IDHW_POWERPC, nullptr),
                     "",
                     IdHardware(IDHW_PPCCLOCK, nullptr),
                     {},
                 } };
    }

    IDCPU Library::GetCPU() noexcept
    {
        return static_cast<IDCPU>(IdHardwareNum(IDHW_CPU, nullptr));
    }

    IDFPU Library::GetFPU() noexcept
    {
        return static_cast<IDFPU>(IdHardwareNum(IDHW_FPU, nullptr));
    }

    IDMMU Library::GetMMU() noexcept
    {
        return static_cast<IDMMU>(IdHardwareNum(IDHW_MMU, nullptr));
    }

    IDPPC Library::GetPowerPC() noexcept
    {
        return static_cast<IDPPC>(IdHardwareNum(IDHW_POWERPC, nullptr));
    }

    IDGOS Library::GetGraphicOS() noexcept
    {
        return static_cast<IDGOS>(IdHardwareNum(IDHW_GFXSYS, nullptr));
    }

    std::vector<Expansion> Library::GetExpansions(const enum ClassID filterByClassId /*= ClassID::NONE*/) noexcept
    {
        std::vector<Expansion> expansions;

        std::set<int> ramClassIds { IDCID_TURBORAM, IDCID_GFXRAM, IDCID_HDRAM, IDCID_IDEHDRAM,   IDCID_RAMSCSIHD,
                                    IDCID_RAM,      IDCID_RAMFPU, IDCID_RAM32, IDCID_TURBOANDRAM };

        ConfigDev *pConfigDev = nullptr;

        char manufacturerName[IDENTIFYBUFLEN] = {}, productName[IDENTIFYBUFLEN] = {}, productClass[IDENTIFYBUFLEN] = {};
        uint16_t manufacturerId = 0;
        uint8_t productId = 0;
        uint32_t classId = 0;

        while (IdExpansionTags(IDTAG_ManufStr, (uint32_t)manufacturerName, IDTAG_ProdStr, (uint32_t)productName, IDTAG_ClassStr,
                               (uint32_t)productClass, IDTAG_ClassID, (uint32_t)&classId, IDTAG_Expansion, (uint32_t)&pConfigDev, TAG_DONE)
               == IDERR_OKAY)
        {
            std::vector<std::string> additionalInfo;
            if (pConfigDev != nullptr)
            {
                if (filterByClassId != ClassID::NONE && classId != (uint32_t)filterByClassId)
                    continue;

                manufacturerId = pConfigDev->cd_Rom.er_Manufacturer;
                productId = pConfigDev->cd_Rom.er_Product;
                std::string memoryValue = "slot size: ";

                if (pConfigDev->cd_BoardSize % (1024 * 1024) == 0)
                    memoryValue += std::to_string(pConfigDev->cd_BoardSize / (1024 * 1024)) + " MB";
                else if (pConfigDev->cd_BoardSize % 1024 == 0)
                    memoryValue += std::to_string(pConfigDev->cd_BoardSize / 1024) + " KB";
                else
                    memoryValue += std::to_string(pConfigDev->cd_BoardSize) + " Bytes";

                additionalInfo.push_back(memoryValue);

                uint32_t serialNumber = pConfigDev->cd_Rom.er_SerialNumber;
                if (serialNumber != 0)
                    additionalInfo.push_back(std::string("SN: " + std::to_string(serialNumber)));

                struct ::Library *pDriver = (struct ::Library *)pConfigDev->cd_Driver;
                if (pDriver != nullptr)
                    additionalInfo.push_back(pDriver->lib_Node.ln_Name);
            }
            else
            {
                manufacturerId = 0;
                productId = 0;
            }

            expansions.push_back({
                pConfigDev,
                manufacturerId,
                manufacturerName,
                productId,
                productName,
                productClass,
                additionalInfo,
            });
        }

        return expansions;
    }

    std::pair<PciExpansionsResultCode, std::vector<PciExpansion>> Library::GetPciExpansions() noexcept
    {
        if (IdentifyBase->lib_Version < 45U) // Check if identify.library version is at least 45
            return { PciExpansionsResultCode::Missing45, {} };

        std::vector<PciExpansion> pciExpansions;
        PciExpansionsResultCode resultCode = PciExpansionsResultCode::Success;

        struct pci_dev *pPciDev = nullptr;
        char manufacturerName[IDENTIFYBUFLEN] = {}, productName[IDENTIFYBUFLEN] = {}, productClass[IDENTIFYBUFLEN] = {};

        while (true)
        {
            auto result = IdPciExpansionTags(IDTAG_ManufStr, (uint32_t)manufacturerName, IDTAG_ProdStr, (uint32_t)productName,
                                             IDTAG_ClassStr, (uint32_t)productClass, IDTAG_Expansion, (uint32_t)&pPciDev, TAG_DONE);

            if (result != IDERR_OKAY)
            {
                switch (result)
                {
                    case IDERR_NOPCIDB:
                        resultCode = PciExpansionsResultCode::NoPciDb;
                        break;
                    case IDERR_BADPCIDB:
                        resultCode = PciExpansionsResultCode::BadPciDb;
                        break;
                    case IDERR_NOPCILIB:
                        resultCode = PciExpansionsResultCode::NoPciLib;
                        break;
                    case IDERR_DONE:
                        break;
                    default:
                        std::cerr << "GetPciExpansions: Error retrieving PCI expansion: " << result << std::endl;
                        resultCode = PciExpansionsResultCode::UnknownError;
                }
                break;
            }

            pciExpansions.push_back({
                pPciDev->vendor,
                manufacturerName,
                pPciDev->device,
                productName,
                productClass,
            });
        }

        return { resultCode, pciExpansions };
    }

    std::string Library::libIdHardware(const enum IDHW idhw) noexcept
    {
        return IdHardware((ULONG)idhw, nullptr);
    }

    uint32_t Library::libIdHardwareNum(const enum IDHW idhw) noexcept
    {
        return IdHardwareNum((ULONG)idhw, nullptr);
    }
}

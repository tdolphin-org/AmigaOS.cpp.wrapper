//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include "ValueTypes/MEMF.hpp"
#include "ValueTypes/NT.hpp"
#include "ValueTypes/SYSTEMINFOTYPE.hpp"

#ifdef __MORPHOS__
#include <optional>
#include <variant>
#endif

#include <exec/ports.h>
#include <exec/resident.h>
#include <string>
#include <vector>

namespace AOS::Exec
{
    struct NodeInfo
    {
        std::string name;
        std::string version;
        NT_Type type;
    };

#ifdef __MORPHOS__
    struct CPUInfo
    {
        unsigned long index;
        std::string family;
        std::string name;
        unsigned long version;
        unsigned long revision;
        unsigned long long clock;
        unsigned long long busClock;
        unsigned long l1InstructionCache; // level 1 instruction cache
        unsigned long l1DataCache; // level 1 data cache
        unsigned long l2InstructionCache; // level 2 instruction cache
        unsigned long l2DataCache; // level 2 data cache
        unsigned long l3InstructionCache; // level 3 instruction cache
        unsigned long l3DataCache; // level 3 data cache
        bool hasFPU;
        bool hasAltivec;
        bool hasPerformanceMeasurement;
        bool hasDataStream;
    };
#endif

    struct Library
    {
        static std::string GetVersion() noexcept;

        /// @brief calls exec:FindTask(NULL) and return ptr
        static std::string CurrentTaskPid();

        /// @brief return list of all loaded nodes of libraries (also datatypes, etc)
        static std::vector<NodeInfo> GetAllLibraryNodeNames() noexcept;
        /// @brief return list of all loaded nodes of devices
        static std::vector<NodeInfo> GetAllDeviceNodeNames() noexcept;

        /// @brief exec/Forbid()
        static void libForbid() noexcept;
        /// @brief exec/Permit()
        static void libPermit() noexcept;

        /// @brief exec/FindTask(NULL) and return ptr to struct Task
        static struct Task *libFindTask() noexcept;
        /// @brief exec/FindTask(name) and return ptr to struct Task
        static struct Task *libFindTask(const std::string &name) noexcept;

        /// @brief exec/AvailMem(name) and returns the amount of free memory given certain attributes
        static unsigned long libAvailMem(const enum MEMF_Type type, const enum MEMF_Avail avail) noexcept;

        /// @brief exec/CopyMem(source, dest, size) --
        ///        CopyMem is a general purpose, fast memory copy function. It can
        ///        deal with arbitrary lengths, with its pointers on arbitrary
        ///        alignments. It attempts to optimize larger copies with more
        ///        efficient copies, it uses byte copies for small moves, parts of
        ///        larger copies, or the entire copy if the source and destination are
        ///        misaligned with respect to each other.
        ///        Arbitrary overlapping copies are not supported.
        /// @param source a pointer to the source data region
        /// @param dest a pointer to the destination data region
        /// @param size the size (in bytes) of the memory area. Zero copies zero bytes
        static void libCopyMem(void *const source, void *dest, uint32_t size) noexcept;

        /// @brief exec/CopyMemQuick - optimized memory copy function --
        ///        CopyMemQuick is a highly optimized memory copy function, with
        ///        restrictions on the size and alignment of its arguments. Both the
        ///        source and destination pointers must be longword aligned.  In
        ///        addition, the size must be an integral number of longwords (e.g.
        ///        the size must be evenly divisible by four).
        ///        Arbitrary overlapping copies are not supported.
        /// @param source a pointer to the source data region, long aligned
        /// @param dest a pointer to the destination data region, long aligned
        /// @param size the size (in bytes) of the memory area. Zero copies zero bytes
        static void libCopyMemQuick(uint32_t *source, uint32_t *dest, uint32_t size) noexcept;

        /// @brief exec/FindResident(name) and return ptr to struct Resident
        static struct Resident *libFindResident(const std::string &name) noexcept;

        /// @brief exec/FindPort(name) and return ptr to struct Port
        static struct MsgPort *libFindPort(const std::string &name) noexcept;

        /// @brief exec/PutMsg(port)
        static void libPutMsg(struct MsgPort &port, struct Message &message) noexcept;
        /// @brief exec/GetMsg(port)
        static struct Message *libGetMsg(struct MsgPort &port) noexcept;
        /// @brief exec/WaitPort(port)
        static struct Message *libWaitPort(struct MsgPort &port) noexcept;

#ifdef __MORPHOS__
        static std::vector<CPUInfo> GetAllCPUs() noexcept;

        static std::variant<std::string, unsigned long, unsigned long long, bool>
        libNewGetSystemAttrs(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx = std::nullopt);

        static std::string libNewGetSystemAttrsAsString(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx = std::nullopt);
        static bool libNewGetSystemAttrsAsBool(const enum SYSTEMINFOTYPE type, std::optional<unsigned long> cpuIdx = std::nullopt);
        static unsigned long libNewGetSystemAttrsAsUnsignedLong(const enum SYSTEMINFOTYPE type,
                                                                std::optional<unsigned long> cpuIdx = std::nullopt);
        static unsigned long long libNewGetSystemAttrsAsUnsignedLongLong(const enum SYSTEMINFOTYPE type,
                                                                         std::optional<unsigned long> cpuIdx = std::nullopt);
#endif
    };
}

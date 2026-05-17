//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "ToString.hpp"

#include <cstdio>
#include <iomanip>
#include <numeric>
#include <type_traits>

#ifdef Format
#undef Format
#endif

std::string ToString::FromDataPointer(const void *value)
{
    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "0x%08lx", reinterpret_cast<unsigned long>(value));

    return std::string(buffer);
}

std::string ToString::FromHexValue(const unsigned long value)
{
    char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "0x%lx", value);
    return std::string(buffer);
}

std::string ToString::Concatenate(const std::vector<std::string> &array, const std::string &separator)
{
    return array.size() == 1
        ? array[0]
        : std::accumulate(array.begin(), array.end(), std::string(""),
                          [&separator](const std::string &a, const std::string &b) { return a.empty() ? b : a + separator + b; });
}

std::string ToString::FromBytesValue(const unsigned long value, const MemorySizeUnit unit, const bool ceiling)
{
    if (unit == MemorySizeUnit::AutoRound)
    {
        if (value % (1024 * 1024) == 0)
            return std::to_string(value / (1024 * 1024)) + " MB";
        else if (value % 1024 == 0)
            return std::to_string(value / 1024) + " KB";
    }
    else if (unit == MemorySizeUnit::GigaBytes)
    {
        if (ceiling)
            return std::to_string((value + (1024 * 1024 * 1024) - 1) / (1024 * 1024 * 1024)) + " GB";
        return (value % (1024 * 1024 * 1024) == 0 ? "" : "~") + std::to_string(value / (1024 * 1024 * 1024)) + " GB";
    }
    else if (unit == MemorySizeUnit::MegaBytes)
    {
        if (ceiling)
            return std::to_string((value + (1024 * 1024) - 1) / (1024 * 1024)) + " MB";
        return (value % (1024 * 1024) == 0 ? "" : "~") + std::to_string(value / (1024 * 1024)) + " MB";
    }
    else if (unit == MemorySizeUnit::KiloBytes)
    {
        if (ceiling)
            return std::to_string((value + 1024 - 1) / 1024) + " KB";
        return (value % 1024 == 0 ? "" : "~") + std::to_string(value / 1024) + " KB";
    }

    return std::to_string(value) + " Bytes";
}

std::string ToString::FromClockHertzValue(const unsigned long long value, const bool useSI, const bool asInteger)
{
    if (!useSI)
    {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%llu Hz", (unsigned long long)value);
        return std::string(buffer);
    }

    char buffer[64];
    if (value >= 1'000'000'000)
        std::snprintf(buffer, sizeof(buffer), "%llu%s GHz", (unsigned long long)(value / 1'000'000'000),
                      asInteger ? "" : FormatFraction((value % 1'000'000'000) / 1'000'000, 3).c_str());
    else if (value >= 1'000'000)
        std::snprintf(buffer, sizeof(buffer), "%llu%s MHz", (unsigned long long)(value / 1'000'000),
                      asInteger ? "" : FormatFraction((value % 1'000'000) / 1'000, 3).c_str());
    else if (value >= 1'000)
        std::snprintf(buffer, sizeof(buffer), "%llu%s kHz", (unsigned long long)(value / 1'000),
                      asInteger ? "" : FormatFraction((value % 1'000) / 1, 3).c_str());
    else
        std::snprintf(buffer, sizeof(buffer), "%llu Hz", (unsigned long long)value);

    return std::string(buffer);
}

std::string ToString::FromSIValue(const unsigned long long value, const std::string &unit, const bool asInteger)
{
    char buffer[64];
    if (value >= 1'000'000'000)
        std::snprintf(buffer, sizeof(buffer), "%llu%s G%s", (unsigned long long)(value / 1'000'000'000),
                      asInteger ? "" : FormatFraction((value % 1'000'000'000) / 1'000'000, 3).c_str(), unit.c_str());
    else if (value >= 1'000'000)
        std::snprintf(buffer, sizeof(buffer), "%llu%s M%s", (unsigned long long)(value / 1'000'000),
                      asInteger ? "" : FormatFraction((value % 1'000'000) / 1'000, 3).c_str(), unit.c_str());
    else if (value >= 1'000)
        std::snprintf(buffer, sizeof(buffer), "%llu%s k%s", (unsigned long long)(value / 1'000),
                      asInteger ? "" : FormatFraction((value % 1'000) / 1, 3).c_str(), unit.c_str());
    else
        std::snprintf(buffer, sizeof(buffer), "%llu%s", (unsigned long long)value, unit.c_str());

    return std::string(buffer);
}

std::string ToString::Replace(std::string input, const std::string &source, const std::string &replacement)
{
    std::size_t pos = 0;
    while ((pos = input.find(source, pos)) != std::string::npos)
    {
        input.replace(pos, source.size(), replacement);
        pos += replacement.size();
    }

    return input;
}

std::string ToString::Format(std::string format, const std::string &arg0)
{
    try
    {
        return format.replace(format.find("{}"), 2, arg0);
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::Format(std::string format, const std::vector<std::string> &args0)
{
    try
    {
        auto arg0 = args0.size() == 1 ? args0[0]
                                      : std::accumulate(args0.begin(), args0.end(), std::string(""),
                                                        [](const std::string &a, const std::string &b) { return a + " " + b; });
        return format.replace(format.find("{}"), 2, arg0);
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::Format(std::string format, const std::string &arg0, const std::string &arg1)
{
    try
    {
        format.replace(format.find("{}"), 2, arg0);
        format.replace(format.find("{}"), 2, arg1);
        return format;
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0,arg1)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::Format(std::string format, const std::string &arg0, const std::vector<std::string> &args1)
{
    try
    {
        format.replace(format.find("{}"), 2, arg0);
        format.replace(format.find("{}"), 2, Concatenate(args1, " "));
        return format;
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0,arg1)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::Format(std::string format, const std::vector<std::string> &args0, const std::vector<std::string> &args1)
{
    try
    {
        format.replace(format.find("{}"), 2, Concatenate(args0, " "));
        format.replace(format.find("{}"), 2, Concatenate(args1, " "));
        return format;
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0,arg1)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::Format(std::string format, const std::string &arg0, const std::string &arg1, const std::string &arg2)
{
    try
    {
        format.replace(format.find("{}"), 2, arg0);
        format.replace(format.find("{}"), 2, arg1);
        format.replace(format.find("{}"), 2, arg2);
        return format;
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0,arg1,arg2)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::Format(std::string format, const std::string &arg0, const std::string &arg1, const std::string &arg2,
                             const std::string &arg3)
{
    try
    {
        format.replace(format.find("{}"), 2, arg0);
        format.replace(format.find("{}"), 2, arg1);
        format.replace(format.find("{}"), 2, arg2);
        format.replace(format.find("{}"), 2, arg3);
        return format;
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0,arg1,arg2,arg3)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::Format(std::string format, const std::string &arg0, const std::string &arg1, const std::string &arg2,
                             const std::string &arg3, const std::string &arg4)
{
    try
    {
        format.replace(format.find("{}"), 2, arg0);
        format.replace(format.find("{}"), 2, arg1);
        format.replace(format.find("{}"), 2, arg2);
        format.replace(format.find("{}"), 2, arg3);
        format.replace(format.find("{}"), 2, arg4);
        return format;
    }
    catch (...)
    {
        std::fprintf(stderr, "exception on std::format(arg0,arg1,arg2,arg3,arg4)=%s\n", format.c_str());
        return format;
    }
}

std::string ToString::FormatFraction(const unsigned long long fraction, const int width)
{
    if (fraction == 0)
        return "";

    std::string frac = std::to_string(fraction);
    while (frac.size() < (std::size_t)width)
        frac = "0" + frac;

    while (!frac.empty() && frac.back() == '0')
        frac.pop_back();

    return frac.empty() ? "" : "." + frac;
}

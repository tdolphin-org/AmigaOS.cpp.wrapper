//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <string>
#include <vector>

enum class MemorySizeUnit
{
    AutoRound, // auto units, only when value can be rounded, e.g. 1536 Bytes, 1048576 Bytes, 100 KB, 2 MB, etc
    Bytes,
    KiloBytes, // value is cut to KB without decimal places
    MegaBytes, // value is cut to MB without decimal places
    GigaBytes  // value is cut to GB without decimal places
};

class ToString
{
  public:
    static std::string FromDataPointer(const void *value);
    static std::string FromHexValue(const unsigned long value);
    static std::string Concatenate(const std::vector<std::string> &array, const std::string &separator);
    static std::string FromBytesValue(const unsigned long value, const MemorySizeUnit unit = MemorySizeUnit::AutoRound, const bool ceiling = false);

    /// @brief Converts a clock frequency value to a string representation.
    /// @param value The clock frequency value in Hertz.
    /// @param useSI Whether to use SI units (e.g., kHz, MHz) or not.
    /// @return The string representation of the clock frequency value.
    static std::string FromClockHertzValue(const unsigned long long value, const bool useSI = false, const bool asInteger = false);

    /// @brief Converts a value to a string representation using SI prefixes (e.g., k, M, G).
    /// @param value The value to convert.
    /// @param asInteger Whether to format the value as an integer (no decimal places).
    /// @return The string representation of the value with SI prefixes.
    static std::string FromSIValue(const unsigned long long value, const std::string &unit, const bool asInteger = false);

    static std::string Replace(std::string input, const std::string &source, const std::string &replacement);

    // below methods could be removed if C++20 would be used with std::format
    static std::string Format(std::string format, const std::string &arg0);
    static std::string Format(std::string format, const std::vector<std::string> &args0);
    static std::string Format(std::string format, const std::string &arg0, const std::string &arg1);
    static std::string Format(std::string format, const std::string &arg0, const std::vector<std::string> &args1);
    static std::string Format(std::string format, const std::vector<std::string> &args0, const std::vector<std::string> &args1);
    static std::string Format(std::string format, const std::string &arg0, const std::string &arg1, const std::string &arg2);
    static std::string Format(std::string format, const std::string &arg0, const std::string &arg1, const std::string &arg2,
                              const std::string &arg3);
    static std::string Format(std::string format, const std::string &arg0, const std::string &arg1, const std::string &arg2,
                              const std::string &arg3, const std::string &arg4);

  private:
    /// @brief Formats the fractional part of a clock frequency value (adds leading zeros).
    /// @param fraction The fractional part of the clock frequency.
    /// @param width The width of the formatted string.
    /// @return The formatted string representation of the fractional part.
    static std::string FormatFraction(const unsigned long long fraction, const int width);
};

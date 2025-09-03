//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <string>
#include <vector>

class ToString
{
  public:
    static std::string FromDataPointer(const void *value);
    static std::string FromHexValue(const unsigned long value);
    static std::string Concatenate(const std::vector<std::string> &array, const std::string &separator);
    static std::string FromBytesValue(const unsigned long value);

    /// @brief Converts a clock frequency value to a string representation.
    /// @param value The clock frequency value in Hertz.
    /// @param useSI Whether to use SI units (e.g., kHz, MHz) or not.
    /// @return The string representation of the clock frequency value.
    static std::string FromClockHertzValue(const unsigned long long value, const bool useSI = false);

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
    static std::string FormatFraction(const unsigned long long fraction, const int width);
};

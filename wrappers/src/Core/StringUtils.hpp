//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#pragma once

#include <chrono>
#include <string>
#include <vector>

#undef ToLower

class StringUtils
{
  public:
    /// @brief trim from start (in place)
    static void LTrim(std::string &str);
    /// @brief trim from end (in place)
    static void RTrim(std::string &str);
    /// @brief trim from both ends (in place)
    ///        characters to trim are: space (0x20, ' '), form feed (0x0c, '\f'), line feed (0x0a, '\n'), carriage return (0x0d, '\r'),
    ///        horizontal tab (0x09, '\t'), vertical tab (0x0b, '\v')
    /// @note https://en.cppreference.com/w/cpp/string/byte/isspace.html
    /// @return reference to the same string (trimmed)
    static std::string &Trim(std::string &str);
    /// @brief trim from both ends and check if is empty
    static bool isEmpty(const std::string &str);
    /// @brief check if given string has prefix
    static bool hasPrefix(const std::string &str, const std::string &prefix);
    /// @brief check if given string has at least on of prefixes
    static bool hasPrefix(const std::string &str, const std::initializer_list<std::string> &prefixes);
    /// @brief check if given string has at least on of prefixes
    static bool hasPrefix(const std::string &str, const std::vector<std::string> &prefixes);
    /// @brief check if given string has suffix
    static bool hasSuffix(const std::string &str, const std::string &suffix);
    /// @brief check if given string (trim before check) has suffix
    static bool hasSuffixTrimmed(std::string str, const std::string &suffix);
    /// @brief check if given string has at least on of suffixes
    static bool hasSuffix(const std::string &str, const std::initializer_list<std::string> &suffixes);
    /// @brief check if given string (trim before check) has at least on of suffixes
    static bool hasSuffixTrimmed(std::string str, const std::initializer_list<std::string> &suffixes);
    /// @brief split string into separate lines
    static std::vector<std::string> Split(const std::string &str);
    /// @brief escape string (" -> \")
    static std::string Escape(const std::string &str);
    /// @brief to lower string (AabB -> aabb)
    static std::string ToLower(const std::string &str);
    /// @brief to lower string (AabB -> aabb)
    static std::string HumanReadableTimeDifference(const std::chrono::system_clock::time_point &past);

    /// constexpr methods

    /// @brief can calculate string (char *) length in compilation time
    static constexpr std::size_t strlen_constexpr(const char *str)
    {
        return *str ? 1 + strlen_constexpr(str + 1) : 0;
    }
};

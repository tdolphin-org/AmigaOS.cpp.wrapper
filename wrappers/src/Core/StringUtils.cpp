//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "StringUtils.hpp"

#include <algorithm>
#include <sstream>

void StringUtils::LTrim(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

void StringUtils::RTrim(std::string &str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
}

std::string &StringUtils::Trim(std::string &str)
{
    RTrim(str);
    LTrim(str);
    return str;
}

bool StringUtils::isEmpty(const std::string &str)
{
    if (str.empty())
        return true;

    for (char ch : str)
        if (!std::isspace(static_cast<unsigned char>(ch)))
            return false;

    return true;
}

bool StringUtils::hasPrefix(const std::string &str, const std::string &prefix)
{
    if (str.empty() || prefix.empty())
        return false;
    if (str.length() < prefix.length())
        return false;

    return str.compare(0, prefix.length(), prefix) == 0;
}

bool StringUtils::hasPrefix(const std::string &str, const std::initializer_list<std::string> &prefixes)
{
    if (str.empty())
        return false;

    for (const auto &prefix : prefixes)
        if (hasPrefix(str, prefix))
            return true;

    return false;
}

bool StringUtils::hasPrefix(const std::string &str, const std::vector<std::string> &prefixes)
{
    if (str.empty())
        return false;

    for (const auto &prefix : prefixes)
        if (hasPrefix(str, prefix))
            return true;

    return false;
}

bool StringUtils::hasSuffix(const std::string &str, const std::string &suffix)
{
    if (str.empty() || suffix.empty())
        return false;

    if (str.length() < suffix.length())
        return false;

    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

bool StringUtils::hasSuffixTrimmed(std::string str, const std::string &suffix)
{
    if (str.empty())
        return false;

    Trim(str);

    return hasSuffix(str, suffix);
}

bool StringUtils::hasSuffix(const std::string &str, const std::initializer_list<std::string> &suffixes)
{
    if (str.empty())
        return false;

    for (const auto &suffix : suffixes)
        if (hasSuffix(str, suffix))
            return true;

    return false;
}

bool StringUtils::hasSuffixTrimmed(std::string str, const std::initializer_list<std::string> &suffixes)
{
    if (str.empty())
        return false;

    Trim(str);

    for (auto suffix : suffixes)
        if (hasSuffix(str, suffix))
            return true;

    return false;
}

std::vector<std::string> StringUtils::Split(const std::string &str)
{
    std::istringstream stream(str);
    std::string line;
    std::vector<std::string> result;

    while (std::getline(stream, line))
        result.push_back(line);

    return result;
}

std::string StringUtils::Escape(const std::string &str)
{
    auto s = str;
    // std::replace_if(
    //     s.begin(), s.end(), [](char c) { return c == '"'; }, "\"");
    // return s;

    std::string escaped = "\\\"";

    size_t pos = 0;
    while ((pos = s.find('"', pos)) != std::string::npos)
    {
        s.replace(pos, 1, escaped);
        pos += escaped.length();
    }

    return s;
}

std::string StringUtils::ToLower(const std::string &str)
{
    auto result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string StringUtils::HumanReadableTimeDifference(const std::chrono::system_clock::time_point &past)
{
    auto now = std::chrono::system_clock::now();
    auto diff = now - past;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(diff).count();
    auto hours = std::chrono::duration_cast<std::chrono::hours>(diff).count();

    std::ostringstream oss;
    if (hours > 0)
    {
        oss << hours << " hour" << (hours > 1 ? "s" : "");
    }
    else if (minutes > 0)
    {
        oss << minutes << " minute" << (minutes > 1 ? "s" : "");
    }
    else
    {
        oss << seconds << " second" << (seconds > 1 ? "s" : "");
    }

    oss << " ago";

    return oss.str();
}

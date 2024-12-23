//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
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
};

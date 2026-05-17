//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#pragma once

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <string>

namespace amiga_std_light
{
    class basic_stringstream
    {
      public:
        enum class NumberBase
        {
            Dec = 10,
            Hex = 16,
            Oct = 8
        };

      private:
        std::string buffer_;
        size_t read_pos_ = 0;
        NumberBase number_base_ = NumberBase::Dec;
        char fill_char_ = ' ';
        size_t field_width_ = 0;
        int float_precision_ = 6;
        bool float_fixed_ = false;

        void skip_whitespace();
        bool read_token(std::string &token);
        void append_with_field_width(std::string &target, const std::string &text);

      public:
        basic_stringstream() = default;
        explicit basic_stringstream(const std::string &str)
          : buffer_(str)
        {
        }

        void clear();

        std::string str() const
        {
            return buffer_;
        }

        void str(const std::string &value)
        {
            buffer_ = value;
            read_pos_ = 0;
        }

        bool eof() const
        {
            return read_pos_ >= buffer_.size();
        }

        size_t tellg() const
        {
            return read_pos_;
        }

        void seekg(size_t pos)
        {
            read_pos_ = (pos <= buffer_.size()) ? pos : buffer_.size();
        }

        void set_base(NumberBase base)
        {
            number_base_ = base;
        }

        NumberBase get_base() const
        {
            return number_base_;
        }

        basic_stringstream &operator<<(const char *str);
        basic_stringstream &operator<<(const std::string &str);
        basic_stringstream &operator<<(char c);
        basic_stringstream &operator<<(int8_t value);
        basic_stringstream &operator<<(uint8_t value);
        basic_stringstream &operator<<(int16_t value);
        basic_stringstream &operator<<(uint16_t value);
        basic_stringstream &operator<<(int32_t value);
        basic_stringstream &operator<<(uint32_t value);
        basic_stringstream &operator<<(long value);
        basic_stringstream &operator<<(unsigned long value);
        basic_stringstream &operator<<(int64_t value);
        basic_stringstream &operator<<(uint64_t value);
        basic_stringstream &operator<<(float value);
        basic_stringstream &operator<<(double value);
        basic_stringstream &operator<<(bool value);
        basic_stringstream &operator<<(const void *ptr);
        basic_stringstream &operator<<(std::ios_base &(*manipulator)(std::ios_base &));
        basic_stringstream &operator<<(const std::_Setfill<char> &manipulator);
        basic_stringstream &operator<<(const std::_Setw &manipulator);
        basic_stringstream &operator<<(const std::_Setprecision &manipulator);

        basic_stringstream &operator<<(basic_stringstream &(*manipulator)(basic_stringstream &));

        basic_stringstream &operator>>(std::string &value);
        basic_stringstream &operator>>(char &value);
        basic_stringstream &operator>>(int8_t &value);
        basic_stringstream &operator>>(uint8_t &value);
        basic_stringstream &operator>>(int16_t &value);
        basic_stringstream &operator>>(uint16_t &value);
        basic_stringstream &operator>>(int32_t &value);
        basic_stringstream &operator>>(uint32_t &value);
        basic_stringstream &operator>>(int64_t &value);
        basic_stringstream &operator>>(uint64_t &value);
        basic_stringstream &operator>>(float &value);
        basic_stringstream &operator>>(double &value);
        basic_stringstream &operator>>(bool &value);

        basic_stringstream &getline(std::string &value, char delim = '\n');
    };

    using stringstream = basic_stringstream;

    basic_stringstream &endl(basic_stringstream &ss);
    basic_stringstream &flush(basic_stringstream &ss);
    basic_stringstream &hex(basic_stringstream &ss);
    basic_stringstream &dec(basic_stringstream &ss);
    basic_stringstream &oct(basic_stringstream &ss);
    basic_stringstream &getline(basic_stringstream &ss, std::string &value, char delim = '\n');
}

namespace std
{
    inline amiga_std_light::basic_stringstream &getline(amiga_std_light::basic_stringstream &ss, std::string &value, char delim = '\n')
    {
        return amiga_std_light::getline(ss, value, delim);
    }
}

#if defined(AMIGA_STD_LIGHT_INJECT_SSTREAM_IN_STD)
namespace std
{
    using amiga_std_light::basic_stringstream;
    using amiga_std_light::dec;
    using amiga_std_light::endl;
    using amiga_std_light::flush;
    using amiga_std_light::hex;
    using amiga_std_light::oct;
    using amiga_std_light::stringstream;
}
#endif

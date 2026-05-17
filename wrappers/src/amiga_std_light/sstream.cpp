//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "sstream.hpp"

#include <cerrno>
#include <cstdlib>
#include <limits>

namespace amiga_std_light
{
    static bool is_space(char c)
    {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
    }

    static void append_unsigned_base(std::string &out, uint64_t value, int base)
    {
        if (value == 0)
        {
            out.push_back('0');
            return;
        }

        char digits[65];
        int count = 0;
        while (value > 0)
        {
            uint64_t digit = value % static_cast<uint64_t>(base);
            digits[count++] = (digit < 10) ? static_cast<char>('0' + digit) : static_cast<char>('a' + (digit - 10));
            value /= static_cast<uint64_t>(base);
        }

        for (int i = count - 1; i >= 0; --i)
        {
            out.push_back(digits[i]);
        }
    }

    static void append_signed_base(std::string &out, int64_t value, int base)
    {
        if (base == 10)
        {
            if (value < 0)
            {
                out.push_back('-');
                uint64_t positive = static_cast<uint64_t>(-(value + 1)) + 1;
                append_unsigned_base(out, positive, 10);
                return;
            }

            append_unsigned_base(out, static_cast<uint64_t>(value), 10);
            return;
        }

        append_unsigned_base(out, static_cast<uint64_t>(value), base);
    }

    static void append_float(std::string &out, float value)
    {
        if (value == 0.0f)
        {
            out.push_back('0');
            return;
        }

        if (value < 0.0f)
        {
            out.push_back('-');
            value = -value;
        }

        int int_part = static_cast<int>(value);
        float frac_part = value - static_cast<float>(int_part);

        append_unsigned_base(out, static_cast<uint64_t>(int_part), 10);

        if (frac_part > 0.0001f)
        {
            out.push_back('.');

            for (int i = 0; i < 6 && frac_part > 0.0001f; ++i)
            {
                frac_part *= 10.0f;
                int digit = static_cast<int>(frac_part);
                out.push_back(static_cast<char>('0' + digit));
                frac_part -= static_cast<float>(digit);
            }
        }
    }

    static bool parse_signed(const std::string &token, int base, int64_t &value)
    {
        errno = 0;
        char *end_ptr = nullptr;
        long long parsed = std::strtoll(token.c_str(), &end_ptr, base);
        if (end_ptr == token.c_str() || *end_ptr != '\0' || errno == ERANGE)
        {
            return false;
        }

        value = static_cast<int64_t>(parsed);
        return true;
    }

    static bool parse_unsigned(const std::string &token, int base, uint64_t &value)
    {
        errno = 0;
        char *end_ptr = nullptr;
        unsigned long long parsed = std::strtoull(token.c_str(), &end_ptr, base);
        if (end_ptr == token.c_str() || *end_ptr != '\0' || errno == ERANGE)
        {
            return false;
        }

        value = static_cast<uint64_t>(parsed);
        return true;
    }

    static bool parse_double_value(const std::string &token, double &value)
    {
        errno = 0;
        char *end_ptr = nullptr;
        double parsed = std::strtod(token.c_str(), &end_ptr);
        if (end_ptr == token.c_str() || *end_ptr != '\0' || errno == ERANGE)
        {
            return false;
        }

        value = parsed;
        return true;
    }

    static void append_with_field_width_impl(std::string &out, const std::string &text, char fill_char, size_t field_width)
    {
        if (field_width > text.size())
        {
            out.append(field_width - text.size(), fill_char);
        }

        out.append(text);
    }

    void basic_stringstream::clear()
    {
        buffer_.clear();
        read_pos_ = 0;
        number_base_ = NumberBase::Dec;
    }

    void basic_stringstream::skip_whitespace()
    {
        while (read_pos_ < buffer_.size() && is_space(buffer_[read_pos_]))
        {
            ++read_pos_;
        }
    }

    bool basic_stringstream::read_token(std::string &token)
    {
        skip_whitespace();
        if (read_pos_ >= buffer_.size())
        {
            return false;
        }

        size_t start = read_pos_;
        while (read_pos_ < buffer_.size() && !is_space(buffer_[read_pos_]))
        {
            ++read_pos_;
        }

        token = buffer_.substr(start, read_pos_ - start);
        return true;
    }

    basic_stringstream &basic_stringstream::getline(std::string &value, char delim)
    {
        value.clear();

        if (read_pos_ >= buffer_.size())
        {
            return *this;
        }

        while (read_pos_ < buffer_.size())
        {
            char c = buffer_[read_pos_++];
            if (c == delim)
            {
                break;
            }

            value.push_back(c);
        }

        return *this;
    }

    void basic_stringstream::append_with_field_width(std::string &target, const std::string &text)
    {
        append_with_field_width_impl(target, text, fill_char_, field_width_);
        field_width_ = 0;
    }

    basic_stringstream &basic_stringstream::operator<<(const char *str)
    {
        if (str)
        {
            append_with_field_width(buffer_, str);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(const std::string &str)
    {
        append_with_field_width(buffer_, str);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(char c)
    {
        std::string text(1, c);
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(int8_t value)
    {
        std::string text;
        append_signed_base(text, static_cast<int64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(uint8_t value)
    {
        std::string text;
        append_unsigned_base(text, static_cast<uint64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(int16_t value)
    {
        std::string text;
        append_signed_base(text, static_cast<int64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(uint16_t value)
    {
        std::string text;
        append_unsigned_base(text, static_cast<uint64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(int32_t value)
    {
        std::string text;
        append_signed_base(text, static_cast<int64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(uint32_t value)
    {
        std::string text;
        append_unsigned_base(text, static_cast<uint64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(long value)
    {
        std::string text;
        append_signed_base(text, static_cast<int64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(unsigned long value)
    {
        std::string text;
        append_unsigned_base(text, static_cast<uint64_t>(value), static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(int64_t value)
    {
        std::string text;
        append_signed_base(text, value, static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(uint64_t value)
    {
        std::string text;
        append_unsigned_base(text, value, static_cast<int>(number_base_));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(float value)
    {
        std::string text;
        append_float(text, value);
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(double value)
    {
        std::string text;
        append_float(text, static_cast<float>(value));
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(bool value)
    {
        append_with_field_width(buffer_, value ? "true" : "false");
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(const void *ptr)
    {
        std::string text;
        text.append("0x");
        append_unsigned_base(text, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(ptr)), 16);
        append_with_field_width(buffer_, text);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(std::ios_base &(*manipulator)(std::ios_base &))
    {
        if (manipulator == static_cast<std::ios_base &(*)(std::ios_base &)>(std::hex))
        {
            number_base_ = NumberBase::Hex;
        }
        else if (manipulator == static_cast<std::ios_base &(*)(std::ios_base &)>(std::dec))
        {
            number_base_ = NumberBase::Dec;
        }
        else if (manipulator == static_cast<std::ios_base &(*)(std::ios_base &)>(std::oct))
        {
            number_base_ = NumberBase::Oct;
        }

        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(const std::_Setfill<char> &manipulator)
    {
        fill_char_ = manipulator._M_c;
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(const std::_Setw &manipulator)
    {
        field_width_ = static_cast<size_t>(manipulator._M_n > 0 ? manipulator._M_n : 0);
        return *this;
    }

    basic_stringstream &basic_stringstream::operator<<(basic_stringstream &(*manipulator)(basic_stringstream &))
    {
        return manipulator(*this);
    }

    basic_stringstream &basic_stringstream::operator>>(std::string &value)
    {
        std::string token;
        if (read_token(token))
        {
            value = token;
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(char &value)
    {
        skip_whitespace();
        if (read_pos_ < buffer_.size())
        {
            value = buffer_[read_pos_++];
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(int8_t &value)
    {
        int64_t parsed;
        std::string token;
        if (read_token(token) && parse_signed(token, static_cast<int>(number_base_), parsed) && parsed >= std::numeric_limits<int8_t>::min()
            && parsed <= std::numeric_limits<int8_t>::max())
        {
            value = static_cast<int8_t>(parsed);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(uint8_t &value)
    {
        uint64_t parsed;
        std::string token;
        if (read_token(token) && parse_unsigned(token, static_cast<int>(number_base_), parsed)
            && parsed <= std::numeric_limits<uint8_t>::max())
        {
            value = static_cast<uint8_t>(parsed);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(int16_t &value)
    {
        int64_t parsed;
        std::string token;
        if (read_token(token) && parse_signed(token, static_cast<int>(number_base_), parsed)
            && parsed >= std::numeric_limits<int16_t>::min() && parsed <= std::numeric_limits<int16_t>::max())
        {
            value = static_cast<int16_t>(parsed);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(uint16_t &value)
    {
        uint64_t parsed;
        std::string token;
        if (read_token(token) && parse_unsigned(token, static_cast<int>(number_base_), parsed)
            && parsed <= std::numeric_limits<uint16_t>::max())
        {
            value = static_cast<uint16_t>(parsed);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(int32_t &value)
    {
        int64_t parsed;
        std::string token;
        if (read_token(token) && parse_signed(token, static_cast<int>(number_base_), parsed)
            && parsed >= std::numeric_limits<int32_t>::min() && parsed <= std::numeric_limits<int32_t>::max())
        {
            value = static_cast<int32_t>(parsed);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(uint32_t &value)
    {
        uint64_t parsed;
        std::string token;
        if (read_token(token) && parse_unsigned(token, static_cast<int>(number_base_), parsed)
            && parsed <= std::numeric_limits<uint32_t>::max())
        {
            value = static_cast<uint32_t>(parsed);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(int64_t &value)
    {
        int64_t parsed;
        std::string token;
        if (read_token(token) && parse_signed(token, static_cast<int>(number_base_), parsed))
        {
            value = parsed;
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(uint64_t &value)
    {
        uint64_t parsed;
        std::string token;
        if (read_token(token) && parse_unsigned(token, static_cast<int>(number_base_), parsed))
        {
            value = parsed;
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(float &value)
    {
        double parsed;
        std::string token;
        if (read_token(token) && parse_double_value(token, parsed))
        {
            value = static_cast<float>(parsed);
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(double &value)
    {
        double parsed;
        std::string token;
        if (read_token(token) && parse_double_value(token, parsed))
        {
            value = parsed;
        }
        return *this;
    }

    basic_stringstream &basic_stringstream::operator>>(bool &value)
    {
        std::string token;
        if (read_token(token))
        {
            if (token == "true" || token == "1")
            {
                value = true;
            }
            else if (token == "false" || token == "0")
            {
                value = false;
            }
        }
        return *this;
    }

    basic_stringstream &getline(basic_stringstream &ss, std::string &value, char delim)
    {
        return ss.getline(value, delim);
    }

    basic_stringstream &endl(basic_stringstream &ss)
    {
        ss << '\n';
        return ss;
    }

    basic_stringstream &flush(basic_stringstream &ss)
    {
        return ss;
    }

    basic_stringstream &hex(basic_stringstream &ss)
    {
        ss.set_base(basic_stringstream::NumberBase::Hex);
        return ss;
    }

    basic_stringstream &dec(basic_stringstream &ss)
    {
        ss.set_base(basic_stringstream::NumberBase::Dec);
        return ss;
    }

    basic_stringstream &oct(basic_stringstream &ss)
    {
        ss.set_base(basic_stringstream::NumberBase::Oct);
        return ss;
    }
}

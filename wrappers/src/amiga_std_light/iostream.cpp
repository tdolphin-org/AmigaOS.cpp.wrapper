//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "iostream.hpp"

#include <cstdio>
#include <cstring>

#include <proto/dos.h>
#include <proto/exec.h>

namespace amiga_std_light
{
    basic_ostream::basic_ostream()
      : buffer_pos(0)
    {
        buffer[0] = '\0';
    }

    basic_ostream::~basic_ostream()
    {
        flush_buffer();
    }

    void basic_ostream::flush_buffer()
    {
        if (buffer_pos > 0)
        {
            buffer[buffer_pos] = '\0';
            VPrintf("%s", (LONG *)&buffer);
            buffer_pos = 0;
        }
    }

    void basic_ostream::ensure_capacity(size_t needed)
    {
        if (buffer_pos + needed >= BUFFER_SIZE - 1)
        {
            flush_buffer();
        }
    }

    basic_ostream &basic_ostream::operator<<(const char *str)
    {
        if (str)
        {
            size_t len = strlen(str);
            while (len > 0)
            {
                size_t available = BUFFER_SIZE - buffer_pos - 1;
                size_t to_copy = (len < available) ? len : available;

                if (to_copy == 0)
                {
                    flush_buffer();
                    continue;
                }

                std::memcpy(buffer + buffer_pos, str, to_copy);
                buffer_pos += to_copy;
                str += to_copy;
                len -= to_copy;
            }
        }
        return *this;
    }

    basic_ostream &basic_ostream::operator<<(const std::string &str)
    {
        return *this << str.c_str();
    }

    basic_ostream &basic_ostream::operator<<(char c)
    {
        ensure_capacity(1);
        buffer[buffer_pos++] = c;
        return *this;
    }

    basic_ostream &basic_ostream::operator<<(int8_t value)
    {
        char temp[5]; // "-128\0"
        sprintf(temp, "%d", static_cast<int>(value));
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint8_t value)
    {
        char temp[4]; // "255\0"
        sprintf(temp, "%u", static_cast<unsigned int>(value));
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(int16_t value)
    {
        char temp[7]; // "-32768\0"
        sprintf(temp, "%d", static_cast<int>(value));
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint16_t value)
    {
        char temp[6]; // "65535\0"
        sprintf(temp, "%u", static_cast<unsigned int>(value));
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(int32_t value)
    {
        char temp[12]; // "-2147483648\0"
        sprintf(temp, "%d", value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint32_t value)
    {
        char temp[11]; // "4294967295\0"
        sprintf(temp, "%u", value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(int64_t value)
    {
        char temp[21]; // "-9223372036854775808\0"
        sprintf(temp, "%lld", value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint64_t value)
    {
        char temp[21]; // "18446744073709551615\0"
        sprintf(temp, "%llu", value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(float value)
    {
        char temp[64];
        sprintf(temp, "%g", value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(double value)
    {
        char temp[64];
        sprintf(temp, "%g", value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(bool value)
    {
        return *this << (value ? "true" : "false");
    }

    basic_ostream &basic_ostream::operator<<(const void *ptr)
    {
        char temp[32];
        sprintf(temp, "%p", ptr);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(basic_ostream &(*manipulator)(basic_ostream &))
    {
        return manipulator(*this);
    }

    basic_ostream &basic_ostream::flush()
    {
        flush_buffer();
        return *this;
    }

    basic_ostream &basic_ostream::write(const char *str, size_t count)
    {
        if (str && count > 0)
        {
            while (count > 0)
            {
                size_t available = BUFFER_SIZE - buffer_pos - 1;
                size_t to_copy = (count < available) ? count : available;

                if (to_copy == 0)
                {
                    flush_buffer();
                    continue;
                }

                memcpy(buffer + buffer_pos, str, to_copy);
                buffer_pos += to_copy;
                str += to_copy;
                count -= to_copy;
            }
        }
        return *this;
    }

    basic_ostream &endl(basic_ostream &os)
    {
        os << '\n';
        return os.flush();
    }

    basic_ostream &flush(basic_ostream &os)
    {
        return os.flush();
    }

    basic_ostream cout;
    basic_ostream cerr;
    basic_ostream clog;
}

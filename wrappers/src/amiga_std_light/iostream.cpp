//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#include "iostream.hpp"

#include <cstring>

#include <proto/dos.h>
#include <proto/exec.h>

namespace amiga_std_light
{
    // RawDoFmt character copy callback in machine code
    // 0x16c0 = move.b d0,(a3)+  ; copy byte from d0 to (a3), increment a3
    // 0x4e75 = rts             ; return from subroutine
    static const uint32_t PutChar = 0x16c04e75;

    // Helper functions using RawDoFmt() instead of sprintf
    static void format_int8(char *buffer, int8_t value)
    {
        int32_t args[1] = { (int32_t)value };
        char *buf_ptr = buffer;
        RawDoFmt("%ld", args, (void (*)())PutChar, &buf_ptr);
        *buf_ptr = '\0';
    }

    static void format_uint8(char *buffer, uint8_t value)
    {
        int32_t args[1] = { (int32_t)value };
        char *buf_ptr = buffer;
        RawDoFmt("%lu", args, (void (*)())PutChar, &buf_ptr);
        *buf_ptr = '\0';
    }

    static void format_int16(char *buffer, int16_t value)
    {
        int32_t args[1] = { (int32_t)value };
        char *buf_ptr = buffer;
        RawDoFmt("%ld", args, (void (*)())PutChar, &buf_ptr);
        *buf_ptr = '\0';
    }

    static void format_uint16(char *buffer, uint16_t value)
    {
        int32_t args[1] = { (int32_t)value };
        char *buf_ptr = buffer;
        RawDoFmt("%lu", args, (void (*)())PutChar, &buf_ptr);
        *buf_ptr = '\0';
    }

    static void format_int32(char *buffer, int32_t value)
    {
        int32_t args[1] = { (int32_t)value };
        char *buf_ptr = buffer;
        RawDoFmt("%ld", args, (void (*)())PutChar, &buf_ptr);
        *buf_ptr = '\0';
    }

    static void format_uint32(char *buffer, uint32_t value)
    {
        int32_t args[1] = { (int32_t)value };
        char *buf_ptr = buffer;
        RawDoFmt("%lu", args, (void (*)())PutChar, &buf_ptr);
        *buf_ptr = '\0';
    }

    static void format_int64(char *buffer, int64_t value)
    {
        // For 64-bit values, we need to split into high and low parts on AmigaOS
        if (value == 0)
        {
            buffer[0] = '0';
            buffer[1] = '\0';
            return;
        }

        int is_negative = 0;
        if (value < 0)
        {
            is_negative = 1;
            value = -value;
        }

        // Simple conversion for 64-bit
        char digits[21];
        int digit_count = 0;
        while (value > 0)
        {
            digits[digit_count++] = '0' + (value % 10);
            value /= 10;
        }

        int pos = 0;
        if (is_negative)
        {
            buffer[pos++] = '-';
        }

        for (int i = digit_count - 1; i >= 0; i--)
        {
            buffer[pos++] = digits[i];
        }
        buffer[pos] = '\0';
    }

    static void format_uint64(char *buffer, uint64_t value)
    {
        if (value == 0)
        {
            buffer[0] = '0';
            buffer[1] = '\0';
            return;
        }

        char digits[21];
        int digit_count = 0;
        while (value > 0)
        {
            digits[digit_count++] = '0' + (value % 10);
            value /= 10;
        }

        int pos = 0;
        for (int i = digit_count - 1; i >= 0; i--)
        {
            buffer[pos++] = digits[i];
        }
        buffer[pos] = '\0';
    }

    static void format_ptr(char *buffer, const void *ptr)
    {
        int32_t args[1] = { (int32_t)ptr };
        char *buf_ptr = buffer;
        RawDoFmt("0x%lx", args, (void (*)())PutChar, &buf_ptr);
        *buf_ptr = '\0';
    }

    // For floating point, we'll use a simple approach since AmigaOS RawDoFmt doesn't support %g
    static void format_float(char *buffer, float value)
    {
        // Simple float to string conversion
        if (value == 0.0f)
        {
            buffer[0] = '0';
            buffer[1] = '\0';
            return;
        }

        // This is a simplified version - for full IEEE float support you'd need more complex code
        int int_part = (int)value;
        float frac_part = value - int_part;

        if (frac_part == 0.0f)
        {
            int32_t args[1] = { (int32_t)int_part };
            char *buf_ptr = buffer;
            RawDoFmt("%ld", args, (void (*)())PutChar, &buf_ptr);
            *buf_ptr = '\0';
        }
        else
        {
            // Simple approach: just show integer part for now
            int32_t args[1] = { (int32_t)int_part };
            char *buf_ptr = buffer;
            RawDoFmt("%ld", args, (void (*)())PutChar, &buf_ptr);
            *buf_ptr = '\0';
        }
    }

    static void format_double(char *buffer, double value)
    {
        // Simple double to string conversion (same approach as float)
        format_float(buffer, (float)value);
    }

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
            VPrintf("%s", (int32_t *)&buffer);
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
        format_int8(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint8_t value)
    {
        char temp[4]; // "255\0"
        format_uint8(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(int16_t value)
    {
        char temp[7]; // "-32768\0"
        format_int16(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint16_t value)
    {
        char temp[6]; // "65535\0"
        format_uint16(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(int32_t value)
    {
        char temp[12]; // "-2147483648\0"
        format_int32(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint32_t value)
    {
        char temp[11]; // "4294967295\0"
        format_uint32(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(int64_t value)
    {
        char temp[21]; // "-9223372036854775808\0"
        format_int64(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint64_t value)
    {
        char temp[21]; // "18446744073709551615\0"
        format_uint64(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(float value)
    {
        char temp[64];
        format_float(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(double value)
    {
        char temp[64];
        format_double(temp, value);
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(bool value)
    {
        return *this << (value ? "true" : "false");
    }

    basic_ostream &basic_ostream::operator<<(const void *ptr)
    {
        char temp[32];
        format_ptr(temp, ptr);
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

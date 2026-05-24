//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2026 TDolphin
//

#include "iostream.hpp"

#include <cstring>

#include <proto/dos.h>
#include <proto/exec.h>

#ifdef __MORPHOS__
#include <exec/rawfmt.h>
#endif

static void putCharToBuffer(char c, char **buf)
{
    *(*buf)++ = c;
}

namespace amiga_std_light
{
    static void format_uint32_base(char *buffer, uint32_t value, int base)
    {
        int normalized_base = 10;
        if (base == 16)
        {
            normalized_base = 16;
        }
        else if (base == 8)
        {
            normalized_base = 8;
        }

        if (value == 0)
        {
            buffer[0] = '0';
            buffer[1] = '\0';
            return;
        }

        static const char digits[] = "0123456789abcdef";
        char reversed[33];
        int digit_count = 0;

        while (value > 0)
        {
            const uint32_t rem = value % static_cast<uint32_t>(normalized_base);
            reversed[digit_count++] = digits[rem];
            value /= static_cast<uint32_t>(normalized_base);
        }

        int pos = 0;
        for (int i = digit_count - 1; i >= 0; i--)
        {
            buffer[pos++] = reversed[i];
        }
        buffer[pos] = '\0';
    }

    // Helper functions without RawDoFmt/sprintf.
    static void format_int8(char *buffer, int8_t value)
    {
        if (value < 0)
        {
            buffer[0] = '-';
            const uint32_t magnitude = static_cast<uint32_t>(-(static_cast<int32_t>(value) + 1)) + 1;
            format_uint32_base(buffer + 1, magnitude, 10);
            return;
        }

        format_uint32_base(buffer, static_cast<uint32_t>(value), 10);
    }

    static void format_int32_base(char *buffer, int32_t value, int base)
    {
        switch (base)
        {
            case 16:
            case 8:
                format_uint32_base(buffer, static_cast<uint32_t>(value), base);
                break;
            default:
                if (value < 0)
                {
                    buffer[0] = '-';
                    const uint32_t magnitude = static_cast<uint32_t>(-(value + 1)) + 1;
                    format_uint32_base(buffer + 1, magnitude, 10);
                }
                else
                {
                    format_uint32_base(buffer, static_cast<uint32_t>(value), 10);
                }
                break;
        }
    }

    static void format_uint8(char *buffer, uint8_t value)
    {
        format_uint32_base(buffer, static_cast<uint32_t>(value), 10);
    }

    static void format_int16(char *buffer, int16_t value)
    {
        format_int32_base(buffer, static_cast<int32_t>(value), 10);
    }

    static void format_uint16(char *buffer, uint16_t value)
    {
        format_uint32_base(buffer, static_cast<uint32_t>(value), 10);
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
        uint64_t magnitude;
        if (value < 0)
        {
            is_negative = 1;
            // Avoid UB for INT64_MIN by converting through -(value + 1).
            magnitude = static_cast<uint64_t>(-(value + 1)) + 1;
        }
        else
        {
            magnitude = static_cast<uint64_t>(value);
        }

        // Simple conversion for 64-bit
        char digits[21];
        int digit_count = 0;
        while (magnitude > 0)
        {
            digits[digit_count++] = '0' + (magnitude % 10);
            magnitude /= 10;
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
#ifdef __MORPHOS__
        ULONG args[] = { (ULONG)ptr };
        NewRawDoFmt("0x%08lx", RAWFMTFUNC_STRING, buffer, args);
#else
        ULONG args[] = { (ULONG)ptr };
        RawDoFmt((STRPTR) "0x%08lx", args, (void (*)())putCharToBuffer, buffer);
#endif
    }

    // For floating point, we'll use a simple approach since AmigaOS RawDoFmt doesn't support %g
    static void format_float(char *buffer, float value)
    {
        // Handle special cases
        if (value == 0.0f)
        {
            buffer[0] = '0';
            buffer[1] = '\0';
            return;
        }

        // Handle negative values
        int pos = 0;
        if (value < 0.0f)
        {
            buffer[pos++] = '-';
            value = -value;
        }

        // Split integer and fractional parts
        int int_part = (int)value;
        float frac_part = value - int_part;

        // Format integer part
        if (int_part == 0)
        {
            buffer[pos++] = '0';
        }
        else
        {
            // Convert integer part to string
            char int_digits[32];
            int digit_count = 0;
            int temp = int_part;
            while (temp > 0)
            {
                int_digits[digit_count++] = '0' + (temp % 10);
                temp /= 10;
            }
            // Reverse digits
            for (int i = digit_count - 1; i >= 0; i--)
            {
                buffer[pos++] = int_digits[i];
            }
        }

        // Add decimal point and fractional part if needed
        if (frac_part > 0.0001f) // Only show decimals if significant
        {
            buffer[pos++] = '.';

            // Show up to 6 decimal places
            for (int i = 0; i < 6 && frac_part > 0.0001f; i++)
            {
                frac_part *= 10.0f;
                int digit = (int)frac_part;
                buffer[pos++] = '0' + digit;
                frac_part -= digit;
            }
        }

        buffer[pos] = '\0';
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
            PutStr(buffer);
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
        return operator<<(str.c_str());
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
        char temp[12]; // "-2147483648\0" or hex equivalent
        format_int32_base(temp, value, static_cast<int>(number_base_));
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(uint32_t value)
    {
        char temp[11]; // "4294967295\0" or hex equivalent
        format_uint32_base(temp, value, static_cast<int>(number_base_));
        return *this << temp;
    }

    basic_ostream &basic_ostream::operator<<(long value)
    {
        if (sizeof(long) <= sizeof(int32_t))
        {
            return *this << static_cast<int32_t>(value);
        }
        return *this << static_cast<int64_t>(value);
    }

    basic_ostream &basic_ostream::operator<<(unsigned long value)
    {
        if (sizeof(unsigned long) <= sizeof(uint32_t))
        {
            return *this << static_cast<uint32_t>(value);
        }
        return *this << static_cast<uint64_t>(value);
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

    basic_ostream &hex(basic_ostream &os)
    {
        os.set_base(basic_ostream::NumberBase::Hex);
        return os;
    }

    basic_ostream &dec(basic_ostream &os)
    {
        os.set_base(basic_ostream::NumberBase::Dec);
        return os;
    }

    basic_ostream &oct(basic_ostream &os)
    {
        os.set_base(basic_ostream::NumberBase::Oct);
        return os;
    }

    basic_ostream cout;
    basic_ostream cerr;
    basic_ostream clog;
}

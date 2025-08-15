//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#ifdef STD_LIGHT

#include <cstddef>
#include <cstdint>
#include <string>

#include <proto/dos.h>
#include <proto/exec.h>

namespace amiga_std_light
{
    class basic_ostream
    {
      public:
        // Internal state for formatting
        enum class NumberBase
        {
            Dec = 10,
            Hex = 16,
            Oct = 8
        };

      private:
        static constexpr size_t BUFFER_SIZE = 512;
        char buffer[BUFFER_SIZE];
        size_t buffer_pos;
        NumberBase number_base_ = NumberBase::Dec;

        void flush_buffer();
        void ensure_capacity(size_t needed);

      public:
        basic_ostream();
        ~basic_ostream();

        void set_base(NumberBase base)
        {
            number_base_ = base;
        }

        basic_ostream &operator<<(const char *str);
        basic_ostream &operator<<(const std::string &str);

        basic_ostream &operator<<(char c);
        basic_ostream &operator<<(int8_t value);
        basic_ostream &operator<<(uint8_t value);
        basic_ostream &operator<<(int16_t value);
        basic_ostream &operator<<(uint16_t value);
        basic_ostream &operator<<(int32_t value);
        basic_ostream &operator<<(uint32_t value);
        basic_ostream &operator<<(int64_t value);
        basic_ostream &operator<<(uint64_t value);
        basic_ostream &operator<<(float value);
        basic_ostream &operator<<(double value);
        basic_ostream &operator<<(bool value);
        basic_ostream &operator<<(const void *ptr);

        basic_ostream &operator<<(basic_ostream &(*manipulator)(basic_ostream &));

        basic_ostream &flush();
        basic_ostream &write(const char *str, size_t count);

        NumberBase get_base() const
        {
            return number_base_;
        }
    };

    basic_ostream &endl(basic_ostream &os);
    basic_ostream &flush(basic_ostream &os);
    basic_ostream &hex(basic_ostream &os);
    basic_ostream &dec(basic_ostream &os);
    basic_ostream &oct(basic_ostream &os);

    extern basic_ostream cout;
    extern basic_ostream cerr;
    extern basic_ostream clog;
}

namespace std
{
    using amiga_std_light::cerr;
    using amiga_std_light::clog;
    using amiga_std_light::cout;
    using amiga_std_light::dec;
    using amiga_std_light::endl;
    using amiga_std_light::flush;
    using amiga_std_light::hex;
    using amiga_std_light::oct;
}
#else
#include <iostream>
#endif

//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#ifdef STD_LIGHT

#include <cstddef>
#include <cstring>

namespace amiga_std_light
{
    class basic_string
    {
      private:
        char *data_;
        size_t size_;
        size_t capacity_;

        void reallocate(size_t new_capacity);
        void ensure_capacity(size_t needed_size);

      public:
        // Constructors
        basic_string();
        basic_string(const char *str);
        basic_string(const char *str, size_t len);
        basic_string(const basic_string &other);
        basic_string(size_t count, char ch);

        // Destructor
        ~basic_string();

        // Assignment operators
        basic_string &operator=(const basic_string &other);
        basic_string &operator=(const char *str);
        basic_string &operator=(char ch);

        // Element access
        char &operator[](size_t index);
        const char &operator[](size_t index) const;
        char &at(size_t index);
        const char &at(size_t index) const;
        char &front();
        const char &front() const;
        char &back();
        const char &back() const;
        const char *data() const;
        const char *c_str() const;

        // Iterators (simple pointer-based)
        char *begin();
        const char *begin() const;
        char *end();
        const char *end() const;

        // Capacity
        bool empty() const;
        size_t size() const;
        size_t length() const;
        size_t capacity() const;
        void reserve(size_t new_capacity);
        void shrink_to_fit();

        // Modifiers
        void clear();
        basic_string &insert(size_t index, const char *str);
        basic_string &insert(size_t index, const basic_string &str);
        basic_string &erase(size_t index = 0, size_t len = npos);
        void push_back(char ch);
        void pop_back();
        basic_string &append(const char *str);
        basic_string &append(const basic_string &str);
        basic_string &append(size_t count, char ch);
        basic_string &assign(const char *str);
        basic_string &assign(const basic_string &str);
        basic_string &assign(size_t count, char ch);

        // String operations
        size_t find(const char *str, size_t pos = 0) const;
        size_t find(const basic_string &str, size_t pos = 0) const;
        size_t find(char ch, size_t pos = 0) const;
        size_t rfind(const char *str, size_t pos = npos) const;
        size_t rfind(const basic_string &str, size_t pos = npos) const;
        size_t rfind(char ch, size_t pos = npos) const;
        basic_string substr(size_t pos = 0, size_t len = npos) const;
        int compare(const char *str) const;
        int compare(const basic_string &str) const;

        // Operators
        basic_string operator+(const char *str) const;
        basic_string operator+(const basic_string &str) const;
        basic_string operator+(char ch) const;
        basic_string &operator+=(const char *str);
        basic_string &operator+=(const basic_string &str);
        basic_string &operator+=(char ch);

        // Comparison operators
        bool operator==(const char *str) const;
        bool operator==(const basic_string &str) const;
        bool operator!=(const char *str) const;
        bool operator!=(const basic_string &str) const;
        bool operator<(const char *str) const;
        bool operator<(const basic_string &str) const;
        bool operator<=(const char *str) const;
        bool operator<=(const basic_string &str) const;
        bool operator>(const char *str) const;
        bool operator>(const basic_string &str) const;
        bool operator>=(const char *str) const;
        bool operator>=(const basic_string &str) const;

        // Constants
        static const size_t npos = static_cast<size_t>(-1);
    };

    // Non-member operators
    basic_string operator+(const char *lhs, const basic_string &rhs);
    basic_string operator+(char lhs, const basic_string &rhs);
}

namespace std
{
    using string = amiga_std_light::basic_string;
}

#else
#include <string>
#endif
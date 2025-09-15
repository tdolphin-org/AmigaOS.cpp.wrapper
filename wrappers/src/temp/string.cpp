//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <string>

/*
#include "string.hpp"

#ifdef STD_LIGHT

#include <cstdlib>
#include <cstring>

#include <proto/exec.h>

namespace amiga_std_light
{
    // Private helper methods
    void basic_string::reallocate(size_t new_capacity)
    {
        if (new_capacity <= capacity_)
            return;

        char *new_data = static_cast<char *>(AllocMem(new_capacity + 1, MEMF_PUBLIC));
        if (!new_data)
            return; // Handle allocation failure gracefully

        if (data_)
        {
            std::memcpy(new_data, data_, size_);
            FreeMem(data_, capacity_ + 1);
        }

        data_ = new_data;
        capacity_ = new_capacity;
        data_[size_] = '\0';
    }

    void basic_string::ensure_capacity(size_t needed_size)
    {
        if (needed_size > capacity_)
        {
            size_t new_capacity = capacity_ == 0 ? 16 : capacity_;
            while (new_capacity < needed_size)
                new_capacity *= 2;
            reallocate(new_capacity);
        }
    }

    // Constructors
    basic_string::basic_string()
        : data_(nullptr), size_(0), capacity_(0)
    {
    }

    basic_string::basic_string(const char *str)
        : data_(nullptr), size_(0), capacity_(0)
    {
        if (str)
        {
            size_ = std::strlen(str);
            ensure_capacity(size_);
            std::memcpy(data_, str, size_);
            data_[size_] = '\0';
        }
    }

    basic_string::basic_string(const char *str, size_t len)
        : data_(nullptr), size_(0), capacity_(0)
    {
        if (str && len > 0)
        {
            size_ = len;
            ensure_capacity(size_);
            std::memcpy(data_, str, size_);
            data_[size_] = '\0';
        }
    }

    basic_string::basic_string(const basic_string &other)
        : data_(nullptr), size_(0), capacity_(0)
    {
        if (other.size_ > 0)
        {
            size_ = other.size_;
            ensure_capacity(size_);
            std::memcpy(data_, other.data_, size_);
            data_[size_] = '\0';
        }
    }

    basic_string::basic_string(size_t count, char ch)
        : data_(nullptr), size_(0), capacity_(0)
    {
        if (count > 0)
        {
            size_ = count;
            ensure_capacity(size_);
            std::memset(data_, ch, size_);
            data_[size_] = '\0';
        }
    }

    // Destructor
    basic_string::~basic_string()
    {
        if (data_)
        {
            FreeMem(data_, capacity_ + 1);
        }
    }

    // Assignment operators
    basic_string &basic_string::operator=(const basic_string &other)
    {
        if (this != &other)
        {
            clear();
            if (other.size_ > 0)
            {
                ensure_capacity(other.size_);
                size_ = other.size_;
                std::memcpy(data_, other.data_, size_);
                data_[size_] = '\0';
            }
        }
        return *this;
    }

    basic_string &basic_string::operator=(const char *str)
    {
        clear();
        if (str)
        {
            size_t len = std::strlen(str);
            if (len > 0)
            {
                ensure_capacity(len);
                size_ = len;
                std::memcpy(data_, str, size_);
                data_[size_] = '\0';
            }
        }
        return *this;
    }

    basic_string &basic_string::operator=(char ch)
    {
        clear();
        ensure_capacity(1);
        size_ = 1;
        data_[0] = ch;
        data_[1] = '\0';
        return *this;
    }

    // Element access
    char &basic_string::operator[](size_t index)
    {
        return data_[index];
    }

    const char &basic_string::operator[](size_t index) const
    {
        return data_[index];
    }

    char &basic_string::at(size_t index)
    {
        return data_[index]; // Should add bounds checking in production
    }

    const char &basic_string::at(size_t index) const
    {
        return data_[index]; // Should add bounds checking in production
    }

    char &basic_string::front()
    {
        return data_[0];
    }

    const char &basic_string::front() const
    {
        return data_[0];
    }

    char &basic_string::back()
    {
        return data_[size_ - 1];
    }

    const char &basic_string::back() const
    {
        return data_[size_ - 1];
    }

    const char *basic_string::data() const
    {
        return data_ ? data_ : "";
    }

    const char *basic_string::c_str() const
    {
        return data();
    }

    // Iterators
    char *basic_string::begin()
    {
        return data_;
    }

    const char *basic_string::begin() const
    {
        return data_;
    }

    char *basic_string::end()
    {
        return data_ + size_;
    }

    const char *basic_string::end() const
    {
        return data_ + size_;
    }

    // Capacity
    bool basic_string::empty() const
    {
        return size_ == 0;
    }

    size_t basic_string::size() const
    {
        return size_;
    }

    size_t basic_string::length() const
    {
        return size_;
    }

    size_t basic_string::capacity() const
    {
        return capacity_;
    }

    void basic_string::reserve(size_t new_capacity)
    {
        if (new_capacity > capacity_)
        {
            reallocate(new_capacity);
        }
    }

    void basic_string::shrink_to_fit()
    {
        if (capacity_ > size_)
        {
            reallocate(size_);
        }
    }

    // Modifiers
    void basic_string::clear()
    {
        size_ = 0;
        if (data_)
        {
            data_[0] = '\0';
        }
    }

    basic_string &basic_string::append(const char *str)
    {
        if (str)
        {
            size_t len = std::strlen(str);
            if (len > 0)
            {
                ensure_capacity(size_ + len);
                std::memcpy(data_ + size_, str, len);
                size_ += len;
                data_[size_] = '\0';
            }
        }
        return *this;
    }

    basic_string &basic_string::append(const basic_string &str)
    {
        if (str.size_ > 0)
        {
            ensure_capacity(size_ + str.size_);
            std::memcpy(data_ + size_, str.data_, str.size_);
            size_ += str.size_;
            data_[size_] = '\0';
        }
        return *this;
    }

    basic_string &basic_string::append(size_t count, char ch)
    {
        if (count > 0)
        {
            ensure_capacity(size_ + count);
            std::memset(data_ + size_, ch, count);
            size_ += count;
            data_[size_] = '\0';
        }
        return *this;
    }

    void basic_string::push_back(char ch)
    {
        ensure_capacity(size_ + 1);
        data_[size_] = ch;
        size_++;
        data_[size_] = '\0';
    }

    void basic_string::pop_back()
    {
        if (size_ > 0)
        {
            size_--;
            data_[size_] = '\0';
        }
    }

    // Operators
    basic_string &basic_string::operator+=(const char *str)
    {
        return append(str);
    }

    basic_string &basic_string::operator+=(const basic_string &str)
    {
        return append(str);
    }

    basic_string &basic_string::operator+=(char ch)
    {
        push_back(ch);
        return *this;
    }

    basic_string basic_string::operator+(const char *str) const
    {
        basic_string result(*this);
        result.append(str);
        return result;
    }

    basic_string basic_string::operator+(const basic_string &str) const
    {
        basic_string result(*this);
        result.append(str);
        return result;
    }

    basic_string basic_string::operator+(char ch) const
    {
        basic_string result(*this);
        result.push_back(ch);
        return result;
    }

    // Comparison operators
    bool basic_string::operator==(const char *str) const
    {
        if (!str)
            return size_ == 0;
        return std::strcmp(data(), str) == 0;
    }

    bool basic_string::operator==(const basic_string &str) const
    {
        if (size_ != str.size_)
            return false;
        if (size_ == 0)
            return true;
        return std::memcmp(data_, str.data_, size_) == 0;
    }

    bool basic_string::operator!=(const char *str) const
    {
        return !(*this == str);
    }

    bool basic_string::operator!=(const basic_string &str) const
    {
        return !(*this == str);
    }

    bool basic_string::operator<(const char *str) const
    {
        return std::strcmp(data(), str ? str : "") < 0;
    }

    bool basic_string::operator<(const basic_string &str) const
    {
        return std::strcmp(data(), str.data()) < 0;
    }

    // String operations
    size_t basic_string::find(const char *str, size_t pos) const
    {
        if (!str || pos >= size_)
            return npos;

        const char *found = std::strstr(data_ + pos, str);
        if (found)
            return found - data_;
        return npos;
    }

    size_t basic_string::find(char ch, size_t pos) const
    {
        if (pos >= size_)
            return npos;

        const char *found = std::strchr(data_ + pos, ch);
        if (found)
            return found - data_;
        return npos;
    }

    basic_string basic_string::substr(size_t pos, size_t len) const
    {
        if (pos >= size_)
            return basic_string();

        if (len == npos || pos + len > size_)
            len = size_ - pos;

        return basic_string(data_ + pos, len);
    }

    int basic_string::compare(const char *str) const
    {
        return std::strcmp(data(), str ? str : "");
    }

    int basic_string::compare(const basic_string &str) const
    {
        return std::strcmp(data(), str.data());
    }

    // Non-member operators
    basic_string operator+(const char *lhs, const basic_string &rhs)
    {
        basic_string result(lhs);
        result.append(rhs);
        return result;
    }

    basic_string operator+(char lhs, const basic_string &rhs)
    {
        basic_string result(1, lhs);
        result.append(rhs);
        return result;
    }
}

#endif*/
#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <initializer_list>

#include <vector>

/*
#include <proto/exec.h>

namespace amiga_std_light
{
    template <typename T, typename Allocator = void> class vector
    {
      private:
        T *data_;
        size_t size_;
        size_t capacity_;

        static constexpr size_t DEFAULT_CAPACITY = 4;
        static constexpr float GROWTH_FACTOR = 1.5f;

        void grow()
        {
            size_t new_capacity = capacity_ == 0 ? DEFAULT_CAPACITY : static_cast<size_t>(capacity_ * GROWTH_FACTOR);
            reserve(new_capacity);
        }

        void deallocate()
        {
            if (data_)
            {
                // Wywołaj destruktory dla wszystkich elementów
                for (size_t i = 0; i < size_; ++i)
                {
                    data_[i].~T();
                }
                // Zwolnij pamięć przez AmigaOS
                FreeMem(data_, capacity_ * sizeof(T));
                data_ = nullptr;
                size_ = 0;
                capacity_ = 0;
            }
        }

      public:
        // Typy pomocnicze
        using value_type = T;
        using size_type = size_t;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using iterator = T *;
        using const_iterator = const T *;

        // Konstruktory
        vector()
          : data_(nullptr)
          , size_(0)
          , capacity_(0)
        {
        }

        explicit vector(size_t count)
          : data_(nullptr)
          , size_(0)
          , capacity_(0)
        {
            resize(count);
        }

        vector(size_t count, const T &value)
          : data_(nullptr)
          , size_(0)
          , capacity_(0)
        {
            resize(count, value);
        }

        // Konstruktor z initializer_list
        vector(std::initializer_list<T> init)
          : data_(nullptr)
          , size_(0)
          , capacity_(0)
        {
            reserve(init.size());
            for (const auto &item : init)
            {
                push_back(item);
            }
        }

        // Copy constructor
        vector(const vector &other)
          : data_(nullptr)
          , size_(0)
          , capacity_(0)
        {
            reserve(other.size_);
            for (size_t i = 0; i < other.size_; ++i)
            {
                push_back(other.data_[i]);
            }
        }

        // Destruktor
        ~vector()
        {
            deallocate();
        }

        // Assignment operator
        vector &operator=(const vector &other)
        {
            if (this != &other)
            {
                clear();
                reserve(other.size_);
                for (size_t i = 0; i < other.size_; ++i)
                {
                    push_back(other.data_[i]);
                }
            }
            return *this;
        }

        // Assignment operator z initializer_list
        vector &operator=(std::initializer_list<T> init)
        {
            clear();
            reserve(init.size());
            for (const auto &item : init)
            {
                push_back(item);
            }
            return *this;
        }

        // Iteratory
        iterator begin()
        {
            return data_;
        }
        const_iterator begin() const
        {
            return data_;
        }
        iterator end()
        {
            return data_ + size_;
        }
        const_iterator end() const
        {
            return data_ + size_;
        }

        // Dostęp do elementów
        reference operator[](size_t index)
        {
            return data_[index];
        }

        const_reference operator[](size_t index) const
        {
            return data_[index];
        }

        reference at(size_t index)
        {
            if (index >= size_)
            {
                throw std::out_of_range("vector::at: index out of range");
            }
            return data_[index];
        }

        const_reference at(size_t index) const
        {
            if (index >= size_)
            {
                throw std::out_of_range("vector::at: index out of range");
            }
            return data_[index];
        }

        reference front()
        {
            return data_[0];
        }
        const_reference front() const
        {
            return data_[0];
        }
        reference back()
        {
            return data_[size_ - 1];
        }
        const_reference back() const
        {
            return data_[size_ - 1];
        }

        // Informacje o rozmiarze
        size_t size() const
        {
            return size_;
        }
        size_t capacity() const
        {
            return capacity_;
        }
        bool empty() const
        {
            return size_ == 0;
        }

        // Modyfikacje rozmiaru
        void reserve(size_t new_capacity)
        {
            if (new_capacity <= capacity_)
            {
                return;
            }

            // Alokuj nową pamięć przez AmigaOS
            T *new_data = static_cast<T *>(AllocMem(new_capacity * sizeof(T), MEMF_ANY));
            if (!new_data)
            {
                throw std::bad_alloc();
            }

            // Przenieś istniejące elementy
            for (size_t i = 0; i < size_; ++i)
            {
                new (&new_data[i]) T(std::move(data_[i]));
                data_[i].~T();
            }

            // Zwolnij starą pamięć
            if (data_)
            {
                FreeMem(data_, capacity_ * sizeof(T));
            }

            data_ = new_data;
            capacity_ = new_capacity;
        }

        void resize(size_t new_size)
        {
            if (new_size > capacity_)
            {
                reserve(new_size);
            }

            // Zniszcz nadmiarowe elementy
            for (size_t i = new_size; i < size_; ++i)
            {
                data_[i].~T();
            }

            // Skonstruuj nowe elementy z domyślną wartością
            for (size_t i = size_; i < new_size; ++i)
            {
                new (&data_[i]) T();
            }

            size_ = new_size;
        }

        void resize(size_t new_size, const T &value)
        {
            if (new_size > capacity_)
            {
                reserve(new_size);
            }

            // Zniszcz nadmiarowe elementy
            for (size_t i = new_size; i < size_; ++i)
            {
                data_[i].~T();
            }

            // Skonstruuj nowe elementy z podaną wartością
            for (size_t i = size_; i < new_size; ++i)
            {
                new (&data_[i]) T(value);
            }

            size_ = new_size;
        }

        void clear()
        {
            for (size_t i = 0; i < size_; ++i)
            {
                data_[i].~T();
            }
            size_ = 0;
        }

        // Dodawanie/usuwanie elementów
        void push_back(const T &value)
        {
            if (size_ >= capacity_)
            {
                grow();
            }
            new (&data_[size_]) T(value);
            ++size_;
        }

        void push_back(T &&value)
        {
            if (size_ >= capacity_)
            {
                grow();
            }
            new (&data_[size_]) T(std::move(value));
            ++size_;
        }

        void pop_back()
        {
            if (size_ > 0)
            {
                --size_;
                data_[size_].~T();
            }
        }

        // Emplacement
        template <typename... Args> void emplace_back(Args &&...args)
        {
            if (size_ >= capacity_)
            {
                grow();
            }
            new (&data_[size_]) T(std::forward<Args>(args)...);
            ++size_;
        }

        // Dostęp do surowych danych
        T *data()
        {
            return data_;
        }
        const T *data() const
        {
            return data_;
        }

        // Metoda assign z initializer_list
        void assign(std::initializer_list<T> init)
        {
            clear();
            reserve(init.size());
            for (const auto &item : init)
            {
                push_back(item);
            }
        }
    };

} // namespace amiga_std_light

// Nadpisanie namespace std
namespace std
{
    using amiga_std_light::vector;
}*/
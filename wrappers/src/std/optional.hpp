#pragma once

#ifdef __MORPHOS__
#include <optional>
#else

#include <stdexcept>
#include <type_traits>
#include <utility>

namespace std
{
    // Exception thrown when accessing empty optional
    class bad_optional_access : public std::exception
    {
    public:
        const char* what() const noexcept override
        {
            return "bad optional access";
        }
    };

    // Tag type for creating empty optional
    struct nullopt_t
    {
        explicit constexpr nullopt_t(int) {}
    };

    constexpr nullopt_t nullopt{0};

    // Tag type for in-place construction
    struct in_place_t
    {
        explicit constexpr in_place_t() = default;
    };

    constexpr in_place_t in_place{};

    template<typename T>
    class optional
    {
    private:
        alignas(T) char storage_[sizeof(T)];
        bool has_value_;

        T* ptr() noexcept
        {
            return reinterpret_cast<T*>(storage_);
        }

        const T* ptr() const noexcept
        {
            return reinterpret_cast<const T*>(storage_);
        }

        void destroy()
        {
            if (has_value_)
            {
                ptr()->~T();
                has_value_ = false;
            }
        }

    public:
        using value_type = T;

        // Default constructor - creates empty optional
        constexpr optional() noexcept : has_value_(false) {}

        // Nullopt constructor - creates empty optional
        constexpr optional(nullopt_t) noexcept : has_value_(false) {}

        // Copy constructor
        optional(const optional& other)
            : has_value_(other.has_value_)
        {
            if (other.has_value_)
            {
                new (storage_) T(*other.ptr());
            }
        }

        // Move constructor
        optional(optional&& other) noexcept(std::is_nothrow_move_constructible<T>::value)
            : has_value_(other.has_value_)
        {
            if (other.has_value_)
            {
                new (storage_) T(std::move(*other.ptr()));
                other.destroy();
            }
        }

        // Value constructor
        template<typename U = T>
        constexpr optional(U&& value)
            : has_value_(true)
        {
            new (storage_) T(std::forward<U>(value));
        }

        // In-place constructor
        template<typename... Args>
        constexpr explicit optional(in_place_t, Args&&... args)
            : has_value_(true)
        {
            new (storage_) T(std::forward<Args>(args)...);
        }

        // Destructor
        ~optional()
        {
            destroy();
        }

        // Copy assignment
        optional& operator=(const optional& other)
        {
            if (this != &other)
            {
                if (other.has_value_)
                {
                    if (has_value_)
                    {
                        *ptr() = *other.ptr();
                    }
                    else
                    {
                        new (storage_) T(*other.ptr());
                        has_value_ = true;
                    }
                }
                else
                {
                    destroy();
                }
            }
            return *this;
        }

        // Move assignment
        optional& operator=(optional&& other) noexcept(std::is_nothrow_move_assignable<T>::value && std::is_nothrow_move_constructible<T>::value)
        {
            if (this != &other)
            {
                if (other.has_value_)
                {
                    if (has_value_)
                    {
                        *ptr() = std::move(*other.ptr());
                    }
                    else
                    {
                        new (storage_) T(std::move(*other.ptr()));
                        has_value_ = true;
                    }
                    other.destroy();
                }
                else
                {
                    destroy();
                }
            }
            return *this;
        }

        // Nullopt assignment
        optional& operator=(nullopt_t) noexcept
        {
            destroy();
            return *this;
        }

        // Value assignment
        template<typename U = T>
        optional& operator=(U&& value)
        {
            if (has_value_)
            {
                *ptr() = std::forward<U>(value);
            }
            else
            {
                new (storage_) T(std::forward<U>(value));
                has_value_ = true;
            }
            return *this;
        }

        // Check if optional has value
        constexpr bool has_value() const noexcept
        {
            return has_value_;
        }

        // Conversion to bool
        constexpr explicit operator bool() const noexcept
        {
            return has_value_;
        }

        // Access value (throws if empty)
        constexpr T& value() &
        {
            if (!has_value_)
                throw bad_optional_access();
            return *ptr();
        }

        constexpr const T& value() const &
        {
            if (!has_value_)
                throw bad_optional_access();
            return *ptr();
        }

        constexpr T&& value() &&
        {
            if (!has_value_)
                throw bad_optional_access();
            return std::move(*ptr());
        }

        constexpr const T&& value() const &&
        {
            if (!has_value_)
                throw bad_optional_access();
            return std::move(*ptr());
        }

        // Access value (undefined behavior if empty)
        constexpr T& operator*() & noexcept
        {
            return *ptr();
        }

        constexpr const T& operator*() const & noexcept
        {
            return *ptr();
        }

        constexpr T&& operator*() && noexcept
        {
            return std::move(*ptr());
        }

        constexpr const T&& operator*() const && noexcept
        {
            return std::move(*ptr());
        }

        // Access value pointer (undefined behavior if empty)
        constexpr T* operator->() noexcept
        {
            return ptr();
        }

        constexpr const T* operator->() const noexcept
        {
            return ptr();
        }

        // Access value with default
        template<typename U>
        constexpr T value_or(U&& default_value) const &
        {
            return has_value_ ? *ptr() : static_cast<T>(std::forward<U>(default_value));
        }

        template<typename U>
        constexpr T value_or(U&& default_value) &&
        {
            return has_value_ ? std::move(*ptr()) : static_cast<T>(std::forward<U>(default_value));
        }

        // Swap
        void swap(optional& other) noexcept(std::is_nothrow_move_constructible<T>::value && std::is_nothrow_swappable<T>::value)
        {
            if (has_value_ && other.has_value_)
            {
                using std::swap;
                swap(*ptr(), *other.ptr());
            }
            else if (has_value_)
            {
                new (other.storage_) T(std::move(*ptr()));
                other.has_value_ = true;
                destroy();
            }
            else if (other.has_value_)
            {
                new (storage_) T(std::move(*other.ptr()));
                has_value_ = true;
                other.destroy();
            }
        }

        // Reset - make optional empty
        void reset() noexcept
        {
            destroy();
        }

        // Emplace - construct value in place
        template<typename... Args>
        T& emplace(Args&&... args)
        {
            destroy();
            new (storage_) T(std::forward<Args>(args)...);
            has_value_ = true;
            return *ptr();
        }
    };

    // Comparison operators
    template<typename T>
    constexpr bool operator==(const optional<T>& lhs, const optional<T>& rhs)
    {
        if (lhs.has_value() != rhs.has_value())
            return false;
        if (!lhs.has_value())
            return true;
        return *lhs == *rhs;
    }

    template<typename T>
    constexpr bool operator!=(const optional<T>& lhs, const optional<T>& rhs)
    {
        return !(lhs == rhs);
    }

    template<typename T>
    constexpr bool operator<(const optional<T>& lhs, const optional<T>& rhs)
    {
        if (!rhs.has_value())
            return false;
        if (!lhs.has_value())
            return true;
        return *lhs < *rhs;
    }

    template<typename T>
    constexpr bool operator<=(const optional<T>& lhs, const optional<T>& rhs)
    {
        return !(rhs < lhs);
    }

    template<typename T>
    constexpr bool operator>(const optional<T>& lhs, const optional<T>& rhs)
    {
        return rhs < lhs;
    }

    template<typename T>
    constexpr bool operator>=(const optional<T>& lhs, const optional<T>& rhs)
    {
        return !(lhs < rhs);
    }

    // Comparison with nullopt
    template<typename T>
    constexpr bool operator==(const optional<T>& opt, nullopt_t) noexcept
    {
        return !opt.has_value();
    }

    template<typename T>
    constexpr bool operator==(nullopt_t, const optional<T>& opt) noexcept
    {
        return !opt.has_value();
    }

    template<typename T>
    constexpr bool operator!=(const optional<T>& opt, nullopt_t) noexcept
    {
        return opt.has_value();
    }

    template<typename T>
    constexpr bool operator!=(nullopt_t, const optional<T>& opt) noexcept
    {
        return opt.has_value();
    }

    // Comparison with values
    template<typename T, typename U>
    constexpr bool operator==(const optional<T>& opt, const U& value)
    {
        return opt.has_value() && *opt == value;
    }

    template<typename T, typename U>
    constexpr bool operator==(const T& value, const optional<U>& opt)
    {
        return opt.has_value() && value == *opt;
    }

    template<typename T, typename U>
    constexpr bool operator!=(const optional<T>& opt, const U& value)
    {
        return !opt.has_value() || *opt != value;
    }

    template<typename T, typename U>
    constexpr bool operator!=(const T& value, const optional<U>& opt)
    {
        return !opt.has_value() || value != *opt;
    }

    // Utility functions
    template<typename T>
    void swap(optional<T>& lhs, optional<T>& rhs) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }

    template<typename T>
    constexpr optional<typename std::decay<T>::type> make_optional(T&& value)
    {
        return optional<typename std::decay<T>::type>(std::forward<T>(value));
    }

    template<typename T, typename... Args>
    constexpr optional<T> make_optional(Args&&... args)
    {
        return optional<T>(in_place, std::forward<Args>(args)...);
    }

} // namespace std

#endif
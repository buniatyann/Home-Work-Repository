#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <cstddef>
#include <utility>
#include <memory>
#include <type_traits>
#include <functional>
#include <ostream>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    using pointer = T*;
    using element_type = T;
    using deleter_type = Deleter;

    constexpr unique_ptr() noexcept;
    explicit unique_ptr(pointer p) noexcept;

    template <typename D>
    unique_ptr(pointer p, D&& d) noexcept;

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& rhs) noexcept;

    template <typename U, typename E>
    unique_ptr(unique_ptr<U, E>&& other) noexcept;

    unique_ptr& operator=(unique_ptr&& rhs) noexcept;

    template <typename U, typename E>
    unique_ptr& operator=(unique_ptr<U, E>&& other) noexcept;

    unique_ptr& operator=(std::nullptr_t) noexcept;
    ~unique_ptr();

    T& operator*() const noexcept;
    pointer operator->() const noexcept;

    pointer get() const noexcept;
    deleter_type& get_deleter() noexcept;
    const deleter_type& get_deleter() const noexcept;

    explicit operator bool() const noexcept;

    pointer release() noexcept;
    void reset(pointer p = nullptr) noexcept;
    void swap(unique_ptr& rhs) noexcept;

    friend bool operator==(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return lhs.resource_ == rhs.resource_;
    }

    friend bool operator==(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return lhs.resource_ == nullptr;
    }

    friend bool operator==(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return rhs.resource_ == nullptr;
    }

    friend bool operator!=(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return !(lhs == rhs);
    }

    friend bool operator!=(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return !(lhs == nullptr);
    }

    friend bool operator!=(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return !(nullptr == rhs);
    }

    friend bool operator<(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return std::less<pointer>()(lhs.resource_, rhs.resource_);
    }

    friend bool operator<(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return std::less<pointer>()(lhs.resource_, nullptr);
    }

    friend bool operator<(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return std::less<pointer>()(nullptr, rhs.resource_);
    }

    friend bool operator<=(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return !(rhs < lhs);
    }

    friend bool operator<=(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return !(nullptr < lhs);
    }

    friend bool operator<=(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return !(rhs < nullptr);
    }

    friend bool operator>(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return rhs < lhs;
    }

    friend bool operator>(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return nullptr < lhs;
    }

    friend bool operator>(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return rhs < nullptr;
    }

    friend bool operator>=(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return !(lhs < rhs);
    }

    friend bool operator>=(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return !(lhs < nullptr);
    }

    friend bool operator>=(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return !(nullptr < rhs);
    }

    friend void swap(unique_ptr& lhs, unique_ptr& rhs) noexcept {
        lhs.swap(rhs);
    }

    template <typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(
        std::basic_ostream<CharT, Traits>& os, const unique_ptr& ptr) {
        os << ptr.get();
        return os;
    }

private:
    pointer resource_;
    deleter_type deleter_;
};

// unique_ptr<T[]> partial specialization
template <typename T, typename Deleter>
class unique_ptr<T[], Deleter> {
public:
    using pointer = T*;
    using element_type = T;
    using deleter_type = Deleter;

    constexpr unique_ptr() noexcept;
    explicit unique_ptr(pointer p) noexcept;

    template <typename D>
    unique_ptr(pointer p, D&& d) noexcept;

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& rhs) noexcept;
    unique_ptr& operator=(unique_ptr&& rhs) noexcept;

    unique_ptr& operator=(std::nullptr_t) noexcept;
    ~unique_ptr();

    T& operator[](std::size_t index) const;

    pointer get() const noexcept;
    deleter_type& get_deleter() noexcept;
    const deleter_type& get_deleter() const noexcept;

    explicit operator bool() const noexcept;

    pointer release() noexcept;
    void reset(pointer p = nullptr) noexcept;
    void swap(unique_ptr& rhs) noexcept;

    friend bool operator==(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return lhs.resource_ == rhs.resource_;
    }

    friend bool operator==(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return lhs.resource_ == nullptr;
    }

    friend bool operator==(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return rhs.resource_ == nullptr;
    }

    friend bool operator!=(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return !(lhs == rhs);
    }

    friend bool operator!=(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return !(lhs == nullptr);
    }

    friend bool operator!=(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return !(nullptr == rhs);
    }

    friend bool operator<(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return std::less<pointer>()(lhs.resource_, rhs.resource_);
    }

    friend bool operator<=(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return !(rhs < lhs);
    }

    friend bool operator>(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return rhs < lhs;
    }

    friend bool operator>=(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return !(lhs < rhs);
    }

    friend void swap(unique_ptr& lhs, unique_ptr& rhs) noexcept {
        lhs.swap(rhs);
    }

private:
    pointer resource_;
    deleter_type deleter_;
};

template <typename T, typename... Args>
typename std::enable_if<!std::is_array<T>::value, unique_ptr<T>>::type
make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, unique_ptr<T>>::type
make_unique(std::size_t size) {
    using element = typename std::remove_extent<T>::type;
    return unique_ptr<T>(new element[size]());
}

template <typename T, typename... Args>
typename std::enable_if<std::extent<T>::value != 0>::type
make_unique(Args&&...) = delete;

template <typename T>
typename std::enable_if<!std::is_array<T>::value, unique_ptr<T>>::type
make_unique_for_overwrite() {
    return unique_ptr<T>(new T);
}

template <typename T>
typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, unique_ptr<T>>::type
make_unique_for_overwrite(std::size_t size) {
    using element = typename std::remove_extent<T>::type;
    return unique_ptr<T>(new element[size]);
}

template <typename T, typename... Args>
typename std::enable_if<std::extent<T>::value != 0>::type
make_unique_for_overwrite(Args&&...) = delete;

// std::hash specialization
// namespace std {
//     template <typename T, typename Deleter>
//     struct hash<::unique_ptr<T, Deleter>> {
//         std::size_t operator()(const ::unique_ptr<T, Deleter>& ptr) const noexcept {
//             return std::hash<typename ::unique_ptr<T, Deleter>::pointer>()(ptr.get());
//         }
//     };

//     template <typename T, typename Deleter>
//     struct hash<::unique_ptr<T[], Deleter>> {
//         std::size_t operator()(const ::unique_ptr<T[], Deleter>& ptr) const noexcept {
//             return std::hash<typename ::unique_ptr<T[], Deleter>::pointer>()(ptr.get());
//         }
//     };
// }

#include "unique_ptr.tpp"

#endif // UNIQUE_PTR_H

#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <memory>
#include <utility>
#include <cstddef>
#include <type_traits>
#include <algorithm>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    using pointer = T*;
    using element_type = T;
    using deleter_type = Deleter;

    constexpr unique_ptr() noexcept;
    explicit unique_ptr(pointer p) noexcept;

    template <typename D = Deleter>
    explicit unique_ptr(pointer p, D&& d) noexcept;

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& other) noexcept;
    unique_ptr& operator=(unique_ptr&& other) noexcept;

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
    void swap(unique_ptr& other) noexcept;

    template <typename U = T>
    auto& operator[](std::size_t index) const;

    friend bool operator==(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const unique_ptr& lhs, const unique_ptr& rhs) noexcept {
        return !(lhs == rhs);
    }

    friend bool operator==(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return !lhs.ptr_;
    }

    friend bool operator==(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return !rhs.ptr_;
    }

    friend bool operator!=(const unique_ptr& lhs, std::nullptr_t) noexcept {
        return lhs.ptr_ != nullptr;
    }

    friend bool operator!=(std::nullptr_t, const unique_ptr& rhs) noexcept {
        return rhs.ptr_ != nullptr;
    }

private:
    pointer ptr_ = nullptr;
    Deleter deleter_;
};

template <typename T, typename Deleter, typename... Args>
std::unique_ptr<T, Deleter> make_unique_with_deleter(Deleter&& deleter, Args&&... args) {
    return std::unique_ptr<T, Deleter>(
        new T(std::forward<Args>(args)...),
        std::forward<Deleter>(deleter)
    );
}

#include "unique_ptr.tpp"

#endif // UNIQUE_PTR_HPP
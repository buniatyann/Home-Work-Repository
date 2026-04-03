#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <utility>
#include <memory>
#include <type_traits>
#include <functional>
#include <ostream>
#include <atomic>
#include <stdexcept>

namespace detail {

class control_block_base {
public:
    std::atomic<std::size_t> strong_count_;
    std::atomic<std::size_t> weak_count_;

    control_block_base() noexcept;
    virtual ~control_block_base();
    virtual void destroy_resource() noexcept = 0;

    void increment_strong() noexcept;
    void increment_weak() noexcept;
    void decrement_strong() noexcept;
    void decrement_weak() noexcept;
    std::size_t use_count() const noexcept;
};

template <typename T, typename Deleter>
class control_block : public control_block_base {
public:
    T* resource_;
    Deleter deleter_;

    control_block(T* p, Deleter d);
    ~control_block() override = default;
    void destroy_resource() noexcept override;
};

struct for_overwrite_tag {};

template <typename T>
class control_block_inplace : public control_block_base {
public:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage_;
    bool constructed_;

    template <typename... Args>
    explicit control_block_inplace(Args&&... args);

    explicit control_block_inplace(for_overwrite_tag);

    ~control_block_inplace() override = default;
    void destroy_resource() noexcept override;

    T* get() noexcept;
};

} // namespace detail

template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
public:
    using pointer = T*;
    using element_type = T;

    constexpr shared_ptr() noexcept;
    constexpr shared_ptr(std::nullptr_t) noexcept;

    explicit shared_ptr(pointer p);

    template <typename Deleter>
    shared_ptr(pointer p, Deleter d);

    shared_ptr(const shared_ptr& other) noexcept;

    template <typename U>
    shared_ptr(const shared_ptr<U>& other) noexcept;

    shared_ptr(shared_ptr&& other) noexcept;

    template <typename U>
    shared_ptr(shared_ptr<U>&& other) noexcept;

    template <typename U>
    shared_ptr(const shared_ptr<U>& owner, element_type* ptr) noexcept;

    explicit shared_ptr(const weak_ptr<T>& wp);

    template <typename U, typename Deleter>
    shared_ptr(std::unique_ptr<U, Deleter>&& uptr);

    ~shared_ptr();

    shared_ptr& operator=(const shared_ptr& other) noexcept;

    template <typename U>
    shared_ptr& operator=(const shared_ptr<U>& other) noexcept;

    shared_ptr& operator=(shared_ptr&& other) noexcept;

    template <typename U>
    shared_ptr& operator=(shared_ptr<U>&& other) noexcept;

    shared_ptr& operator=(std::nullptr_t) noexcept;

    template <typename U, typename Deleter>
    shared_ptr& operator=(std::unique_ptr<U, Deleter>&& uptr);

    T& operator*() const noexcept;
    pointer operator->() const noexcept;

    pointer get() const noexcept;
    std::size_t use_count() const noexcept;
    bool unique() const noexcept;

    explicit operator bool() const noexcept;

    void reset() noexcept;
    void reset(pointer p);

    template <typename Deleter>
    void reset(pointer p, Deleter d);

    void swap(shared_ptr& other) noexcept;

    friend bool operator==(const shared_ptr& lhs, const shared_ptr& rhs) noexcept {
        return lhs.resource_ == rhs.resource_;
    }

    friend bool operator==(const shared_ptr& lhs, std::nullptr_t) noexcept {
        return lhs.resource_ == nullptr;
    }

    friend bool operator==(std::nullptr_t, const shared_ptr& rhs) noexcept {
        return rhs.resource_ == nullptr;
    }

    friend bool operator!=(const shared_ptr& lhs, const shared_ptr& rhs) noexcept {
        return !(lhs == rhs);
    }

    friend bool operator!=(const shared_ptr& lhs, std::nullptr_t) noexcept {
        return !(lhs == nullptr);
    }

    friend bool operator!=(std::nullptr_t, const shared_ptr& rhs) noexcept {
        return !(nullptr == rhs);
    }

    friend bool operator<(const shared_ptr& lhs, const shared_ptr& rhs) noexcept {
        return std::less<pointer>()(lhs.resource_, rhs.resource_);
    }

    friend bool operator<(const shared_ptr& lhs, std::nullptr_t) noexcept {
        return std::less<pointer>()(lhs.resource_, nullptr);
    }

    friend bool operator<(std::nullptr_t, const shared_ptr& rhs) noexcept {
        return std::less<pointer>()(nullptr, rhs.resource_);
    }

    friend bool operator<=(const shared_ptr& lhs, const shared_ptr& rhs) noexcept {
        return !(rhs < lhs);
    }

    friend bool operator<=(const shared_ptr& lhs, std::nullptr_t) noexcept {
        return !(nullptr < lhs);
    }

    friend bool operator<=(std::nullptr_t, const shared_ptr& rhs) noexcept {
        return !(rhs < nullptr);
    }

    friend bool operator>(const shared_ptr& lhs, const shared_ptr& rhs) noexcept {
        return rhs < lhs;
    }

    friend bool operator>(const shared_ptr& lhs, std::nullptr_t) noexcept {
        return nullptr < lhs;
    }

    friend bool operator>(std::nullptr_t, const shared_ptr& rhs) noexcept {
        return rhs < nullptr;
    }

    friend bool operator>=(const shared_ptr& lhs, const shared_ptr& rhs) noexcept {
        return !(lhs < rhs);
    }

    friend bool operator>=(const shared_ptr& lhs, std::nullptr_t) noexcept {
        return !(lhs < nullptr);
    }

    friend bool operator>=(std::nullptr_t, const shared_ptr& rhs) noexcept {
        return !(nullptr < rhs);
    }

    friend void swap(shared_ptr& lhs, shared_ptr& rhs) noexcept {
        lhs.swap(rhs);
    }

    template <typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(
        std::basic_ostream<CharT, Traits>& os, const shared_ptr& ptr) {
        os << ptr.get();
        return os;
    }

private:
    pointer resource_;
    detail::control_block_base* control_;

    shared_ptr(pointer p, detail::control_block_base* cb) noexcept;

    template <typename U>
    friend class shared_ptr;

    template <typename U>
    friend class weak_ptr;

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);

    template <typename U>
    friend shared_ptr<U> make_shared_for_overwrite();

    template <typename To, typename From>
    friend shared_ptr<To> static_pointer_cast(const shared_ptr<From>& r) noexcept;

    template <typename To, typename From>
    friend shared_ptr<To> dynamic_pointer_cast(const shared_ptr<From>& r) noexcept;

    template <typename To, typename From>
    friend shared_ptr<To> const_pointer_cast(const shared_ptr<From>& r) noexcept;
};

template <typename T>
class weak_ptr {
public:
    using element_type = T;

    constexpr weak_ptr() noexcept;

    weak_ptr(const weak_ptr& other) noexcept;

    template <typename U>
    weak_ptr(const weak_ptr<U>& other) noexcept;

    template <typename U>
    weak_ptr(const shared_ptr<U>& sp) noexcept;

    weak_ptr(weak_ptr&& other) noexcept;

    template <typename U>
    weak_ptr(weak_ptr<U>&& other) noexcept;

    ~weak_ptr();

    weak_ptr& operator=(const weak_ptr& other) noexcept;

    template <typename U>
    weak_ptr& operator=(const weak_ptr<U>& other) noexcept;

    template <typename U>
    weak_ptr& operator=(const shared_ptr<U>& sp) noexcept;

    weak_ptr& operator=(weak_ptr&& other) noexcept;

    template <typename U>
    weak_ptr& operator=(weak_ptr<U>&& other) noexcept;

    std::size_t use_count() const noexcept;
    bool expired() const noexcept;
    shared_ptr<T> lock() const noexcept;

    void reset() noexcept;
    void swap(weak_ptr& other) noexcept;

    friend void swap(weak_ptr& lhs, weak_ptr& rhs) noexcept {
        lhs.swap(rhs);
    }

private:
    T* resource_;
    detail::control_block_base* control_;

    template <typename U>
    friend class shared_ptr;

    template <typename U>
    friend class weak_ptr;
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args);

template <typename T>
shared_ptr<T> make_shared_for_overwrite();

template <typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U>& r) noexcept;

template <typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& r) noexcept;

template <typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U>& r) noexcept;

#include "shared_ptr.tpp"

#endif // SHARED_PTR_HPP

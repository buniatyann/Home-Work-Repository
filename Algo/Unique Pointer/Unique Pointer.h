#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <cstddef>
#include <utility>
#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    using pointer = T*;
    using element_type = T;
    using deleter_type = Deleter;

    constexpr unique_ptr() noexcept : resource_(nullptr), deleter_(Deleter{}) {}
    explicit unique_ptr(pointer p) noexcept : resource_(p), deleter_(Deleter{}) {}
    template <typename D>
    unique_ptr(pointer p, D&& d) noexcept : resource_(p), deleter_(std::forward<D>(d)) {}

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& rhs) noexcept : resource_(rhs.resource_), deleter_(std::move(rhs.deleter_)) {
        rhs.resource_ = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& rhs) noexcept {
        if (this != &rhs) {
            reset();
            resource_ = rhs.resource_;
            deleter_ = std::move(rhs.deleter_);
            rhs.resource_ = nullptr;
        }

        return *this;
    }

    unique_ptr& operator=(std::nullptr_t) noexcept {
        reset();
        return *this;
    }

    ~unique_ptr() {
        reset();
    }

    T& operator*() const noexcept { 
        return *resource_; 
    }
    
    pointer operator->() const noexcept { 
        return resource_; 
    }

    pointer get() const noexcept { 
        return resource_; 
    }
    
    deleter_type& get_deleter() noexcept { 
        return deleter_; 
    }
    
    const deleter_type& get_deleter() const noexcept { 
        return deleter_; 
    }
    
    explicit operator bool() const noexcept { 
        return resource_ != nullptr; 
    }

    pointer release() noexcept {
        pointer temp = resource_;
        resource_ = nullptr;
        return temp;
    }

    void reset(pointer p = nullptr) noexcept {
        pointer old = resource_;
        resource_ = p;
        if (old) {
            deleter_(old);
        }
    }

    void swap(unique_ptr& rhs) noexcept {
        std::swap(resource_, rhs.resource_);
        std::swap(deleter_, rhs.deleter_);
    }

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

    friend void swap(unique_ptr& lhs, unique_ptr& rhs) noexcept {
        lhs.swap(rhs);
    }

private:
    pointer resource_;
    deleter_type deleter_;
};

#endif // UNIQUE_PTR_H
#include "unique_ptr.hpp"

template <typename T, typename D>
constexpr unique_ptr<T, D>::unique_ptr() noexcept = default;

template <typename T, typename D>
unique_ptr<T, D>::unique_ptr(pointer p) noexcept : ptr_(p) {}

template <typename T, typename D>
template <typename D2>
unique_ptr<T, D>::unique_ptr(pointer p, D2&& d) noexcept
    : ptr_(p), deleter_(std::forward<D2>(d)) {}

template <typename T, typename D>
unique_ptr<T, D>::unique_ptr(unique_ptr&& other) noexcept
    : ptr_(other.ptr_), deleter_(std::move(other.deleter_)) {
    other.ptr_ = nullptr;
}

template <typename T, typename D>
unique_ptr<T, D>& unique_ptr<T, D>::operator=(unique_ptr&& other) noexcept {
    if (this != &other) {
        reset();
        ptr_ = other.ptr_;
        deleter_ = std::move(other.deleter_);
        other.ptr_ = nullptr;
    }

    return *this;
}

template <typename T, typename D>
unique_ptr<T, D>& unique_ptr<T, D>::operator=(std::nullptr_t) noexcept {
    reset();
    return *this;
}

template <typename T, typename D>
unique_ptr<T, D>::~unique_ptr() {
    reset();
}

template <typename T, typename D>
T& unique_ptr<T, D>::operator*() const noexcept {
    return *ptr_;
}

template <typename T, typename D>
typename unique_ptr<T, D>::pointer unique_ptr<T, D>::operator->() const noexcept {
    return ptr_;
}

template <typename T, typename D>
typename unique_ptr<T, D>::pointer unique_ptr<T, D>::get() const noexcept {
    return ptr_;
}

template <typename T, typename D>
typename unique_ptr<T, D>::deleter_type& unique_ptr<T, D>::get_deleter() noexcept {
    return deleter_;
}

template <typename T, typename D>
const typename unique_ptr<T, D>::deleter_type& unique_ptr<T, D>::get_deleter() const noexcept {
    return deleter_;
}

template <typename T, typename D>
unique_ptr<T, D>::operator bool() const noexcept {
    return ptr_ != nullptr;
}

template <typename T, typename D>
typename unique_ptr<T, D>::pointer unique_ptr<T, D>::release() noexcept {
    pointer temp = ptr_;
    ptr_ = nullptr;
    
    return temp;
}

template <typename T, typename D>
void unique_ptr<T, D>::reset(pointer p) noexcept {
    if (ptr_ != p) {
        if (ptr_) {
            deleter_(ptr_);
        }
    
        ptr_ = p;
    }
}

template <typename T, typename D>
void unique_ptr<T, D>::swap(unique_ptr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(deleter_, other.deleter_);
}

template <typename T, typename D>
template <typename U>
auto& unique_ptr<T, D>::operator[](std::size_t index) const {
    static_assert(std::is_array_v<U>, "operator[] is only valid for array types");
    return ptr_[index];
}

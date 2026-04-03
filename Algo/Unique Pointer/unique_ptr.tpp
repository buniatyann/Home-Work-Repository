#include "unique_ptr.h"

// --- unique_ptr<T, Deleter> (scalar) ---

template <typename T, typename D>
constexpr unique_ptr<T, D>::unique_ptr() noexcept : resource_(nullptr), deleter_(D{}) {}

template <typename T, typename D>
unique_ptr<T, D>::unique_ptr(pointer p) noexcept : resource_(p), deleter_(D{}) {}

template <typename T, typename D>
template <typename D2>
unique_ptr<T, D>::unique_ptr(pointer p, D2&& d) noexcept
    : resource_(p), deleter_(std::forward<D2>(d)) {}

template <typename T, typename D>
unique_ptr<T, D>::unique_ptr(unique_ptr&& rhs) noexcept
    : resource_(rhs.resource_), deleter_(std::move(rhs.deleter_)) {
    rhs.resource_ = nullptr;
}

template <typename T, typename D>
template <typename U, typename E>
unique_ptr<T, D>::unique_ptr(unique_ptr<U, E>&& other) noexcept
    : resource_(other.release()), deleter_(std::forward<E>(other.get_deleter())) {
    static_assert(std::is_convertible<typename unique_ptr<U, E>::pointer, pointer>::value,
        "U* must be convertible to T*");
}

template <typename T, typename D>
unique_ptr<T, D>& unique_ptr<T, D>::operator=(unique_ptr&& rhs) noexcept {
    if (this != &rhs) {
        reset();
        resource_ = rhs.resource_;
        deleter_ = std::move(rhs.deleter_);
        rhs.resource_ = nullptr;
    }

    return *this;
}

template <typename T, typename D>
template <typename U, typename E>
unique_ptr<T, D>& unique_ptr<T, D>::operator=(unique_ptr<U, E>&& other) noexcept {
    static_assert(std::is_convertible<typename unique_ptr<U, E>::pointer, pointer>::value,
        "U* must be convertible to T*");
    reset(other.release());
    deleter_ = std::forward<E>(other.get_deleter());
    
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
    return *resource_;
}

template <typename T, typename D>
typename unique_ptr<T, D>::pointer unique_ptr<T, D>::operator->() const noexcept {
    return resource_;
}

template <typename T, typename D>
typename unique_ptr<T, D>::pointer unique_ptr<T, D>::get() const noexcept {
    return resource_;
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
    return resource_ != nullptr;
}

template <typename T, typename D>
typename unique_ptr<T, D>::pointer unique_ptr<T, D>::release() noexcept {
    pointer temp = resource_;
    resource_ = nullptr;
    
    return temp;
}

template <typename T, typename D>
void unique_ptr<T, D>::reset(pointer p) noexcept {
    pointer old = resource_;
    resource_ = p;
    if (old) {
        deleter_(old);
    }
}

template <typename T, typename D>
void unique_ptr<T, D>::swap(unique_ptr& rhs) noexcept {
    std::swap(resource_, rhs.resource_);
    std::swap(deleter_, rhs.deleter_);
}

// --- unique_ptr<T[], Deleter> (array specialization) ---

template <typename T, typename D>
constexpr unique_ptr<T[], D>::unique_ptr() noexcept : resource_(nullptr), deleter_(D{}) {}

template <typename T, typename D>
unique_ptr<T[], D>::unique_ptr(pointer p) noexcept : resource_(p), deleter_(D{}) {}

template <typename T, typename D>
template <typename D2>
unique_ptr<T[], D>::unique_ptr(pointer p, D2&& d) noexcept
    : resource_(p), deleter_(std::forward<D2>(d)) {}

template <typename T, typename D>
unique_ptr<T[], D>::unique_ptr(unique_ptr&& rhs) noexcept
    : resource_(rhs.resource_), deleter_(std::move(rhs.deleter_)) {
    rhs.resource_ = nullptr;
}

template <typename T, typename D>
unique_ptr<T[], D>& unique_ptr<T[], D>::operator=(unique_ptr&& rhs) noexcept {
    if (this != &rhs) {
        reset();
        resource_ = rhs.resource_;
        deleter_ = std::move(rhs.deleter_);
        rhs.resource_ = nullptr;
    }

    return *this;
}

template <typename T, typename D>
unique_ptr<T[], D>& unique_ptr<T[], D>::operator=(std::nullptr_t) noexcept {
    reset();
    return *this;
}

template <typename T, typename D>
unique_ptr<T[], D>::~unique_ptr() {
    reset();
}

template <typename T, typename D>
T& unique_ptr<T[], D>::operator[](std::size_t index) const {
    return resource_[index];
}

template <typename T, typename D>
typename unique_ptr<T[], D>::pointer unique_ptr<T[], D>::get() const noexcept {
    return resource_;
}

template <typename T, typename D>
typename unique_ptr<T[], D>::deleter_type& unique_ptr<T[], D>::get_deleter() noexcept {
    return deleter_;
}

template <typename T, typename D>
const typename unique_ptr<T[], D>::deleter_type& unique_ptr<T[], D>::get_deleter() const noexcept {
    return deleter_;
}

template <typename T, typename D>
unique_ptr<T[], D>::operator bool() const noexcept {
    return resource_ != nullptr;
}

template <typename T, typename D>
typename unique_ptr<T[], D>::pointer unique_ptr<T[], D>::release() noexcept {
    pointer temp = resource_;
    resource_ = nullptr;
    return temp;
}

template <typename T, typename D>
void unique_ptr<T[], D>::reset(pointer p) noexcept {
    pointer old = resource_;
    resource_ = p;
    if (old) {
        deleter_(old);
    }
}

template <typename T, typename D>
void unique_ptr<T[], D>::swap(unique_ptr& rhs) noexcept {
    std::swap(resource_, rhs.resource_);
    std::swap(deleter_, rhs.deleter_);
}

#include "shared_ptr.hpp"

// --- detail::control_block_base ---

inline detail::control_block_base::control_block_base() noexcept
    : strong_count_(1), weak_count_(1) {}

inline detail::control_block_base::~control_block_base() {}

inline void detail::control_block_base::increment_strong() noexcept {
    strong_count_.fetch_add(1, std::memory_order_relaxed);
}

inline void detail::control_block_base::increment_weak() noexcept {
    weak_count_.fetch_add(1, std::memory_order_relaxed);
}

inline void detail::control_block_base::decrement_strong() noexcept {
    if (strong_count_.fetch_sub(1, std::memory_order_acq_rel) == 1) {
        destroy_resource();
        decrement_weak();
    }
}

inline void detail::control_block_base::decrement_weak() noexcept {
    if (weak_count_.fetch_sub(1, std::memory_order_acq_rel) == 1) {
        delete this;
    }
}

inline std::size_t detail::control_block_base::use_count() const noexcept {
    return strong_count_.load(std::memory_order_relaxed);
}

// --- detail::control_block<T, Deleter> ---

template <typename T, typename Deleter>
detail::control_block<T, Deleter>::control_block(T* p, Deleter d)
    : control_block_base(), resource_(p), deleter_(std::move(d)) {}

template <typename T, typename Deleter>
void detail::control_block<T, Deleter>::destroy_resource() noexcept {
    if (resource_) {
        deleter_(resource_);
        resource_ = nullptr;
    }
}

// --- detail::control_block_inplace<T> ---

template <typename T>
template <typename... Args>
detail::control_block_inplace<T>::control_block_inplace(Args&&... args)
    : control_block_base(), constructed_(true) {
    new (&storage_) T(std::forward<Args>(args)...);
}

template <typename T>
detail::control_block_inplace<T>::control_block_inplace(for_overwrite_tag)
    : control_block_base(), constructed_(true) {
    new (&storage_) T;
}

template <typename T>
void detail::control_block_inplace<T>::destroy_resource() noexcept {
    if (constructed_) {
        get()->~T();
        constructed_ = false;
    }
}

template <typename T>
T* detail::control_block_inplace<T>::get() noexcept {
    return reinterpret_cast<T*>(&storage_);
}

// --- shared_ptr<T> ---

// Private constructor (no increment — caller must have already accounted for the reference)
template <typename T>
shared_ptr<T>::shared_ptr(pointer p, detail::control_block_base* cb) noexcept
    : resource_(p), control_(cb) {}

template <typename T>
constexpr shared_ptr<T>::shared_ptr() noexcept : resource_(nullptr), control_(nullptr) {}

template <typename T>
constexpr shared_ptr<T>::shared_ptr(std::nullptr_t) noexcept : resource_(nullptr), control_(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(pointer p)
    : resource_(p), control_(nullptr) {
    if (p) {
        try {
            control_ = new detail::control_block<T, std::default_delete<T>>(p, std::default_delete<T>{});
        } catch (...) {
            delete p;
            throw;
        }
    }
}

template <typename T>
template <typename Deleter>
shared_ptr<T>::shared_ptr(pointer p, Deleter d)
    : resource_(p), control_(nullptr) {
    if (p) {
        try {
            control_ = new detail::control_block<T, Deleter>(p, std::move(d));
        } catch (...) {
            d(p);
            throw;
        }
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    if (control_) {
        control_->increment_strong();
    }
}

template <typename T>
template <typename U>
shared_ptr<T>::shared_ptr(const shared_ptr<U>& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    static_assert(std::is_convertible<U*, T*>::value, "U* must be convertible to T*");
    if (control_) {
        control_->increment_strong();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    other.resource_ = nullptr;
    other.control_ = nullptr;
}

template <typename T>
template <typename U>
shared_ptr<T>::shared_ptr(shared_ptr<U>&& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    static_assert(std::is_convertible<U*, T*>::value, "U* must be convertible to T*");
    other.resource_ = nullptr;
    other.control_ = nullptr;
}

template <typename T>
template <typename U>
shared_ptr<T>::shared_ptr(const shared_ptr<U>& owner, element_type* ptr) noexcept
    : resource_(ptr), control_(owner.control_) {
    if (control_) {
        control_->increment_strong();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const weak_ptr<T>& wp)
    : resource_(nullptr), control_(nullptr) {
    if (wp.expired()) {
        throw std::bad_weak_ptr();
    }
    resource_ = wp.resource_;
    control_ = wp.control_;
    control_->increment_strong();
}

template <typename T>
template <typename U, typename Deleter>
shared_ptr<T>::shared_ptr(std::unique_ptr<U, Deleter>&& uptr)
    : resource_(nullptr), control_(nullptr) {
    if (uptr) {
        pointer p = uptr.get();
        control_ = new detail::control_block<U, Deleter>(p, uptr.get_deleter());
        resource_ = p;
        uptr.release();
    }
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    if (control_) {
        control_->decrement_strong();
    }
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& other) noexcept {
    shared_ptr(other).swap(*this);
    return *this;
}

template <typename T>
template <typename U>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<U>& other) noexcept {
    shared_ptr(other).swap(*this);
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other) noexcept {
    shared_ptr(std::move(other)).swap(*this);
    return *this;
}

template <typename T>
template <typename U>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<U>&& other) noexcept {
    shared_ptr(std::move(other)).swap(*this);
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(std::nullptr_t) noexcept {
    reset();
    return *this;
}

template <typename T>
template <typename U, typename Deleter>
shared_ptr<T>& shared_ptr<T>::operator=(std::unique_ptr<U, Deleter>&& uptr) {
    shared_ptr(std::move(uptr)).swap(*this);
    return *this;
}

template <typename T>
T& shared_ptr<T>::operator*() const noexcept {
    return *resource_;
}

template <typename T>
typename shared_ptr<T>::pointer shared_ptr<T>::operator->() const noexcept {
    return resource_;
}

template <typename T>
typename shared_ptr<T>::pointer shared_ptr<T>::get() const noexcept {
    return resource_;
}

template <typename T>
std::size_t shared_ptr<T>::use_count() const noexcept {
    return control_ ? control_->use_count() : 0;
}

template <typename T>
bool shared_ptr<T>::unique() const noexcept {
    return use_count() == 1;
}

template <typename T>
shared_ptr<T>::operator bool() const noexcept {
    return resource_ != nullptr;
}

template <typename T>
void shared_ptr<T>::reset() noexcept {
    shared_ptr().swap(*this);
}

template <typename T>
void shared_ptr<T>::reset(pointer p) {
    shared_ptr(p).swap(*this);
}

template <typename T>
template <typename Deleter>
void shared_ptr<T>::reset(pointer p, Deleter d) {
    shared_ptr(p, std::move(d)).swap(*this);
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr& other) noexcept {
    std::swap(resource_, other.resource_);
    std::swap(control_, other.control_);
}

// --- weak_ptr<T> ---

template <typename T>
constexpr weak_ptr<T>::weak_ptr() noexcept : resource_(nullptr), control_(nullptr) {}

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    if (control_) {
        control_->increment_weak();
    }
}

template <typename T>
template <typename U>
weak_ptr<T>::weak_ptr(const weak_ptr<U>& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    static_assert(std::is_convertible<U*, T*>::value, "U* must be convertible to T*");
    if (control_) {
        control_->increment_weak();
    }
}

template <typename T>
template <typename U>
weak_ptr<T>::weak_ptr(const shared_ptr<U>& sp) noexcept
    : resource_(sp.resource_), control_(sp.control_) {
    static_assert(std::is_convertible<U*, T*>::value, "U* must be convertible to T*");
    if (control_) {
        control_->increment_weak();
    }
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr&& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    other.resource_ = nullptr;
    other.control_ = nullptr;
}

template <typename T>
template <typename U>
weak_ptr<T>::weak_ptr(weak_ptr<U>&& other) noexcept
    : resource_(other.resource_), control_(other.control_) {
    static_assert(std::is_convertible<U*, T*>::value, "U* must be convertible to T*");
    other.resource_ = nullptr;
    other.control_ = nullptr;
}

template <typename T>
weak_ptr<T>::~weak_ptr() {
    if (control_) {
        control_->decrement_weak();
    }
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr& other) noexcept {
    weak_ptr(other).swap(*this);
    return *this;
}

template <typename T>
template <typename U>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr<U>& other) noexcept {
    weak_ptr(other).swap(*this);
    return *this;
}

template <typename T>
template <typename U>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<U>& sp) noexcept {
    weak_ptr(sp).swap(*this);
    return *this;
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr&& other) noexcept {
    weak_ptr(std::move(other)).swap(*this);
    return *this;
}

template <typename T>
template <typename U>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr<U>&& other) noexcept {
    weak_ptr(std::move(other)).swap(*this);
    return *this;
}

template <typename T>
std::size_t weak_ptr<T>::use_count() const noexcept {
    return control_ ? control_->use_count() : 0;
}

template <typename T>
bool weak_ptr<T>::expired() const noexcept {
    return use_count() == 0;
}

template <typename T>
shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    if (expired()) {
        return shared_ptr<T>();
    }

    control_->increment_strong();
    return shared_ptr<T>(resource_, control_);
}

template <typename T>
void weak_ptr<T>::reset() noexcept {
    weak_ptr().swap(*this);
}

template <typename T>
void weak_ptr<T>::swap(weak_ptr& other) noexcept {
    std::swap(resource_, other.resource_);
    std::swap(control_, other.control_);
}

// --- Free functions ---

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    auto* cb = new detail::control_block_inplace<T>(std::forward<Args>(args)...);
    shared_ptr<T> sp;
    sp.resource_ = cb->get();
    sp.control_ = cb;

    return sp;
}

template <typename T>
shared_ptr<T> make_shared_for_overwrite() {
    auto* cb = new detail::control_block_inplace<T>(detail::for_overwrite_tag{});
    shared_ptr<T> sp;
    sp.resource_ = cb->get();
    sp.control_ = cb;

    return sp;
}

template <typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U>& r) noexcept {
    auto p = static_cast<T*>(r.get());
    if (r.control_) {
        r.control_->increment_strong();
    }

    return shared_ptr<T>(p, r.control_);
}

template <typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& r) noexcept {
    auto p = dynamic_cast<T*>(r.get());
    if (p && r.control_) {
        r.control_->increment_strong();
    }

    return shared_ptr<T>(p, p ? r.control_ : nullptr);
}

template <typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U>& r) noexcept {
    auto p = const_cast<T*>(r.get());
    if (r.control_) {
        r.control_->increment_strong();
    }

    return shared_ptr<T>(p, r.control_);
}

#include "Optional.hpp"

namespace hw {

template <typename T>
void Optional<T>::destroy() noexcept(std::is_nothrow_destructible_v<value_type>) {
    if(engaged) {
        storage.value.~value_type();
        engaged = false;
    }
}

template <typename T>
constexpr Optional<T>::Optional() noexcept : engaged(false) {}

template <typename T>
constexpr Optional<T>::Optional(nullopt_t) noexcept : engaged(false) {}

template <typename T>
template <typename U, typename>
constexpr Optional<T>::Optional(U&& val) : engaged(true) {
    new (&storage.value) value_type(std::forward<U>(val));
}

template <typename T>
Optional<T>::Optional(const Optional& rhs) : engaged(rhs.engaged) {
    if(rhs.engaged) {
        new (&storage.value) value_type(rhs.storage.value);
    }
}

template <typename T>
Optional<T>::Optional(Optional&& rhs) noexcept(std::is_nothrow_move_constructible_v<T>)
    : engaged(rhs.engaged) {
    if(rhs.engaged) {
        new (&storage.value) value_type(std::move(rhs.storage.value));
        rhs.engaged = false;
    }
}

template <typename T>
Optional<T>& Optional<T>::operator=(const Optional& rhs) {
    if(this != &rhs) {
        Optional temp(rhs);
        destroy();
        engaged = temp.engaged;
        
        if(temp.engaged) {
            new (&storage.value) value_type(std::move(temp.storage.value));
            temp.engaged = false;
        }
    }

    return *this;
}

template <typename T>
Optional<T>& Optional<T>::operator=(Optional&& rhs) noexcept(std::is_nothrow_move_assignable_v<T>) {
    if (this != &rhs) {
        destroy();
        engaged = rhs.engaged;
        
        if (rhs.engaged) {
            new (&storage.value) value_type(std::move(rhs.storage.value));
            rhs.engaged = false;
        }
    }

    return *this;
}

template <typename T>
Optional<T>::~Optional() { 
    destroy(); 
}

template <typename T>
constexpr bool Optional<T>::has_value() const noexcept { 
    return engaged;
}

// template <typename T>
// constexpr explicit operator bool() const noexcept { 
//     return engaged; 
// }

template <typename T>
constexpr  Optional<T>::operator bool() const noexcept { 
    return engaged; 
}

template <typename T>
Optional<T>::value_type& Optional<T>::operator*() {
    if(!engaged) {
        throw std::logic_error("No value");
    }
    
    return storage.value;
}

template <typename T>
const Optional<T>::value_type& Optional<T>::operator*() const {
    if (!engaged) {
        throw std::logic_error("No value");
    }
    
    return storage.value;
}

template <typename T>
Optional<T>::value_type* Optional<T>::operator->() {
    if (!engaged) {
        throw std::logic_error("No value");
    }
    
    return &storage.value;
}

template <typename T>
const Optional<T>::value_type* Optional<T>::operator->() const {
    if (!engaged) {
        throw std::logic_error("No value");
    }
    
    return &storage.value;
}

template <typename T>
template <typename U>
Optional<T>::value_type Optional<T>::value_or(U&& default_value) const& {
    return engaged ? storage.value : static_cast<value_type>(std::forward<U>(default_value));
}

template <typename T>
template <typename U>
Optional<T>::value_type Optional<T>::value_or(U&& default_value) && {
    return engaged ? std::move(storage.value) : static_cast<value_type>(std::forward<U>(default_value));
}

template <typename T>
Optional<T>& Optional<T>::emplace(T&& value) {
    destroy();
    new (&storage.value) value_type(std::forward<T>(value));
    engaged = true;
    
    return *this;
}

template <typename T>
template <typename Func>
Optional<std::remove_reference_t<std::invoke_result_t<Func, const T&>>> Optional<T>::map(Func&& func) const& {
    using ReturnType = std::invoke_result_t<Func, const T&>;
    if (engaged) {
        return Optional<std::remove_reference_t<ReturnType>>(func(storage.value));
    }
    
    return Optional<std::remove_reference_t<ReturnType>>{};
}

template <typename T>
template <typename Func>
Optional<std::remove_reference_t<std::invoke_result_t<Func, T&&>>> Optional<T>::map(Func&& func) && {
    using ReturnType = std::invoke_result_t<Func, T&&>;
    if (engaged) {
        return Optional<std::remove_reference_t<ReturnType>>(std::forward<Func>(func)(std::move(storage.value)));
    }
    
    return Optional<std::remove_reference_t<ReturnType>>{};
}

template <typename T>
template <typename Func>
Optional<std::remove_reference_t<std::invoke_result_t<Func, const T&>>> Optional<T>::and_then(Func&& func) const& {
    using ReturnType = std::invoke_result_t<Func, const T&>;
    if (engaged) {
        return func(storage.value);
    }
    
    return Optional<std::remove_reference_t<ReturnType>>{};
}

template <typename T>
template <typename Func>
Optional<std::remove_reference_t<std::invoke_result_t<Func, T&&>>> Optional<T>::and_then(Func&& func) && {
    using ReturnType = std::invoke_result_t<Func, T&&>;
    if(engaged) {
        return func(std::move(storage.value));
    }
    
    return Optional<std::remove_reference_t<ReturnType>>{};
}

template <typename T>
bool operator==(const Optional<T>& lhs, const Optional<T>& rhs) {
    if(lhs.engaged != rhs.engaged){
        return false;
    }
    if(!lhs.engaged){
        return true;
    }
    
    return lhs.storage.value == rhs.storage.value;
}

template <typename T>
bool operator!=(const Optional<T>& lhs, const Optional<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator==(const Optional<T>& lhs, nullopt_t) {
    return !lhs.engaged;
}

template <typename T>
bool operator!=(const Optional<T>& lhs, nullopt_t) {
    return lhs.engaged;
}


template <typename T, typename... Args>
constexpr Optional<T> make_optional(Args&&... args) {
    return Optional<T>(T(std::forward<Args>(args)...));
}
    
} // namespace hw

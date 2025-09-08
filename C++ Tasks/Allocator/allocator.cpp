#include "allocator.hpp"
#include <new>          // For placement new
#include <stdexcept>    // For std::bad_alloc

// Address functions
template <typename T>
typename Allocator<T>::pointer Allocator<T>::address(reference x) const noexcept {
    return &x;
}

template <typename T>
typename Allocator<T>::const_pointer Allocator<T>::address(const_reference x) const noexcept {
    return &x;
}

// Allocate function
template <typename T>
typename Allocator<T>::pointer Allocator<T>::allocate(size_type n, const void* hint) {
    if (n == 0) {
        return nullptr;
    }

    void* ptr = ::operator new(n * sizeof(T));
    if (!ptr) {
        throw std::bad_alloc();
    }

    return static_cast<pointer>(ptr);
}

// Deallocate function
template <typename T>
void Allocator<T>::deallocate(pointer p, size_type n) {
    if (p != nullptr) {
        ::operator delete(static_cast<void*>(p)); 
    }
}

// Construct function (single object)
template <typename T>
void Allocator<T>::construct(pointer p, const_reference val) {
    new (static_cast<void*>(p)) T(val);  
}

// Construct function (variadic arguments)
template <typename T>
template <typename U, typename... Args>
void Allocator<T>::construct(U* p, Args&&... args) {
    new (static_cast<void*>(p)) U(std::forward<Args>(args)...);  
}

// Destruct function (single object)
template <typename T>
void Allocator<T>::destruct(pointer p) {
    p->~T(); 
}

// Destruct function (for different type U)
template <typename T>
template <typename U>
void Allocator<T>::destruct(U* p) {
    p->~U(); 
}


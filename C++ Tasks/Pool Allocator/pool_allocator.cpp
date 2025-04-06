#include "pool_allocator.hpp"

template <typename T, typename Alloc>
pool_allocator<T, Alloc>::pool_allocator(memory_pool<T>& pool) noexcept
    : pool_(pool) {}

template <typename T, typename Alloc>
template <typename U>
pool_allocator<T, Alloc>::pool_allocator(const pool_allocator<U, Alloc>& other) noexcept
    : pool_(other.pool_) {}

template <typename T, typename Alloc>
typename pool_allocator<T, Alloc>::pointer pool_allocator<T, Alloc>::allocate(size_type n, const void* hint) {
    if (n == 0) {
        return nullptr;
    }

    pointer block = static_cast<pointer>(pool_.allocate(n * sizeof(T)));
    if (!block) {
        throw std::bad_alloc();
    }
    
    return block;
}

template <typename T, typename Alloc>
void pool_allocator<T, Alloc>::deallocate(pointer p, size_type n) noexcept {
    if (p) {
        pool_.deallocate(p);
    }
}

template <typename T, typename Alloc>
template <typename U, typename... Args>
void pool_allocator<T, Alloc>::construct(U* p, Args&&... args) noexcept {
    new (p) U(std::forward<Args>(args)...);
}

template <typename T, typename Alloc>
template <typename U>
void pool_allocator<T, Alloc>::destroy(U* p) noexcept {
    p->~U();
}

template <typename T, typename Alloc>
bool pool_allocator<T, Alloc>::operator==(const pool_allocator& other) const noexcept {
    return &pool_ == &other.pool_;
}

template <typename T, typename Alloc>
bool pool_allocator<T, Alloc>::operator!=(const pool_allocator& other) const noexcept {
    return !(*this == other);
}

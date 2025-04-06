#ifndef POOL_ALLOCATOR_HPP
#define POOL_ALLOCATOR_HPP

#include "memory_pool.hpp"
#include <memory>
#include <type_traits>

template <typename T, typename Alloc = std::allocator<T>>
class pool_allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    explicit pool_allocator(memory_pool<T>& pool) noexcept;
    
    template <typename U>
    pool_allocator(const pool_allocator<U, Alloc>& other) noexcept;

    pointer allocate(size_type n, const void* hint = nullptr);

    void deallocate(pointer p, size_type n) noexcept;

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) noexcept;

    template <typename U>
    void destroy(U* p) noexcept;

    template <typename U>
    struct rebind {
        using other = pool_allocator<U, Alloc>;
    };

    bool operator==(const pool_allocator& other) const noexcept;
    bool operator!=(const pool_allocator& other) const noexcept;

private:
    memory_pool<T>& pool_;
};


#endif // POOL_ALLOCATOR_HPP

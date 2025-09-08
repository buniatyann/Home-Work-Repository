#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <iterator>
#include <functional>
#include <stdexcept>

template <typename T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

public:
    // Default constructor
    Allocator() noexcept {}

    // Copy constructor
    Allocator(const Allocator& rhs) noexcept {}

    // Template copy constructor for different type
    template <typename U>
    Allocator(const Allocator<U>& rhs) noexcept {}

    // Destructor
    ~Allocator() {}

    // Address of an element
    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;

    // Allocate memory for `n` elements of type `T`
    pointer allocate(size_type n, const void* hint = nullptr);

    // Deallocate previously allocated memory
    void deallocate(pointer p, size_type n);

    // Construct an object of type `T` at the allocated location
    void construct(pointer p, const_reference val);

    // Construct an object of type `U` at the allocated location
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args);

    // Destruct an object of type `T`
    void destruct(pointer p);

    // Destruct an object of type `U`
    template <typename U>
    void destruct(U* p);
};

#endif // ALLOCATOR_HPP
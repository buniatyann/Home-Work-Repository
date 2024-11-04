#pragma once

#include <cassert>
#include <cstdlib>
#include <new>
#include <utility>
#include <memory>

// template <typename T>
// class RawMemory {
// public:
//     RawMemory() = default;

//     RawMemory(size_t capacity);
//     RawMemory(const RawMemory&) = delete;
//     RawMemory& operator=(const RawMemory& rhs) = delete;
//     RawMemory(RawMemory&& other) noexcept;
//     RawMemory& operator=(RawMemory&& rhs) noexcept;
//     ~RawMemory();

//     T* operator+(size_t offset) noexcept;
//     const T* operator+(size_t offset) const noexcept;
//     const T& operator[](size_t index) const noexcept;
//     T& operator[](size_t index) noexcept;

//     void Swap(RawMemory& other) noexcept;
//     const T* GetAddress() const noexcept;
//     T* GetAddress() noexcept;
//     size_t Capacity() const noexcept;

// private:
//     static T* Allocate(size_t n);
//     static void Deallocate(T* buf) noexcept;

//     T* buffer_ = nullptr;
//     size_t capacity_ = 0;
// };

template <typename T>
class RawMemory {
public:
    // Default constructor
    RawMemory() = default;

    // Parameterized constructor to allocate memory for 'capacity' number of elements
    RawMemory(size_t capacity);

    // Deleted copy constructor to prevent copying
    RawMemory(const RawMemory&) = delete;

    // Deleted copy assignment operator to prevent copying
    RawMemory& operator=(const RawMemory& rhs) = delete;

    // Move constructor to transfer ownership of memory
    RawMemory(RawMemory&& other) noexcept;

    // Move assignment operator to transfer ownership of memory
    RawMemory& operator=(RawMemory&& rhs) noexcept;

    // Destructor to deallocate memory
    ~RawMemory();

    // Pointer arithmetic to access memory with an offset
    T* operator+(size_t offset) noexcept;

    // Const pointer arithmetic to access memory with an offset
    const T* operator+(size_t offset) const noexcept;

    // Subscript operator to access memory elements
    const T& operator[](size_t index) const noexcept;
    T& operator[](size_t index) noexcept;

    // Swap contents of this object with another RawMemory object
    void Swap(RawMemory& other) noexcept;

    // Get the address of the managed memory (const version)
    const T* GetAddress() const noexcept;

    // Get the address of the managed memory (non-const version)
    T* GetAddress() noexcept;

    // Get the capacity of the allocated memory
    size_t Capacity() const noexcept;

private:
    // Static method to allocate memory for 'n' elements of type T
    static T* Allocate(size_t n);

    // Static method to deallocate previously allocated memory
    static void Deallocate(T* buf) noexcept;

    // Pointer to the beginning of the allocated memory
    T* buffer_ = nullptr;

    // Number of elements that can be stored in the allocated memory
    size_t capacity_ = 0;
};
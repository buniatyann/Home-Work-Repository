#pragma once

#include <iostream>
#include "explore/explore_raw_memory.h"


template <typename T>
class Vector {
public:
    // Define iterator types for non-const and const access
    using iterator = T*;
    using const_iterator = const T*;

    // Default constructor: initializes an empty vector
    Vector() = default;

    // Constructor that creates a vector with a specified number of elements
    Vector(size_t size);

    // Copy constructor: initializes a new vector as a copy of another
    Vector(const Vector& other);

    // Move constructor: transfers resources from another vector to this one
    Vector(Vector&& other) noexcept;

    // Destructor: cleans up resources
    ~Vector();

    // Copy assignment operator: assigns the contents of another vector to this one
    Vector& operator=(const Vector& rhs);

    // Move assignment operator: transfers resources from another vector to this one
    Vector& operator=(Vector&& rhs) noexcept;

    // Subscript operator for const access: provides read-only access to elements
    const T& operator[](size_t index) const noexcept;

    // Subscript operator for non-const access: provides read-write access to elements
    T& operator[](size_t index) noexcept;

    // Iterator functions: provide access to the beginning and end of the vector
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    // EmplaceBack: constructs an element in place at the end of the vector
    template <typename... Args>
    T& EmplaceBack(Args&&... args);

    // Emplace: constructs an element in place at a specified position
    template <typename... Args>
    iterator Emplace(const_iterator pos, Args&&... args);

    // PushBack: adds a new element to the end of the vector by copying or moving
    void PushBack(const T& value);
    void PushBack(T&& value);

    // Insert: inserts an element at a specified position by copying or moving
    iterator Insert(const_iterator pos, const T& value);
    iterator Insert(const_iterator pos, T&& value);

    // PopBack: removes the last element from the vector
    void PopBack() noexcept;

    // Erase: removes an element at a specified position
    // noexcept specifier indicates whether this operation can throw exceptions
    iterator Erase(const_iterator pos) noexcept(std::is_nothrow_move_assignable_v<T>);

    // Swap: exchanges the contents of this vector with another vector
    void Swap(Vector& other) noexcept;

    // Size: returns the number of elements in the vector
    size_t Size() const noexcept;

    // Capacity: returns the current allocated capacity of the vector
    size_t Capacity() const noexcept;

    // Reserve: allocates space for at least new_capacity elements
    void Reserve(size_t new_capacity);

    // Resize: changes the size of the vector, adding or removing elements as needed
    void Resize(size_t new_size);

private:
    RawMemory<T> data_; // Manages raw memory for elements of type T
    size_t size_ = 0; // Tracks the number of elements currently in the vector

    // Helper function: manages the process of replacing elements in memory
    void ReplaceElementsInMemory(iterator old_memory, iterator new_memory, size_t size);
};

// template <typename T>
// class Vector {
// public:
//     using iterator = T*;
//     using const_iterator = const T*;

//     Vector() = default;
//     Vector(size_t size);
//     Vector(const Vector& other);
//     Vector(Vector&& other) noexcept;
//     ~Vector();

//     Vector& operator=(const Vector& rhs);
//     Vector& operator=(Vector&& rhs) noexcept;

//     const T& operator[](size_t index) const noexcept;
//     T& operator[](size_t index) noexcept;

//     iterator begin() noexcept;
//     iterator end() noexcept;
//     const_iterator begin() const noexcept;
//     const_iterator end() const noexcept;
//     const_iterator cbegin() const noexcept;
//     const_iterator cend() const noexcept;

//     template <typename... Args>
//     T& EmplaceBack(Args&&... args);

//     template <typename... Args>
//     iterator Emplace(const_iterator pos, Args&&... args);

//     void PushBack(const T& value);
//     void PushBack(T&& value);
//     iterator Insert(const_iterator pos, const T& value);
//     iterator Insert(const_iterator pos, T&& value);

//     void PopBack() noexcept;
//     iterator Erase(const_iterator pos) noexcept(std::is_nothrow_move_assignable_v<T>);

//     void Swap(Vector& other) noexcept;

//     size_t Size() const noexcept;
//     size_t Capacity() const noexcept;
//     void Reserve(size_t new_capacity);
//     void Resize(size_t new_size);

// private:
//     RawMemory<T> data_;
//     size_t size_ = 0;

//     void ReplaceElementsInMemory(iterator old_memory, iterator new_memory, size_t size);
// };



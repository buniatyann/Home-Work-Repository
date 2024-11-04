#include "explore_raw_memory.h" // Includes the header file defining the RawMemory class

template <typename T>
RawMemory<T>::RawMemory(size_t capacity)
        : buffer_(Allocate(capacity)), capacity_(capacity) {
    // Constructor initializes the RawMemory object with the given capacity
    // Allocates memory for 'capacity' number of elements of type T
    // Initializes the capacity_ member with the provided capacity
}

template <typename T>
RawMemory<T>::RawMemory(RawMemory&& other) noexcept {
    // Move constructor transfers ownership of memory from 'other' to this object
    // Uses Swap to exchange buffer and capacity with 'other'
    // Deallocates memory previously held by 'other' (buffer_ is now nullptr)
    Swap(other);
    Deallocate(other.buffer_);
    other.capacity_ = 0; // Ensure 'other' has no memory resources
}

template <typename T>
RawMemory<T>& RawMemory<T>::operator=(RawMemory&& rhs) noexcept {
    // Move assignment operator transfers ownership of memory from 'rhs' to this object
    // Checks for self-assignment
    // Swaps contents with 'rhs' and deallocates 'rhs' memory
    if (this != &rhs) {
        Swap(rhs);
        Deallocate(rhs.buffer_);
        rhs.capacity_ = 0; // Ensure 'rhs' has no memory resources
    }
    return *this; // Return *this to allow chained assignments
}

template <typename T>
RawMemory<T>::~RawMemory() {
    // Destructor deallocates memory if buffer_ is not null
    // Ensures proper cleanup of resources
    if (buffer_ != nullptr) {
        Deallocate(buffer_);
    }
}

template <typename T>
T* RawMemory<T>::operator+(size_t offset) noexcept {
    // Offset operator returns a pointer to memory at a specific offset
    // Asserts that offset does not exceed capacity
    assert(offset <= capacity_);
    return buffer_ + offset;
}

template <typename T>
const T* RawMemory<T>::operator+(size_t offset) const noexcept {
    // Const offset operator returns a const pointer to memory at a specific offset
    // Casts away constness to use non-const offset operator
    return const_cast<RawMemory&>(*this) + offset;
}

template <typename T>
const T& RawMemory<T>::operator[](size_t index) const noexcept {
    // Const subscript operator returns a const reference to an element at a given index
    // Casts away constness to use non-const subscript operator
    return const_cast<RawMemory&>(*this)[index];
}

template <typename T>
T& RawMemory<T>::operator[](size_t index) noexcept {
    // Subscript operator returns a reference to an element at a given index
    // Asserts that index is within bounds of the allocated capacity
    assert(index < capacity_);
    return buffer_[index];
}

template <typename T>
void RawMemory<T>::Swap(RawMemory& other) noexcept {
    // Swaps the contents of this RawMemory object with another
    // Exchanges the buffer pointers and capacities
    std::swap(buffer_, other.buffer_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
const T* RawMemory<T>::GetAddress() const noexcept {
    // Returns the address of the managed memory as a const pointer
    return buffer_;
}

template <typename T>
T* RawMemory<T>::GetAddress() noexcept {
    // Returns the address of the managed memory as a non-const pointer
    return buffer_;
}

template <typename T>
size_t RawMemory<T>::Capacity() const noexcept {
    // Returns the capacity of the allocated memory
    return capacity_;
}

template <typename T>
T* RawMemory<T>::Allocate(size_t n) {
    // Allocates memory for 'n' elements of type T
    // Uses operator new to allocate raw memory
    // Returns a pointer to the allocated memory, or nullptr if n is 0
    return n != 0 ? static_cast<T*>(operator new(n * sizeof(T))) : nullptr;
}

template <typename T>
void RawMemory<T>::Deallocate(T* buf) noexcept {
    // Deallocates previously allocated memory using operator delete
    // Ensures that memory is properly released
    operator delete(buf);
}
// template <typename T>
// RawMemory<T>::RawMemory(size_t capacity)
//         : buffer_(Allocate(capacity)) , capacity_(capacity) {}

// template <typename T>
// RawMemory<T>::RawMemory(RawMemory&& other) noexcept {
//     Swap(other);
//     Deallocate(other.buffer_);
//     other.capacity_ = 0;
// }

// template <typename T>
// RawMemory<T>& RawMemory<T>::operator=(RawMemory&& rhs) noexcept {
//     if (this != &rhs) {
//         Swap(rhs);
//         Deallocate(rhs.buffer_);
//         rhs.capacity_ = 0;
//     }
//     return *this;
// }

// template <typename T>
// RawMemory<T>::~RawMemory() {
//     if (buffer_ != nullptr) {
//         Deallocate(buffer_);
//     }
// }

// template <typename T>
// T* RawMemory<T>::operator+(size_t offset) noexcept {
//     assert(offset <= capacity_);
//     return buffer_ + offset;
// }

// template <typename T>
// const T* RawMemory<T>::operator+(size_t offset) const noexcept {
//     return const_cast<RawMemory&>(*this) + offset;
// }

// template <typename T>
// const T& RawMemory<T>::operator[](size_t index) const noexcept {
//     return const_cast<RawMemory&>(*this)[index];
// }

// template <typename T>
// T& RawMemory<T>::operator[](size_t index) noexcept {
//     assert(index < capacity_);
//     return buffer_[index];
// }

// template <typename T>
// void RawMemory<T>::Swap(RawMemory& other) noexcept {
//     std::swap(buffer_, other.buffer_);
//     std::swap(capacity_, other.capacity_);
// }

// template <typename T>
// const T* RawMemory<T>::GetAddress() const noexcept {
//     return buffer_;
// }

// template <typename T>
// T* RawMemory<T>::GetAddress() noexcept {
//     return buffer_;
// }

// template <typename T>
// size_t RawMemory<T>::Capacity() const noexcept {
//     return capacity_;
// }

// template <typename T>
// T* RawMemory<T>::Allocate(size_t n) {
//     return n != 0 ? static_cast<T*>(operator new(n * sizeof(T))) : nullptr;
// }

// template <typename T>
// void RawMemory<T>::Deallocate(T* buf) noexcept {
//     operator delete(buf);
// }



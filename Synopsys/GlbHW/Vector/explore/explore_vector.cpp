#include "explore/explore_vector_h.h" // Includes header for Vector class definition

// Constructor that initializes the Vector with a given size
template <typename T>
Vector<T>::Vector(size_t size) : data_(size), size_(size) {
    // Construct default values for all elements
    std::uninitialized_value_construct_n(begin(), size);
}

// Copy constructor: Initializes this Vector as a copy of another Vector
template<typename T>
Vector<T>::Vector(const Vector& other) : data_(other.size_), size_(other.size_) {
    // Copy elements from the other Vector
    std::uninitialized_copy_n(other.begin(), size_, begin());
}

// Move constructor: Transfers resources from another Vector to this one
template<typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    // Swap contents with the other Vector
    Swap(other);
}

// Destructor: Cleans up the Vector by destroying elements
template<typename T>
Vector<T>::~Vector() {
    // Destroy all elements in the Vector
    std::destroy_n(begin(), size_);
}

// Copy assignment operator: Assigns the contents of another Vector to this one
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    if (this != &rhs) { // Self-assignment check
        if (rhs.size_ > data_.Capacity()) { // If rhs is larger than current capacity
            Vector rhs_copy(rhs); // Create a copy of rhs
            Swap(rhs_copy); // Swap contents with the copied Vector
        } else {
            if (size_ > rhs.size_) { // If current size is larger than rhs size
                // Copy elements from rhs and destroy extra elements
                std::copy(rhs.begin(), rhs.end(), begin());
                std::destroy_n(begin() + rhs.size_, size_ - rhs.size_);
            } else {
                // Copy existing elements from rhs and add new elements
                std::copy(rhs.begin(), rhs.data_ + size_, begin());
                std::uninitialized_copy_n(rhs.data_ + size_, rhs.size_ - size_, data_ + size_);
            }
            size_ = rhs.size_; // Update size
        }
    }
    return *this;
}

// Move assignment operator: Transfers resources from another Vector to this one
template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept {
    if (this != &rhs) { // Self-assignment check
        Swap(rhs); // Swap contents with rhs
    }
    return *this;
}

// Subscript operator for read-only access
template<typename T>
const T& Vector<T>::operator[](size_t index) const noexcept {
    // Use non-const version of operator[] for access
    return const_cast<Vector&>(*this)[index];
}

// Subscript operator for read-write access
template<typename T>
T& Vector<T>::operator[](size_t index) noexcept {
    assert(index < size_); // Ensure index is within bounds
    return data_[index];
}

// Iterator functions: Provide access to the beginning and end of the Vector
template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept { return data_.GetAddress(); }

template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept { return data_ + size_; }

// Const iterator functions: Provide const access to the beginning and end
template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept { return cbegin(); }

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept { return cend(); }

// Const iterator functions for range-based access
template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept { return data_.GetAddress(); }

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept { return data_ + size_; }

// EmplaceBack: Constructs an element in place at the end of the Vector
template<typename T>
template<typename... Args>
T &Vector<T>::EmplaceBack(Args&&... args) {
    if (size_ < data_.Capacity()) { // Check if there's enough capacity
        // Construct element in place at the end
        new (data_ + size_) T{std::forward<Args>(args)...};
    } else {
        // Allocate new memory with double the current capacity
        RawMemory<T> new_data{size_ == 0 ? 1 : size_ * 2};
        new (new_data + size_) T{std::forward<Args>(args)...};
        // Move existing elements to the new memory
        ReplaceElementsInMemory(data_.GetAddress(), new_data.GetAddress(), size_);
        data_.Swap(new_data); // Swap old and new memory
    }
    size_++; // Update size
    return data_[size_ - 1]; // Return reference to the newly added element
}

// Emplace: Constructs an element in place at a specified position
template<typename T>
template<typename... Args>
typename Vector<T>::iterator Vector<T>::Emplace(const_iterator pos, Args&&... args) {
    size_t position_index = std::distance(cbegin(), pos); // Calculate position index
    if (size_ < data_.Capacity()) { // Check if there's enough capacity
        if (pos == end()) return &EmplaceBack(std::forward<Args>(args)...); // If at the end, use EmplaceBack
        T tmp{std::forward<Args>(args)...}; // Construct temporary element
        new (end()) T{std::move(data_[size_ - 1])}; // Move the last element to the end
        std::move_backward(data_ + position_index, end() - 1, end()); // Shift elements to make room
        data_[position_index] = std::move(tmp); // Insert new element
    } else {
        // Allocate new memory with double the current capacity
        RawMemory<T> new_data{size_ == 0 ? 1 : size_ * 2};
        new (new_data + position_index) T{std::forward<Args>(args)...};
        try {
            // Move elements before the position
            ReplaceElementsInMemory(begin(), new_data.GetAddress(), position_index);
        } catch (...) {
            std::destroy_at(new_data + position_index); // Clean up on exception
            throw;
        }
        try {
            // Move elements after the position
            ReplaceElementsInMemory(begin() + position_index, new_data.GetAddress() + position_index + 1, size_ - position_index);
        } catch (...) {
            std::destroy_n(begin(), position_index + 1); // Clean up on exception
            throw;
        }
        data_.Swap(new_data); // Swap old and new memory
    }
    size_++; // Update size
    return data_ + position_index; // Return iterator to the newly inserted element
}

// PushBack: Adds a new element to the end of the Vector by copying
template<typename T>
void Vector<T>::PushBack(const T& value) {
    EmplaceBack(value); // Use EmplaceBack for adding element
}

// PushBack: Adds a new element to the end of the Vector by moving
template<typename T>
void Vector<T>::PushBack(T&& value) {
    EmplaceBack(std::move(value)); // Use EmplaceBack for adding element
}

// Insert: Inserts an element at a specified position by copying
template<typename T>
typename Vector<T>::iterator Vector<T>::Insert(const_iterator pos, const T& value) {
    return Emplace(pos, value); // Use Emplace for insertion
}

// Insert: Inserts an element at a specified position by moving
template<typename T>
typename Vector<T>::iterator Vector<T>::Insert(const_iterator pos, T&& value) {
    return Emplace(pos, std::move(value)); // Use Emplace for insertion
}

// PopBack: Removes the last element from the Vector
template<typename T>
void Vector<T>::PopBack() noexcept {
    std::destroy_at(end() - 1); // Destroy the last element
    size_--; // Update size
}

// Erase: Removes an element at a specified position
template<typename T>
typename Vector<T>::iterator Vector<T>::Erase(const_iterator pos) noexcept(std::is_nothrow_move_assignable_v<T>) {
    if (pos == cend()) { // If at end, just call PopBack
        PopBack();
        return end();
    }
    size_t position_index = std::distance(cbegin(), pos); // Calculate position index
    std::move(data_ + position_index + 1, end(), data_ + position_index); // Shift elements left
    PopBack(); // Remove last element
    return data_ + position_index; // Return iterator to the next element
}

// Swap: Exchanges the contents of this Vector with another Vector
template<typename T>
void Vector<T>::Swap(Vector& other) noexcept {
    std::swap(size_, other.size_); // Swap sizes
    std::swap(data_, other.data_); // Swap data pointers
}

// Size: Returns the number of elements in the Vector
template<typename T>
size_t Vector<T>::Size() const noexcept {
    return size_;
}

// Capacity: Returns the current allocated capacity of the Vector
template<typename T>
size_t Vector<T>::Capacity() const noexcept {
    return data_.Capacity();
}

// Reserve: Allocates space for at least new_capacity elements
template<typename T>
void Vector<T>::Reserve(size_t new_capacity) {
    if (new_capacity <= data_.Capacity()) return; // No change needed if capacity is sufficient
    RawMemory<T> new_data{new_capacity}; // Allocate new memory
    ReplaceElementsInMemory(begin(), new_data.GetAddress(), size_); // Move elements to new memory
    data_.Swap(new_data); // Swap old and new memory
}

// Resize: Changes the size of the Vector
template<typename T>
void Vector<T>::Resize(size_t new_size) {
    if (new_size > size_) { // If increasing size
        Reserve(new_size); // Ensure enough capacity
        std::uninitialized_value_construct_n(begin() + size_, new_size - size_); // Construct new elements
    } else if (new_size < size_) { // If decreasing size
        std::destroy_n(begin() + new_size, size_ - new_size); // Destroy extra elements
    }
    size_ = new_size; // Update size
}

// ReplaceElementsInMemory: Moves or copies elements from old memory to new memory
template<typename T>
void Vector<T>::ReplaceElementsInMemory(iterator old_memory, iterator new_memory, size_t size) {
    if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
        // Use move construction if possible or if copying is not available
        std::uninitialized_move_n(old_memory, size, new_memory);
    } else {
        // Otherwise, use copy construction
        std::uninitialized_copy_n(old_memory, size, new_memory);
    }
    std::destroy_n(old_memory, size); // Destroy old elements
}


// template <typename T>
// Vector<T>::Vector(size_t size) : data_(size), size_(size) {
//     std::uninitialized_value_construct_n(begin(), size);
// }

// template<typename T>
// Vector<T>::Vector(const Vector& other) : data_(other.size_) , size_(other.size_) {
//     std::uninitialized_copy_n(other.begin(), size_, begin());
// }

// template<typename T>
// Vector<T>::Vector(Vector&& other) noexcept {
//     Swap(other);
// }

// template<typename T>
// Vector<T>::~Vector() {
//     std::destroy_n(begin(), size_);
// }

// template<typename T>
// Vector<T>& Vector<T>::operator=(const Vector& rhs) {
//     if (this != &rhs) {
//         if (rhs.size_ > data_.Capacity()) {
//             Vector rhs_copy(rhs);
//             Swap(rhs_copy);
//         } else {
//             if (size_ > rhs.size_) {
//                 std::copy(rhs.begin(), rhs.end(), begin());
//                 std::destroy_n(begin() + rhs.size_, size_ - rhs.size_);
//             } else {
//                 std::copy(rhs.begin(), rhs.data_ + size_, begin());
//                 std::uninitialized_copy_n(rhs.data_ + size_, rhs.size_ - size_, data_ + size_);
//             }
//             size_ = rhs.size_;
//         }
//     }
//     return *this;
// }

// template<typename T>
// Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept {
//     if (this != &rhs) {
//         Swap(rhs);
//     }
//     return *this;
// }

// template<typename T>
// const T& Vector<T>::operator[](size_t index) const noexcept {
//     return const_cast<Vector&>(*this)[index];
// }

// template<typename T>
// T& Vector<T>::operator[](size_t index) noexcept {
//     assert(index < size_);
//     return data_[index];
// }

// template<typename T>
// typename Vector<T>::iterator Vector<T>::begin() noexcept { return data_.GetAddress(); }

// template<typename T>
// typename Vector<T>::iterator Vector<T>::end() noexcept { return data_ + size_; }

// template<typename T>
// typename Vector<T>::const_iterator Vector<T>::begin() const noexcept { return cbegin(); }

// template<typename T>
// typename Vector<T>::const_iterator Vector<T>::end() const noexcept { return cend(); }

// template<typename T>
// typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept { return data_.GetAddress(); }

// template<typename T>
// typename Vector<T>::const_iterator Vector<T>::cend() const noexcept { return data_ + size_; }

// template<typename T>
// template<typename... Args>
// T &Vector<T>::EmplaceBack(Args&&... args) {
//     if (size_ < data_.Capacity()) {
//         new (data_ + size_) T{std::forward<Args>(args)...};
//     } else {
//         RawMemory<T> new_data{size_ == 0 ? 1 : size_ * 2};
//         new (new_data + size_) T{std::forward<Args>(args)...};
//         ReplaceElementsInMemory(data_.GetAddress(), new_data.GetAddress(), size_);
//         data_.Swap(new_data);
//     }
//     size_++;
//     return data_[size_ - 1];
// }

// template<typename T>
// template<typename... Args>
// typename Vector<T>::iterator Vector<T>::Emplace(const_iterator pos, Args&&... args) {
//     size_t position_index = std::distance(cbegin(), pos);
//     if (size_ < data_.Capacity()) {
//         if (pos == end()) return &EmplaceBack(std::forward<Args>(args)...);
//         T tmp{std::forward<Args>(args)...};
//         new (end()) T{std::move(data_[size_ - 1])};
//         std::move_backward(data_ + position_index, end() - 1, end());
//         data_[position_index] = std::move(tmp);
//     } else {
//         RawMemory<T> new_data{size_ == 0 ? 1 : size_ * 2};
//         new (new_data + position_index) T{std::forward<Args>(args)...};
//         try {
//             ReplaceElementsInMemory(begin(), new_data.GetAddress(), position_index);
//         } catch (...) {
//             std::destroy_at(new_data + position_index);
//             throw;
//         }
//         try {
//             ReplaceElementsInMemory(begin() + position_index, new_data.GetAddress() + position_index + 1, size_ - position_index);
//         } catch (...) {
//             std::destroy_n(begin(), position_index + 1);
//             throw;
//         }
//         data_.Swap(new_data);
//     }
//     size_++;
//     return data_ + position_index;
// }

// template<typename T>
// void Vector<T>::PushBack(const T& value) {
//     EmplaceBack(value);
// }

// template<typename T>
// void Vector<T>::PushBack(T&& value) {
//     EmplaceBack(std::move(value));
// }

// template<typename T>
// typename Vector<T>::iterator Vector<T>::Insert(const_iterator pos, const T& value) {
//     return Emplace(pos, value);
// }

// template<typename T>
// typename Vector<T>::iterator Vector<T>::Insert(const_iterator pos, T&& value) {
//     return Emplace(pos, std::move(value));
// }

// template<typename T>
// void Vector<T>::PopBack() noexcept {
//     std::destroy_at(end() - 1);
//     size_--;
// }

// template<typename T>
// typename Vector<T>::iterator Vector<T>::Erase(const_iterator pos) noexcept(std::is_nothrow_move_assignable_v<T>) {
//     if (pos == cend()) {
//         PopBack();
//         return end();
//     }
//     size_t position_index = std::distance(cbegin(), pos);
//     std::move(data_ + position_index + 1, end(), data_ + position_index);
//     PopBack();
//     return data_ + position_index;
// }

// template<typename T>
// void Vector<T>::Swap(Vector& other) noexcept {
//     std::swap(size_, other.size_);
//     std::swap(data_, other.data_);
// }

// template<typename T>
// size_t Vector<T>::Size() const noexcept {
//     return size_;
// }

// template<typename T>
// size_t Vector<T>::Capacity() const noexcept {
//     return data_.Capacity();
// }

// template<typename T>
// void Vector<T>::Reserve(size_t new_capacity) {
//     if (new_capacity <= data_.Capacity()) return;
//     RawMemory<T> new_data{new_capacity};
//     ReplaceElementsInMemory(begin(), new_data.GetAddress(), size_);
//     data_.Swap(new_data);
// }

// template<typename T>
// void Vector<T>::Resize(size_t new_size) {
//     if (new_size > size_) {
//         Reserve(new_size);
//         std::uninitialized_value_construct_n(begin() + size_, new_size - size_);
//     } else if (new_size < size_) {
//         std::destroy_n(begin() + new_size, size_ - new_size);
//     }
//     size_ = new_size;
// }

// template<typename T>
// void Vector<T>::ReplaceElementsInMemory(iterator old_memory, iterator new_memory, size_t size) {
//     if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
//         std::uninitialized_move_n(old_memory, size, new_memory);
//     } else {
//         std::uninitialized_copy_n(old_memory, size, new_memory);
//     }
//     std::destroy_n(old_memory, size);
// }
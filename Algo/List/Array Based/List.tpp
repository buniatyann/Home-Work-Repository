#ifndef ARRAY__LINKED_LIST_TPP
#define ARRAY__LINKED_LIST_TPP

#include "List.hpp"
#include <algorithm>
#include <stdexcept>
#include <cassert>

template <typename T>
List<T>::List() : capacity_(0), size_(0), head_(SIZE_MAX) {
    resize(INITIAL_CAPACITY);
}

template <typename T>
List<T>::List(const List& other) 
    : capacity_(0), size_(0), head_(SIZE_MAX) {
    *this = other;
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        for (std::size_t i = 0; i < other.size_(); ++i) {
            push_back(other.at(i));
        }
    }

    return *this;
}

template <typename T>
List<T>::List(List&& other) noexcept 
    : array_(std::move(other.array_)), capacity_(other.capacity_), 
      size_(other.size_), head_(other.head_) {
    other.capacity_ = 0;
    other.size_ = 0;
    other.head_ = SIZE_MAX;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        array_ = std::move(other.array_);
        capacity_ = other.capacity_;
        size_ = other.size_;
        head_ = other.head_;
        other.capacity_ = 0;
        other.size_ = 0;
        other.head_ = SIZE_MAX;
    }
    
    return *this;
}

template <typename T>
void List<T>::insert(const T& value, std::size_t pos) {
    if (pos > size_) 
        throw std::out_of_range("Position out of range");
    
    std::size_t new_idx = allocate_node(value);
    if (pos == 0) {
        array_[new_idx].next = head_;
        head_ = new_idx;
    } 
    else {
        std::size_t prev_idx = get_node_at_position(pos - 1);
        array_[new_idx].next = array_[prev_idx].next;
        array_[prev_idx].next = new_idx;
    }
}

template <typename T>
void List<T>::insert(T&& value, std::size_t pos) {
    if (pos > size_) 
        throw std::out_of_range("Position out of range");
    
    std::size_t new_idx = allocate_node(std::move(value));
    if (pos == 0) {
        array_[new_idx].next = head_;
        head_ = new_idx;
    } 
    else {
        std::size_t prev_idx = get_node_at_position(pos - 1);
        array_[new_idx].next = array_[prev_idx].next;
        array_[prev_idx].next = new_idx;
    }
}

template <typename T>
void List<T>::push_back(const T& value) {
    insert(value, size_);
}

template <typename T>
void List<T>::push_back(T&& value) {
    insert(std::move(value), size_);
}

template <typename T>
void List<T>::push_front(const T& value) {
    insert(value, 0);
}

template <typename T>
void List<T>::push_front(T&& value) {
    insert(std::move(value), 0);
}

template <typename T>
void List<T>::pop_back() {
    if (empty()) 
        return;
    
    if (size_ == 1) {
        head_ = SIZE_MAX;
    } 
    else {
        std::size_t prev_idx = get_node_at_position(size_ - 2);
        array_[prev_idx].next = SIZE_MAX;
    }
    
    deallocate_node(size_ - 1);
}

template <typename T>
void List<T>::pop_front() {
    if (empty()) 
        return;
    
    std::size_t old_head = head_;
    head_ = array_[head_].next;
    deallocate_node(old_head);
}

template <typename T>
void List<T>::clear() {
    resize(0);
}

template <typename T>
const T& List<T>::front() const {
    if (empty()) 
        throw std::out_of_range("List is empty");

    return array_[head_].data;
}

template <typename T>
const T& List<T>::back() const {
    if (empty()) 
        throw std::out_of_range("List is empty");

    std::size_t last_idx = get_node_at_position(size_ - 1);
    return array_[last_idx].data;
}

template <typename T>
T& List<T>::front() {
    if (empty()) 
        throw std::out_of_range("List is empty");

    return array_[head_].data;
}

template <typename T>
T& List<T>::back() {
    if (empty()) 
        throw std::out_of_range("List is empty");

    std::size_t last_idx = get_node_at_position(size_ - 1);
    return array_[last_idx].data;
}

template <typename T>
std::size_t List<T>::size() const noexcept {
    return size_;
}

template <typename T>
bool List<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
std::size_t List<T>::find(const T& value) {
    std::size_t current = head_;
    std::size_t pos = 0;
    while (current != SIZE_MAX) {
        if (array_[current].data == value) {
            return pos;
        }
        current = array_[current].next;
        ++pos;
    }

    return SIZE_MAX; // Not found
}

template <typename T>
const T& List<T>::at(std::size_t ind) const {
    std::size_t idx = get_node_at_position(ind);
    return array_[idx].data;
}

template <typename T>
void List<T>::resize(std::size_t new_capacity) {
    if (new_capacity == 0) {
        array_.reset();
        capacity_ = 0;
        head_ = SIZE_MAX;
        size_ = 0;

        return;
    }

    auto new_array_ = std::make_unique<Node[]>(new_capacity);
    std::size_t old_idx = head_;
    std::size_t new_idx = 0;
    std::size_t* old_to_new = new std::size_t[capacity_](); 
    while (old_idx != SIZE_MAX && new_idx < new_capacity) {
        new_array_[new_idx] = std::move(array_[old_idx]);
        old_to_new[old_idx] = new_idx;
        old_idx = array_[old_idx].next;
        ++new_idx;
    }
    
    if (head_ != SIZE_MAX) {
        std::size_t current = 0;
        while (new_array_[current].next != SIZE_MAX) {
            std::size_t old_next = new_array_[current].next;
            new_array_[current].next = old_to_new[old_next];
            current = new_array_[current].next;
        }
    }
    
    array_ = std::move(new_array_);
    capacity_ = new_capacity;
    head_ = (size_ > 0) ? 0 : SIZE_MAX;
    delete[] old_to_new;
}

template <typename T>
void List<T>::shrink() {
    if (size_ == 0 || size_ >= capacity_ / 2) 
        return;
    
    std::size_t new_capacity = std::max(INITIAL_CAPACITY, size_ * 2);
    if (new_capacity < capacity_) {
        resize(new_capacity);
    }
}

template <typename T>
std::size_t List<T>::allocate_node(const T& value) {
    if (size_ >= capacity_) {
        std::size_t new_cap = capacity_ == 0 ? INITIAL_CAPACITY : capacity_ * 2;
        resize(new_cap);
    }
    
    std::size_t idx = size_++;
    array_[idx] = Node(value);
    return idx;
}

template <typename T>
std::size_t List<T>::allocate_node(T&& value) {
    if (size_ >= capacity_) {
        std::size_t new_cap = capacity_ == 0 ? INITIAL_CAPACITY : capacity_ * 2;
        resize(new_cap);
    }
    
    std::size_t idx = size_++;
    array_[idx] = Node(std::move(value));
    return idx;
}

template <typename T>
void List<T>::deallocate_node(std::size_t idx) {
    if (idx >= size_) 
        return;
    
    if (idx != size_ - 1) {
        array_[idx] = std::move(array_[size_ - 1]);
    }

    --size_;
    shrink();
}

template <typename T>
std::size_t List<T>::get_node_at_position(std::size_t pos) const {
    if (pos >= size_) 
        throw std::out_of_range("Index out of range");
    
    std::size_t current = head_;
    for (std::size_t i = 0; i < pos && current != SIZE_MAX; ++i) {
        current = array_[current].next;
    }

    return current;
}

#endif // ARRAY__LINKED_LIST_TPP
#include "Deque.hpp"
#include <stdexcept>
#include <algorithm>

template <typename T>
Deque<T>::Deque() : front_idx(0), back_idx(0), current_size(0) {}

template <typename T>
Deque<T>::~Deque() {
    clear();
}

template <typename T>
Deque<T>::Deque(const Deque& other)
    : data(other.data), front_idx(other.front_idx), back_idx(other.back_idx), current_size(other.current_size) {}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
    if (this != &other) {
        Deque temp(other);
        swap(*this, temp);
    }
    
    return *this;
}

template <typename T>
Deque<T>::Deque(Deque&& other) noexcept
    : data(std::move(other.data)), front_idx(other.front_idx), back_idx(other.back_idx), current_size(other.current_size) {
    other.front_idx = 0;
    other.back_idx = 0;
    other.current_size = 0;
}

template <typename T>
Deque<T>& Deque<T>::operator=(Deque&& other) noexcept {
    if (this != &other) {
        clear();
        data = std::move(other.data);
        front_idx = other.front_idx;
        back_idx = other.back_idx;
        current_size = other.current_size;
        other.front_idx = 0;
        other.back_idx = 0;
        other.current_size = 0;
    }

    return *this;
}

template <typename T>
void swap(Deque<T>& a, Deque<T>& b) noexcept {
    std::swap(a.get_data(), b.get_data());
    std::swap(a.get_front_idx(), b.get_front_idx());
    std::swap(a.get_back_idx(), b.get_back_idx());
    std::swap(a.get_current_size(), b.get_current_size());
}

template <typename T>
void Deque<T>::push_front(const T& element) {
    if (current_size == data.size()) 
        resize();

    front_idx = prev(front_idx);
    data[front_idx] = element;
    ++current_size;
}

template <typename T>
void Deque<T>::push_front(T&& element) {
    if (current_size == data.size()) 
        resize();

    front_idx = prev(front_idx);
    data[front_idx] = std::move(element);
    ++current_size;
}

template <typename T>
void Deque<T>::pop_front() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    front_idx = next(front_idx);
    --current_size;
}

template <typename T>
T& Deque<T>::front() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return data[front_idx];
}

template <typename T>
const T& Deque<T>::front() const {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return data[front_idx];
}

template <typename T>
void Deque<T>::push_back(const T& element) {
    if (current_size == data.size()) 
        resize();

    data[back_idx] = element;
    back_idx = next(back_idx);
    ++current_size;
}

template <typename T>
void Deque<T>::push_back(T&& element) {
    if (current_size == data.size()) 
        resize();

    data[back_idx] = std::move(element);
    back_idx = next(back_idx);
    ++current_size;
}

template <typename T>
void Deque<T>::pop_back() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    back_idx = prev(back_idx);
    --current_size;
}

template <typename T>
T& Deque<T>::back() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");
        
    return data[prev(back_idx)];
}

template <typename T>
const T& Deque<T>::back() const {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return data[prev(back_idx)];
}

template <typename T>
bool Deque<T>::empty() const {
    return current_size == 0;
}

template <typename T>
std::size_t Deque<T>::size() const {
    return current_size;
}

template <typename T>
void Deque<T>::clear() {
    while (!empty()) pop_front();
}

template <typename T>
std::size_t Deque<T>::next(std::size_t idx) const {
    return (idx + 1) % data.size();
}

template <typename T>
std::size_t Deque<T>::prev(std::size_t idx) const {
    return (idx == 0 ? data.size() - 1 : idx - 1);
}

template <typename T>
void Deque<T>::resize() {
    std::size_t new_capacity = (data.size() == 0) ? 4 : data.size() * 2;
    std::vector<T> new_data(new_capacity);
    std::size_t new_idx = 0;
    for (std::size_t i = 0; i < current_size; ++i) {
        std::size_t old_idx = (front_idx + i) % data.size();
        new_data[new_idx++] = std::move_if_noexcept(data[old_idx]);
    }
 
    data = std::move(new_data);
    front_idx = 0;
    back_idx = current_size;
}

template <typename T>
std::vector<T>& Deque<T>::get_data() {
    return data;
}

template <typename T>
std::size_t& Deque<T>::get_front_idx() {
    return front_idx;
}

template <typename T>
std::size_t& Deque<T>::get_back_idx() {
    return back_idx;
}

template <typename T>
std::size_t& Deque<T>::get_current_size() {
    return current_size;
}
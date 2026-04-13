#ifndef HEAP_TPP
#define HEAP_TPP

#include "Heap.hpp"

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::heapify_up(size_type index) {
    while (index > 0) {
        size_type parent = (index - 1) / 2;
        if (comp_(c_[parent], c_[index])) {
            std::swap(c_[parent], c_[index]);
            index = parent;
        } else {
            break;
        }
    }
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::heapify_down(size_type index) {
    size_type size = c_.size();
    while (true) {
        size_type largest = index;
        size_type left = 2 * index + 1;
        size_type right = 2 * index + 2;

        if (left < size && comp_(c_[largest], c_[left])) {
            largest = left;
        }
        if (right < size && comp_(c_[largest], c_[right])) {
            largest = right;
        }
        if (largest != index) {
            std::swap(c_[index], c_[largest]);
            index = largest;
        } 
        else {
            break;
        }
    }
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::build_heap() {
    if (c_.size() <= 1) {
        return;
    }
    for (size_type i = c_.size() / 2; i > 0; --i) {
        heapify_down(i - 1);
    }
}

template <typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::Heap() : c_(Container()), comp_(Compare()) {}

template <typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::Heap(const Compare& compare) : c_(Container()), comp_(compare) {}

template <typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::Heap(const Compare& compare, const Container& cont)
    : c_(cont), comp_(compare) {
    build_heap();
}

template <typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::Heap(const Compare& compare, Container&& cont)
    : c_(std::move(cont)), comp_(compare) {
    build_heap();
}

template <typename T, typename Container, typename Compare>
template <class InputIt>
Heap<T, Container, Compare>::Heap(InputIt first, InputIt last, const Compare& compare)
    : c_(first, last), comp_(compare) {
    build_heap();
}

template <typename T, typename Container, typename Compare>
template <class InputIt>
Heap<T, Container, Compare>::Heap(InputIt first, InputIt last, const Compare& compare, const Container& cont)
    : c_(cont), comp_(compare) {
    c_.insert(c_.end(), first, last);
    build_heap();
}

template <typename T, typename Container, typename Compare>
template <class InputIt>
Heap<T, Container, Compare>::Heap(InputIt first, InputIt last, const Compare& compare, Container&& cont)
    : c_(std::move(cont)), comp_(compare) {
    c_.insert(c_.end(), first, last);
    build_heap();
}

template <typename T, typename Container, typename Compare>
Heap<T, Container, Compare>::Heap(std::initializer_list<value_type> init)
    : c_(init), comp_(Compare()) {
    build_heap();
}

template <typename T, typename Container, typename Compare>
bool Heap<T, Container, Compare>::empty() const {
    return c_.empty();
}

template <typename T, typename Container, typename Compare>
typename Heap<T, Container, Compare>::const_reference Heap<T, Container, Compare>::top() const {
    return c_.front();
}

template <typename T, typename Container, typename Compare>
typename Heap<T, Container, Compare>::size_type Heap<T, Container, Compare>::size() const {
    return c_.size();
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::push(const T& rhs) {
    c_.push_back(rhs);
    heapify_up(c_.size() - 1);
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::push(T&& rhs) {
    c_.push_back(std::move(rhs));
    heapify_up(c_.size() - 1);
}

template <typename T, typename Container, typename Compare>
template <typename... Args>
void Heap<T, Container, Compare>::emplace(Args&&... values) noexcept {
    c_.emplace_back(std::forward<Args>(values)...);
    heapify_up(c_.size() - 1);
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::pop() {
    std::swap(c_.front(), c_.back());
    c_.pop_back();
    if (!c_.empty()) {
        heapify_down(0);
    }
}

template <typename T, typename Container, typename Compare>
void Heap<T, Container, Compare>::swap(Heap& rhs) noexcept {
    std::swap(c_, rhs.c_);
    std::swap(comp_, rhs.comp_);
}

#endif // HEAP_TPP
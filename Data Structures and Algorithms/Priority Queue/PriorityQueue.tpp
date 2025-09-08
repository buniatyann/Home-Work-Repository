#ifndef PRIORITYQUEUE_TPP
#define PRIORITYQUEUE_TPP

#include "PriorityQueue.hpp"

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue() : c_(Container()), comp_(Compare()) {
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare) : c_(Container()), comp_(compare) {
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, const Container& cont)
    : c_(cont), comp_(compare) {
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, Container&& cont)
    : c_(std::move(cont)), comp_(compare) {
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
template <class InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare)
    : c_(first, last), comp_(compare) {
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
template <class InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont)
    : c_(cont), comp_(compare) {
    c_.insert(c_.end(), first, last);
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
template <class InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare, Container&& cont)
    : c_(std::move(cont)), comp_(compare) {
    c_.insert(c_.end(), first, last);
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(std::initializer_list<value_type> init)
    : c_(init), comp_(Compare()) {
    std::make_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
bool PriorityQueue<T, Container, Compare>::empty() const {
    return c_.empty();
}

template <typename T, typename Container, typename Compare>
typename PriorityQueue<T, Container, Compare>::const_reference PriorityQueue<T, Container, Compare>::top() const {
    return c_.front();
}

template <typename T, typename Container, typename Compare>
typename PriorityQueue<T, Container, Compare>::size_type PriorityQueue<T, Container, Compare>::size() const {
    return c_.size();
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::push(const T& rhs) {
    c_.push_back(rhs);
    std::push_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::push(T&& rhs) {
    c_.push_back(std::move(rhs));
    std::push_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
template <typename... Args>
void PriorityQueue<T, Container, Compare>::emplace(Args&&... values) noexcept {
    c_.emplace_back(std::forward<Args>(values)...);
    std::push_heap(c_.begin(), c_.end(), comp_);
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::pop() {
    std::pop_heap(c_.begin(), c_.end(), comp_);
    c_.pop_back();
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::swap(PriorityQueue& rhs) noexcept {
    std::swap(c_, rhs.c_);
    std::swap(comp_, rhs.comp_);
}


#endif // PRIORITYQUEUE_TPP
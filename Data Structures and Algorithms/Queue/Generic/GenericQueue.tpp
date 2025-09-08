#ifndef GENERICQUEUE_TPP
#define GENERICQUEUE_TPP

#include "GenericQueue.hpp"

template <typename T, typename Container>
Queue<T, Container>::Queue() = default;

template <typename T, typename Container>
Queue<T, Container>::Queue(const Queue& rhs) = default;

template <typename T, typename Container>
Queue<T, Container>& Queue<T, Container>::operator=(const Queue& rhs) = default;

template <typename T, typename Container>
Queue<T, Container>::Queue(Queue&& rhs) noexcept = default;

template <typename T, typename Container>
Queue<T, Container>& Queue<T, Container>::operator=(Queue&& rhs) noexcept = default;

template <typename T, typename Container>
Queue<T, Container>::~Queue() = default;

template <typename T, typename Container>
Queue<T, Container>::Queue(std::initializer_list<value_type> init) : c_(init) {}

template <typename T, typename Container>
typename Queue<T, Container>::const_reference Queue<T, Container>::front() const {
    return c_.front();
}

template <typename T, typename Container>
typename Queue<T, Container>::reference Queue<T, Container>::front() {
    return c_.front();
}

template <typename T, typename Container>
typename Queue<T, Container>::const_reference Queue<T, Container>::back() const {
    return c_.back();
}

template <typename T, typename Container>
typename Queue<T, Container>::reference Queue<T, Container>::back() {
    return c_.back();
}

template <typename T, typename Container>
bool Queue<T, Container>::empty() const {
    return c_.empty();
}

template <typename T, typename Container>
typename Queue<T, Container>::size_type Queue<T, Container>::size() const {
    return c_.size();
}

template <typename T, typename Container>
void Queue<T, Container>::push(const value_type& value) {
    c_.push_back(value);
}

template <typename T, typename Container>
void Queue<T, Container>::push(value_type&& value) {
    c_.push_back(std::move(value));
}

template <typename T, typename Container>
void Queue<T, Container>::pop() {
    c_.pop_front();
}

template <typename T, typename Container>
template <typename... Args>
void Queue<T, Container>::emplace(Args&&... args) {
    c_.emplace_back(std::forward<Args>(args)...);
}

template <typename T, typename Container>
void Queue<T, Container>::swap(Queue& rhs) {
    std::swap(c_, rhs.c_);
}

template <typename T1, typename Container1>
bool operator==(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs) {
    return lhs.c_ == rhs.c_;
}

template <typename T1, typename Container1>
bool operator!=(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs) {
    return lhs.c_ != rhs.c_;
}

template <typename T1, typename Container1>
bool operator<(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs) {
    return lhs.c_ < rhs.c_;
}

template <typename T1, typename Container1>
bool operator<=(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs) {
    return lhs.c_ <= rhs.c_;
}

template <typename T1, typename Container1>
bool operator>(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs) {
    return lhs.c_ > rhs.c_;
}

template <typename T1, typename Container1>
bool operator>=(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs) {
    return lhs.c_ >= rhs.c_;
}


#endif // GENERICQUEUE_TPP
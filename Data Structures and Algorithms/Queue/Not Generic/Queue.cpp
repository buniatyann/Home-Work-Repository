#include "Queue.hpp"

template <typename T>
Queue<T>::Queue() = default;

template <typename T>
Queue<T>::Queue(const Queue& rhs) = default;

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& rhs) = default;

template <typename T>
Queue<T>::Queue(Queue&& rhs) noexcept = default;

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& rhs) noexcept = default;

template <typename T>
Queue<T>::Queue(std::initializer_list<T> rhs) {
    for (const auto& value : rhs) {
        this->push(value);
    }
}

template <typename T>
Queue<T>::~Queue() = default;

template <typename T>
const T& Queue<T>::front() const {
    return lst_.front();
}

template <typename T>
T& Queue<T>::front() {
    return lst_.front();
}

template <typename T>
const T& Queue<T>::back() const {
    return lst_.back();
}

template <typename T>
T& Queue<T>::back() {
    return lst_.back();
}

template <typename T>
size_t Queue<T>::size() const {
    return lst_.size();
}

template <typename T>
bool Queue<T>::empty() const {
    return lst_.empty();
}

template <typename T>
void Queue<T>::push(const T& value) {
    lst_.push_back(value);
}

template <typename T>
void Queue<T>::push(T&& value) {
    lst_.push_back(std::move(value));
}

template <typename T>
void Queue<T>::pop() {
    lst_.pop_front();
}

template <typename T>
template <typename... Args>
void Queue<T>::emplace(Args&&... values) noexcept(noexcept(lst_.emplace_back(std::forward<Args>(values)...))) {
    lst_.emplace_back(std::forward<Args>(values)...);
}

template <typename T>
void Queue<T>::swap(Queue& rhs) {
    lst_.swap(rhs.lst_);
}

template <typename T>
bool Queue<T>::operator==(const Queue& other) const {
    return lst_ == other.lst_;
}

template <typename T>
bool Queue<T>::operator!=(const Queue& other) const {
    return lst_ != other.lst_;
}

template <typename T>
bool Queue<T>::operator<(const Queue& other) const {
    return lst_ < other.lst_;
}

template <typename T>
bool Queue<T>::operator>(const Queue& other) const {
    return lst_ > other.lst_;
}

template <typename T>
bool Queue<T>::operator<=(const Queue& other) const {
    return lst_ <= other.lst_;
}

template <typename T>
bool Queue<T>::operator>=(const Queue& other) const {
    return lst_ >= other.lst_;
}

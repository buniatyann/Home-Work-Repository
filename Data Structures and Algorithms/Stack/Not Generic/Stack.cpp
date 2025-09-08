#include "Stack.hpp"

/*
    template <typename T>
    Stack<T>::Stack() = default;

    template <typename T>
    Stack<T>::Stack(const Stack& rhs) : c_(rhs.c_) {}

    template <typename T>
    Stack<T>& Stack<T>::operator=(const Stack& rhs) {
        if (this != &rhs) {
            c_ = rhs.c_;
        }

        return *this;
    }

    template <typename T>
    Stack<T>::Stack(Stack&& rhs) noexcept : c_(std::move(rhs.c_)) {}

    template <typename T>
    Stack<T>& Stack<T>::operator=(Stack&& rhs) noexcept {
        if (this != &rhs) {
            c_ = std::move(rhs.c_);
        }

        return *this;
    }

    template <typename T>
    Stack<T>::Stack(const std::initializer_list<T>& init) {
        c_.assign(init.begin(), init.end());
    }
*/

template <typename T>
Stack<T>::Stack() = default;

template <typename T>
Stack<T>::Stack(const Stack& rhs) = default;

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) = default;

template <typename T>
Stack<T>::Stack(Stack&& rhs) noexcept = default;

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& rhs) noexcept = default;

template <typename T>
Stack<T>::~Stack() = default;

template <typename T>
Stack<T>::Stack(const std::initializer_list<T>& init) {
    c_.assign(init.begin(), init.end());
}

template <typename T>
void Stack<T>::push(const T& value) {
    c_.push_back(value);
}

template <typename T>
void Stack<T>::push(T&& value) {
    c_.push_back(std::move(value));
}

template <typename T>
void Stack<T>::pop() {
    if (!c_.empty()) c_.pop_back();
}

template <typename T>
const T& Stack<T>::top() const {
    return c_.back();
}

template <typename T>
T& Stack<T>::top() {
    return c_.back();
}

template <typename T>
std::size_t Stack<T>::size() const noexcept {
    return c_.size();
}

template <typename T>
bool Stack<T>::empty() const noexcept {
    return c_.empty();
}

template <typename T>
void Stack<T>::clear() noexcept {
    c_.clear();
}

template <typename T>
void Stack<T>::swap(Stack& rhs) noexcept {
    c_.swap(rhs.c_);
}

template <typename T>
template <typename... Args>
void Stack<T>::emplace(Args&&... values) {
    c_.emplace_back(std::forward<Args>(values)...);
}

template <typename T>
bool operator==(const Stack<T>& lhs, const Stack<T>& rhs) {
    return lhs.c_ == rhs.c_;
}

template <typename T>
bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator>(const Stack<T>& lhs, const Stack<T>& rhs) {
    return lhs.c_ > rhs.c_;
}

template <typename T>
bool operator>=(const Stack<T>& lhs, const Stack<T>& rhs) {
    return lhs.c_ >= rhs.c_;
}

template <typename T>
bool operator<(const Stack<T>& lhs, const Stack<T>& rhs) {
    return lhs.c_ < rhs.c_;
}

template <typename T>
bool operator<=(const Stack<T>& lhs, const Stack<T>& rhs) {
    return lhs.c_ <= rhs.c_;
}
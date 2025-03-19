#ifndef GENERICSTACK_TPP
#define GENERICSTACK_TPP

#include "GenericStack.hpp"

template <typename T, typename Container>
Stack<T, Container>::Stack(const Container& cont) : c_(cont) {}

template <typename T, typename Container>
Stack<T, Container>::Stack(Container&& cont) noexcept : c_(std::move(cont)) {}

template <typename T, typename Container>
Stack<T, Container>::Stack(std::initializer_list<value_type> init) {
    c_.assign(init.begin(), init.end());
}

template <typename T, typename Container>
void Stack<T, Container>::push(const value_type& value) {
    c_.push_back(value);
}

template <typename T, typename Container>
void Stack<T, Container>::push(value_type&& value) {
    c_.push_back(std::move(value));
}

template <typename T, typename Container>
void Stack<T, Container>::pop() {
    c_.pop_back();
}

template <typename T, typename Container>
const typename Stack<T, Container>::value_type& Stack<T, Container>::top() const {
    return c_.back();
}

template <typename T, typename Container>
typename Stack<T, Container>::value_type& Stack<T, Container>::top() {
    return c_.back();
}

template <typename T, typename Container>
typename Stack<T, Container>::size_type Stack<T, Container>::size() const noexcept {
    return c_.size();
}

template <typename T, typename Container>
bool Stack<T, Container>::empty() const noexcept {
    return c_.empty();
}

template <typename T, typename Container>
void Stack<T, Container>::clear() {
    c_.clear();
}

template <typename T, typename Container>
void Stack<T, Container>::swap(Stack& rhs) noexcept(noexcept(std::declval<Container&>().swap(std::declval<Container&>()))) {
    c_.swap(rhs.c_);
}

template <typename T, typename Container>
template <typename... Args>
void Stack<T, Container>::emplace(Args&&... args) {
    c_.emplace_back(std::forward<Args>(args)...);
}

template <typename T, typename Container>
const Container& Stack<T, Container>::get_container() const noexcept {
    return c_;
}

template <typename T, typename Container>
Container& Stack<T, Container>::get_container() noexcept {
    return c_;
}

template <typename T1, typename Container1>
bool operator==(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs) {
    return lhs.c_ == rhs.c_;
}

template <typename T1, typename Container1>
bool operator!=(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs) {
    return lhs.c_ != rhs.c_;
}

template <typename T1, typename Container1>
bool operator<(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs) {
    return lhs.c_ < rhs.c_;
}

template <typename T1, typename Container1>
bool operator<=(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs) {
    return lhs.c_ <= rhs.c_;
}

template <typename T1, typename Container1>
bool operator>(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs) {
    return lhs.c_ > rhs.c_;
}

template <typename T1, typename Container1>
bool operator>=(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs) {
    return lhs.c_ >= rhs.c_;
}

#endif // GENERICSTACK_TPP

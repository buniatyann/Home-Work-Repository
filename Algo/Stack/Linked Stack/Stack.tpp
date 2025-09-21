#ifndef STACKLIST_TPP
#define STACKLIST_TPP

#include "Stack.hpp"

template <typename T>
Stack<T>::Stack() = default;

template <typename T>
Stack<T>::~Stack() = default;

template <typename T>
Stack<T>::Stack(const Stack& other) : elements_(other.elements_) {}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        elements_ = other.elements_;
    }

    return *this;
}

template <typename T>
Stack<T>::StackList(Stack&& other) noexcept : elements_(std::move(other.elements_)) {}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        elements_ = std::move(other.elements_);
    }
    
    return *this;
}

template <typename T>
void Stack<T>::push(Stack<T>::const_reference element) {
    elements_.push_front(element);
}

template <typename T>
void Stack<T>::emplace(Stack<T>::value_type&& element) {
    elements_.emplace_front(std::move(element));
}

template <typename T>
const_reference Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    return elements_.front();
}

template <typename T>
reference Stack<T>::top() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    return elements_.front();
}

template <typename T>
bool Stack<T>::empty() const {
    return elements_.empty();
}

template <typename T>
typename Stack<T>::value_type Stack<T>::peek() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    return elements_.front();
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    elements_.pop_front();
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
    return elements_.size();
}

#endif
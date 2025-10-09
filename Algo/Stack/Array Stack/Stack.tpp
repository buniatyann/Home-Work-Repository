#ifndef STACKARRAY_TPP
#define STACKARRAY_TPP

#include "Stack.hpp"

template <typename T>
Stack<T>::Stack() = default;

template <typename T>
Stack<T>::~Stack() = default;

template <typename T>
Stack<T>::Stack(const Stack& other) : elements(other.elements) {}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        elements = other.elements;
    }

    return *this;
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept : elements(std::move(other.elements)) {}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        elements = std::move(other.elements);
    }

    return *this;
}

template <typename T>
void Stack<T>::push(Stack<T>::const_reference element) {
    elements.push_back(element);
}

template <typename T>
void Stack<T>::emplace(Stack<T>::value_type&& element) {
    elements.emplace_back(std::move(element));
}

template <typename T>
Stack<T>::const_reference Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    return elements.back();
}

template <typename T>
Stack<T>::reference Stack<T>::top() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    return elements.back();
}

template <typename T>
bool Stack<T>::empty() const {
    return elements.empty();
}

template <typename T>
typename Stack<T>::value_type Stack<T>::peek() const {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    return elements.back();
}

template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    
    elements.pop_back();
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
    return elements.size();
}

template <typename T>
void Stack<T>::swap(Stack& other) noexcept {
    std::swap(elements, other.elements); // is that correct?
}

#endif
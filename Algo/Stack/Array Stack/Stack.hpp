#ifndef STACKARRAY_HPP
#define STACKARRAY_HPP

#include "IStack.hpp"
#include <vector>
#include <stdexcept>

template <typename T>
class Stack : public IStack<T> {
public:
    using value_type = typename IStack<T>::value_type;
    using reference = typename IStack<T>::reference;
    using const_reference = typename IStack<T>::const_reference;
    using size_type = typename IStack<T>::size_type;

    Stack();
    ~Stack() override;
    Stack(const Stack& other);
    Stack& operator=(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;

    void push(const_reference element) override;
    void emplace(value_type&& element) override;
    const_reference top() const override;
    reference top() override;
    bool empty() const override;
    value_type peek() const override;
    void pop() override;
    size_type size() const override;

    void swap(Stack& other) noexcept;

private:
    std::vector<value_type> elements;
};

#include "Stack.tpp"

#endif // STACKARRAY_HPP
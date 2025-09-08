#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include <initializer_list>

template <typename T>
class Stack {
public:
    Stack();
    Stack(const Stack& rhs);
    Stack& operator=(const Stack& rhs);
    Stack(Stack&& rhs) noexcept;
    Stack& operator=(Stack&& rhs) noexcept;
    ~Stack();

    Stack(const std::initializer_list<T>& init);

    void push(const T& value);
    void push(T&& value);
    void pop();

    const T& top() const;
    T& top();

    std::size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    void swap(Stack& rhs) noexcept;

    template <typename... Args>
    void emplace(Args&&... values);

    // Comparison operators
    template <typename C>
    friend bool operator==(const Stack<C>& lhs, const Stack<C>& rhs);

    template <typename C>
    friend bool operator!=(const Stack<C>& lhs, const Stack<C>& rhs);

    template <typename C>
    friend bool operator>(const Stack<C>& lhs, const Stack<C>& rhs);

    template <typename C>
    friend bool operator>=(const Stack<C>& lhs, const Stack<C>& rhs);

    template <typename C>
    friend bool operator<(const Stack<C>& lhs, const Stack<C>& rhs);

    template <typename C>
    friend bool operator<=(const Stack<C>& lhs, const Stack<C>& rhs);

private:
    std::deque<T> c_; // Container
};

#endif // STACK_HPP

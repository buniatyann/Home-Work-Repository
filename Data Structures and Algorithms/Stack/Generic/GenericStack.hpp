#ifndef GENERICSTACK_HPP
#define GENERICSTACK_HPP

#include <deque>
#include <initializer_list>
#include <utility>

template <typename T, typename Container = std::deque<T>>
class Stack {
public:
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using container_type = Container;

    Stack() = default;
    explicit Stack(const Container& cont);
    explicit Stack(Container&& cont) noexcept;
    Stack(const Stack& rhs) = default;
    Stack(Stack&& rhs) noexcept = default;
    Stack(std::initializer_list<value_type> init);

    Stack& operator=(const Stack& rhs) = default;
    Stack& operator=(Stack&& rhs) noexcept = default;

    ~Stack() = default;

    void push(const value_type& value);
    void push(value_type&& value);
    void pop();
    const value_type& top() const;
    value_type& top();

    size_type size() const noexcept;
    bool empty() const noexcept;
    void clear();

    void swap(Stack& rhs) noexcept(noexcept(std::declval<Container&>().swap(std::declval<Container&>())));

    template <typename... Args>
    void emplace(Args&&... args);

    const Container& get_container() const noexcept;
    Container& get_container() noexcept;

    template <typename T1, typename Container1>
    friend bool operator==(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs);
    template <typename T1, typename Container1>
    friend bool operator!=(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs);
    template <typename T1, typename Container1>
    friend bool operator<(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs);
    template <typename T1, typename Container1>
    friend bool operator<=(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs);
    template <typename T1, typename Container1>
    friend bool operator>(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs);
    template <typename T1, typename Container1>
    friend bool operator>=(const Stack<T1, Container1>& lhs, const Stack<T1, Container1>& rhs);

private:
    Container c_;
};

#include "GenericStack.tpp"

#endif // GENERICSTACK_HPP

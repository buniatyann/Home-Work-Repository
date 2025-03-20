#ifndef GENERICQUEUE_HPP
#define GENERICQUEUE_HPP

#include <deque>
#include <initializer_list>
#include <utility>

template <typename T, typename Container = std::deque<T>>
class Queue {
public:
    using value_type = T;
    using size_type = typename Container::size_type;
    using container_type = Container;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

    Queue();
    Queue(const Queue& rhs);
    Queue& operator=(const Queue& rhs);
    Queue(Queue&& rhs) noexcept;
    Queue& operator=(Queue&& rhs) noexcept;
    ~Queue();

    Queue(std::initializer_list<value_type> init);

    const_reference front() const;
    reference front();
    const_reference back() const;
    reference back();

    bool empty() const;
    size_type size() const;

    void push(const value_type& value);
    void push(value_type&& value);
    void pop();
    template <typename... Args>
    void emplace(Args&&... args);
    void swap(Queue& rhs);

    template <typename T1, typename Container1>
    friend bool operator==(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs);
    
    template <typename T1, typename Container1>
    friend bool operator!=(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs);

    template <typename T1, typename Container1>
    friend bool operator<(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs);
    
    template <typename T1, typename Container1>
    friend bool operator<=(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs);
    
    template <typename T1, typename Container1>
    friend bool operator>(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs);
    
    template <typename T1, typename Container1>
    friend bool operator>=(const Queue<T1, Container1>& lhs, const Queue<T1, Container1>& rhs);

private:
    Container c_;
};

#endif // GENERICQUEUE_HPP

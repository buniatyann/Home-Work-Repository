#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>
#include <utility>
#include <initializer_list>

template <typename T>
class Queue {
public:
    using value_type = typename std::list<T>::value_type;

    Queue();
    Queue(const Queue& rhs);
    Queue& operator=(const Queue& rhs);
    Queue(Queue&& rhs) noexcept;
    Queue& operator=(Queue&& rhs) noexcept;
    Queue(std::initializer_list<T> rhs);

    ~Queue();

    const T& front() const;
    T& front();
    const T& back() const;
    T& back();

    size_t size() const;
    bool empty() const;

    void push(const T& value);
    void push(T&& value);
    void pop();

    template <typename... Args>
    void emplace(Args&&... values) noexcept(noexcept(lst_.emplace_back(std::forward<Args>(values)...)));

    void swap(Queue& rhs);

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
    bool operator<(const Queue& other) const;
    bool operator>(const Queue& other) const;
    bool operator<=(const Queue& other) const;
    bool operator>=(const Queue& other) const;

private:
    std::list<T> lst_;
};

#endif // QUEUE_HPP

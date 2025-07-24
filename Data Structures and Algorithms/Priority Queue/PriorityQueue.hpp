#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <vector>
#include <memory>
#include <initializer_list>
#include <type_traits>

template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class PriorityQueue {
public:
    static_assert(std::is_same<T, typename Container::value_type>::value, "T must match Container::value_type");

    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using value_compare = Compare;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using container_type = Container;

    PriorityQueue();
    explicit PriorityQueue(const Compare& compare);
    PriorityQueue(const Compare& compare, const Container& cont);
    PriorityQueue(const Compare& compare, Container&& cont);
    PriorityQueue(const PriorityQueue& other) = default;
    PriorityQueue(PriorityQueue&& other) noexcept = default;

    template <class InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& compare = Compare());

    template <class InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont);

    template <class InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& compare, Container&& cont);

    PriorityQueue(std::initializer_list<value_type> init);

    PriorityQueue& operator=(const PriorityQueue& rhs) = default;
    PriorityQueue& operator=(PriorityQueue&& rhs) noexcept = default;
    ~PriorityQueue() = default;

    bool empty() const;
    const_reference top() const;
    size_type size() const;

    void push(const T& rhs);
    void push(T&& rhs);

    template <typename... Args>
    void emplace(Args&&... values) noexcept;

    void pop();
    void swap(PriorityQueue& rhs) noexcept;

private:
    Container c_;
    Compare comp_;
};

#include "PriorityQueue.tpp"

#endif // PRIORITYQUEUE_HPP

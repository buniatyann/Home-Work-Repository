#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <memory>
#include <initializer_list>
#include <type_traits>

template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class Heap {
public:
    static_assert(std::is_same<T, typename Container::value_type>::value, "T must match Container::value_type");

    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using value_compare = Compare;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using container_type = Container;

    Heap();
    explicit Heap(const Compare& compare);
    Heap(const Compare& compare, const Container& cont);
    Heap(const Compare& compare, Container&& cont);
    Heap(const Heap& other) = default;
    Heap(Heap&& other) noexcept = default;

    template <class InputIt>
    Heap(InputIt first, InputIt last, const Compare& compare = Compare());

    template <class InputIt>
    Heap(InputIt first, InputIt last, const Compare& compare, const Container& cont);

    template <class InputIt>
    Heap(InputIt first, InputIt last, const Compare& compare, Container&& cont);

    Heap(std::initializer_list<value_type> init);

    Heap& operator=(const Heap& rhs) = default;
    Heap& operator=(Heap&& rhs) noexcept = default;
    ~Heap() = default;

    bool empty() const;
    const_reference top() const;
    size_type size() const;

    void push(const T& rhs);
    void push(T&& rhs);

    template <typename... Args>
    void emplace(Args&&... values) noexcept;

    void pop();
    void swap(Heap& rhs) noexcept;

private:
    void heapify_up(size_type index);
    void heapify_down(size_type index);
    void build_heap();

    Container c_;
    Compare comp_;
};

#include "Heap.tpp"

#endif // HEAP_HPP

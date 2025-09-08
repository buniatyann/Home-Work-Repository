#ifndef LAZY_COMPUTATION_GENERIC_H
#define LAZY_COMPUTATION_GENERIC_H

#include <type_traits>
#include <stdexcept>
#include <iterator>
#include <numeric>

template <typename C>
concept IndexableContainer = requires(C c, std::size_t i) {
    { c[i] } -> std::convertible_to<typename C::value_type>;
    { c.size() } -> std::convertible_to<std::size_t>;
};

template <typename C>
concept IterableContainer = requires(C c) {
    { c.begin() } -> std::input_iterator;
    { c.end() } -> std::input_iterator;
    typename C::value_type;
};

template <typename ContainerL, typename ContainerR>
    requires IndexableContainer<ContainerL> && IndexableContainer<ContainerR> &&
             IterableContainer<ContainerL> && IterableContainer<ContainerR>
class ContainerPairOps {
public:
    using T = typename ContainerL::value_type;
    static_assert(std::is_same_v<T, typename ContainerR::value_type>, "Container value types must match");

    // Constructors
    ContainerPairOps() = delete;
    ContainerPairOps(const ContainerL& left, const ContainerR& right);
    ContainerPairOps(ContainerL&& left, ContainerR&& right);

    // Index-based operations
    T operator+(std::size_t ind) const;
    T operator-(std::size_t ind) const;
    T operator*(std::size_t ind) const;
    T operator/(std::size_t ind) const;

    // Accumulation operations
    T sum_of_elements() const;
    T difference_of_elements() const;

    // Container operations
    ContainerL container_of_sums() const;
    ContainerL container_of_differences() const;
    ContainerL container_of_sums_iter() const;
    ContainerL container_of_max() const;

    // Generic operation
    template<typename BinaryOp>
    ContainerL combine_containers(BinaryOp op) const;

    // Utility methods
    std::size_t size() const;
    bool empty() const;

    // Iterator interface
    class iterator {
        typename ContainerL::const_iterator left_it;
        typename ContainerR::const_iterator right_it;
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator(typename ContainerL::const_iterator l, typename ContainerR::const_iterator r);
        T operator*() const;
        iterator& operator++();
        iterator operator++(int);
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    iterator begin() const;
    iterator end() const;

private:
    const ContainerL left_;
    const ContainerR right_;
};

#endif // LAZY_COMPUTATION_GENERIC_H
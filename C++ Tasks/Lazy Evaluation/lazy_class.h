#ifndef LAZY_COMPUTATION_H
#define LAZY_COMPUTATION_H

#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <functional>

template <typename T>
class VectorPairOps {
public:
    // Constructors
    VectorPairOps(const std::vector<T>& left, const std::vector<T>& right);
    VectorPairOps(std::vector<T>&& left, std::vector<T>&& right);

    // Index-based operations
    T element_sum(std::size_t ind) const;
    T element_diff(std::size_t ind) const;
    T element_product(std::size_t ind) const;
    T element_division(std::size_t ind) const;

    // Accumulation operations
    T sum_of_elements() const;
    T difference_of_elements() const;

    // Container operations
    std::vector<T> container_of_sums() const;
    std::vector<T> container_of_differences() const;
    std::vector<T> container_of_max() const;

    // Generic operation
    template<typename BinaryOp>
    std::vector<T> combine_vectors(BinaryOp op) const;

    // Utility methods
    std::size_t size() const;
    bool empty() const;

    // Iterator interface
    class iterator {
        typename std::vector<T>::const_iterator left_it;
        typename std::vector<T>::const_iterator right_it;
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator(typename std::vector<T>::const_iterator l, typename std::vector<T>::const_iterator r);

        T operator*() const;
        iterator& operator++();
        iterator operator++(int);

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    };

    iterator begin() const;
    iterator end() const;

private:
    const std::vector<T> left_;
    const std::vector<T> right_;
};

// Template methods need to be defined in the header
template<typename T>
template<typename BinaryOp>
std::vector<T> VectorPairOps<T>::combine_vectors(BinaryOp op) const {
    std::vector<T> result;
    result.reserve(left_.size());
    std::transform(left_.begin(), left_.end(), right_.begin(), std::back_inserter(result), op);
    return result;
}

#endif // LAZY_COMPUTATION_H

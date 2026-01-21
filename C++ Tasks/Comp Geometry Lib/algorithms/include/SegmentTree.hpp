#ifndef SEGMENTTREE_HPP
#define SEGMENTTREE_HPP

#include <vector>
#include <functional>
#include <cstddef>
#include <type_traits>
#include <limits>

template <typename T, typename Op = std::plus<T>>
class SegmentTree {
    static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

public:
    using value_type = T;
    using size_type = std::size_t;
    using operation_type = Op;

    SegmentTree() = default;
    explicit SegmentTree(size_type n, T identity = T{});
    explicit SegmentTree(const std::vector<T>& data, T identity = T{});

    SegmentTree(const SegmentTree&) = default;
    SegmentTree& operator=(const SegmentTree&) = default;
    SegmentTree(SegmentTree&&) noexcept = default;
    SegmentTree& operator=(SegmentTree&&) noexcept = default;

    // Build tree from data
    void build(const std::vector<T>& data);

    // Point update: set value at index
    void update(size_type index, T value);

    // Point update: modify value at index using operation
    void modify(size_type index, T delta);

    // Range query: apply operation over [left, right]
    T query(size_type left, size_type right) const;

    // Single element access
    T get(size_type index) const;

    // Size of the underlying array
    size_type size() const;

    // Check if empty
    bool empty() const;

    // Clear the tree
    void clear();

    // Resize and reinitialize
    void resize(size_type n, T identity = T{});

private:
    std::vector<T> tree_;
    size_type n_ = 0;
    T identity_;
    Op op_;

    void build_internal(const std::vector<T>& data, size_type node, size_type start, size_type end);
    void update_internal(size_type node, size_type start, size_type end, size_type index, T value);
    T query_internal(size_type node, size_type start, size_type end, size_type left, size_type right) const;
};

// Common segment tree types
template <typename T>
using SumSegmentTree = SegmentTree<T, std::plus<T>>;

template <typename T>
struct MinOp {
    T operator()(const T& a, const T& b) const { return std::min(a, b); }
};

template <typename T>
struct MaxOp {
    T operator()(const T& a, const T& b) const { return std::max(a, b); }
};

template <typename T>
using MinSegmentTree = SegmentTree<T, MinOp<T>>;

template <typename T>
using MaxSegmentTree = SegmentTree<T, MaxOp<T>>;

#include "../src/SegmentTree.tpp"

#endif // SEGMENTTREE_HPP

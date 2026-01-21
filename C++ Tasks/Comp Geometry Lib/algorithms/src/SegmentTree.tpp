#ifndef SEGMENTTREE_TPP
#define SEGMENTTREE_TPP

#include "../include/SegmentTree.hpp"
#include <cassert>

template <typename T, typename Op>
SegmentTree<T, Op>::SegmentTree(size_type n, T identity)
    : n_(n), identity_(identity), op_() {
    if (n_ > 0) {
        tree_.resize(4 * n_, identity_);
    }
}

template <typename T, typename Op>
SegmentTree<T, Op>::SegmentTree(const std::vector<T>& data, T identity)
    : n_(data.size()), identity_(identity), op_() {
    if (n_ > 0) {
        tree_.resize(4 * n_, identity_);
        build_internal(data, 1, 0, n_ - 1);
    }
}

template <typename T, typename Op>
void SegmentTree<T, Op>::build(const std::vector<T>& data) {
    n_ = data.size();
    if (n_ > 0) {
        tree_.assign(4 * n_, identity_);
        build_internal(data, 1, 0, n_ - 1);
    }
}

template <typename T, typename Op>
void SegmentTree<T, Op>::build_internal(const std::vector<T>& data, size_type node,
                                         size_type start, size_type end) {
    if (start == end) {
        tree_[node] = data[start];
        return;
    }

    size_type mid = start + (end - start) / 2;
    build_internal(data, 2 * node, start, mid);
    build_internal(data, 2 * node + 1, mid + 1, end);
    tree_[node] = op_(tree_[2 * node], tree_[2 * node + 1]);
}

template <typename T, typename Op>
void SegmentTree<T, Op>::update(size_type index, T value) {
    assert(index < n_ && "Index out of bounds");
    update_internal(1, 0, n_ - 1, index, value);
}

template <typename T, typename Op>
void SegmentTree<T, Op>::update_internal(size_type node, size_type start, size_type end,
                                          size_type index, T value) {
    if (start == end) {
        tree_[node] = value;
        return;
    }

    size_type mid = start + (end - start) / 2;
    if (index <= mid) {
        update_internal(2 * node, start, mid, index, value);
    } else {
        update_internal(2 * node + 1, mid + 1, end, index, value);
    }
    tree_[node] = op_(tree_[2 * node], tree_[2 * node + 1]);
}

template <typename T, typename Op>
void SegmentTree<T, Op>::modify(size_type index, T delta) {
    assert(index < n_ && "Index out of bounds");
    T current = get(index);
    update(index, op_(current, delta));
}

template <typename T, typename Op>
T SegmentTree<T, Op>::query(size_type left, size_type right) const {
    assert(left <= right && right < n_ && "Invalid query range");
    return query_internal(1, 0, n_ - 1, left, right);
}

template <typename T, typename Op>
T SegmentTree<T, Op>::query_internal(size_type node, size_type start, size_type end,
                                      size_type left, size_type right) const {
    if (right < start || end < left) {
        return identity_;
    }

    if (left <= start && end <= right) {
        return tree_[node];
    }

    size_type mid = start + (end - start) / 2;
    T left_result = query_internal(2 * node, start, mid, left, right);
    T right_result = query_internal(2 * node + 1, mid + 1, end, left, right);
    return op_(left_result, right_result);
}

template <typename T, typename Op>
T SegmentTree<T, Op>::get(size_type index) const {
    assert(index < n_ && "Index out of bounds");
    return query(index, index);
}

template <typename T, typename Op>
typename SegmentTree<T, Op>::size_type SegmentTree<T, Op>::size() const {
    return n_;
}

template <typename T, typename Op>
bool SegmentTree<T, Op>::empty() const {
    return n_ == 0;
}

template <typename T, typename Op>
void SegmentTree<T, Op>::clear() {
    tree_.clear();
    n_ = 0;
}

template <typename T, typename Op>
void SegmentTree<T, Op>::resize(size_type n, T identity) {
    identity_ = identity;
    n_ = n;
    if (n_ > 0) {
        tree_.assign(4 * n_, identity_);
    } else {
        tree_.clear();
    }
}

#endif // SEGMENTTREE_TPP

#ifndef RTREE_HPP
#define RTREE_HPP

#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <utility>
#include <set>
#include "../Rect/rect.hpp"

template<typename ValueType>
class RTree {
public:
    explicit RTree(int max_entries = 16);

    void insert(const rect &r, const ValueType &v);
    void bulk_load(const std::vector<std::pair<rect, ValueType>>& items);
    bool remove(const rect &r, const ValueType &v);
    std::vector<ValueType> range_search(const rect &query) const;
    std::vector<ValueType> knn(const std::pair<double,double>& p, int k) const;
    std::vector<ValueType> point_search(const rect &r) const;
    void print_tree() const;
    void clear();

private:
    struct entry {
        rect mbr;
        ValueType val;
        int child; // -1 for leaf entries, else child node index

        entry();
        entry(const rect &r, const ValueType &v);
        entry(const rect &r, int child_idx);
    };

    struct node {
        bool leaf;
        std::vector<entry> entries;
        int parent;

        node(bool leaf_ = true);
    };

    std::vector<node> nodes_;
    int root_;
    int max_entries_;
    int min_entries_;

    int new_node(bool leaf);
    void clear_internal();
    rect node_mbr(int node_idx) const;
    int choose_leaf(int node_idx, const rect &r);
    void adjust_tree(int node_idx);
    void split_node(int node_idx);
    int find_leaf(int start, const rect &r, const ValueType &v) const;
    void condense_tree(int leaf_idx);
    void collect_and_reinsert(int node_idx);
    void print_node(int idx, int depth) const;
};

#endif // RTREE_HPP
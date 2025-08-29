#ifndef AABB_TREE_HPP
#define AABB_TREE_HPP

#include "../AABB/aabb.hpp"
#include <memory>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <type_traits>
// #include <nlohmann/json.hpp>

// using json = nlohmann::json;

// Utility for detecting printable types
template<typename T>
struct is_streamable {
private:
    template<typename U>
    static auto test(int) -> decltype(std::declval<std::ostream&>() << std::declval<U>(), std::true_type());
    template<typename>
    static std::false_type test(...);
public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
class AABBNode {
public:
    AABBNode(const AABB& aabb, const T& value);

    bool is_leaf() const;

    std::shared_ptr<AABBNode<T>> left_;
    std::shared_ptr<AABBNode<T>> right_;
    AABB aabb_;
    T value_;
};

template<typename T>
class AABBTree {
public:
    void insert(const AABB& aabb, const T& value);
    void remove(const T& value);
    void update(const T& value, const AABB& new_aabb);
    std::vector<T> query_overlaps(const AABB& query) const;
    T nearest_neighbor(const point_t& point) const;
    void rebalance();
    void print() const;
    bool validate() const;
    std::vector<std::tuple<point_t, point_t>> export_aabbs() const;
    // void save(const std::string& filename) const;
    // void load(const std::string& filename);

private:
    std::shared_ptr<AABBNode<T>> root_;
    std::optional<std::shared_ptr<AABBNode<T>>> find_node(const T& value) const;
    std::optional<std::shared_ptr<AABBNode<T>>> find_parent(const std::shared_ptr<AABBNode<T>>& target) const;
    void replace_child(const std::shared_ptr<AABBNode<T>>& current, const std::shared_ptr<AABBNode<T>>& target,
                       const std::shared_ptr<AABBNode<T>>& replacement);
    void update_aabbs_upward(std::shared_ptr<AABBNode<T>> node);
    void query_recursive(const std::shared_ptr<AABBNode<T>>& node, const AABB& query, std::vector<T>& results) const;
    T nearest_recursive(const std::shared_ptr<AABBNode<T>>& node, const point_t& point, float& best_dist) const;
    void collect_leaves(std::shared_ptr<AABBNode<T>> node, std::vector<std::shared_ptr<AABBNode<T>>>& leaves);
    std::shared_ptr<AABBNode<T>> build_balanced(std::vector<std::shared_ptr<AABBNode<T>>>& leaves, int l, int r);
    void print_node(const std::shared_ptr<AABBNode<T>>& node, int depth) const;
    void export_recursive(const std::shared_ptr<AABBNode<T>>& node,
                          std::vector<std::tuple<point_t, point_t>>& out) const;
};

/////// Implementation /////////

template<typename T>
AABBNode<T>::AABBNode(const AABB& aabb, const T& value)
    : left_(nullptr), right_(nullptr), aabb_(aabb), value_(value) {}

template<typename T>
bool AABBNode<T>::is_leaf() const {
    return !left_ && !right_;
}

template<typename T>
void AABBTree<T>::insert(const AABB& aabb, const T& value) {
    if (root_ && aabb.min().size() != root_->aabb_.min().size()){
        throw std::invalid_argument("AABB dimension mismatch");
    }
    
    auto new_node = std::make_shared<AABBNode<T>>(aabb, value);
    if (!root_) { 
        root_ = new_node;
        return; 
    }
    // Choose insertion spot heuristic
    auto cur = root_;
    while (!cur->is_leaf()) {
        auto l = cur->left_, r = cur->right_;
        AABB la = l->aabb_, ra = r->aabb_;
        la.extend(aabb); ra.extend(aabb);
        float cost_l = la.area() - cur->aabb_.area();
        float cost_r = ra.area() - cur->aabb_.area();
        cur = (cost_l < cost_r ? l : r);
    }

    auto parent = std::make_shared<AABBNode<T>>(cur->aabb_, T());
    parent->left_ = cur;
    parent->right_ = new_node;
    parent->aabb_ = cur->aabb_;
    parent->aabb_.extend(aabb);

    if (cur == root_) {
        root_ = parent;
    }
    else {
        auto par = find_parent(cur);
        if (par) {
            replace_child(*par, cur, parent);
        }
    }

    update_aabbs_upward(root_);
}

template<typename T>
std::optional<std::shared_ptr<AABBNode<T>>> AABBTree<T>::find_node(const T& value) const {
    if (!root_) return {};
    std::function<std::shared_ptr<AABBNode<T>>(std::shared_ptr<AABBNode<T>>)> dfs;
    dfs = [&](auto node)->std::shared_ptr<AABBNode<T>> {
        if (!node) {
            return nullptr;
        }
        if (node->is_leaf() && node->value_ == value) {
            return node;
        }
        
        auto l = dfs(node->left_), r = dfs(node->right_);
        return l ? l : r;
    };
    
    auto res = dfs(root_);
    return res ? std::optional{res} : std::nullopt;
}

template<typename T>
std::optional<std::shared_ptr<AABBNode<T>>> AABBTree<T>::find_parent(const std::shared_ptr<AABBNode<T>>& target) const {
    if (!root_ || root_ == target) return {};
    std::function<std::shared_ptr<AABBNode<T>>(std::shared_ptr<AABBNode<T>>)> dfs;
    dfs = [&](auto node)->std::shared_ptr<AABBNode<T>> {
        if (!node || node->is_leaf()) {
            return nullptr;
        }
        if (node->left_ == target || node->right_ == target) {
            return node;
        }
        
        auto l = dfs(node->left_), r = dfs(node->right_);
        return l ? l : r;
    };
    
    auto res = dfs(root_);
    return res ? std::optional{res} : std::nullopt;
}

template<typename T>
void AABBTree<T>::remove(const T& value) {
    auto node_opt = find_node(value);
    if (!node_opt) {
        return;
    }
    
    auto node = *node_opt;
    auto parent_opt = find_parent(node);
    if (!parent_opt) { 
        root_.reset();
        return; 
    }
    
    auto parent = *parent_opt;
    auto grand_opt = find_parent(parent);

    auto sibling = parent->left_ == node ? parent->right_ : parent->left_;
    if (!grand_opt) { 
        root_ = sibling; 
    }
    else {
        replace_child(*grand_opt, parent, sibling);
    }
    
    update_aabbs_upward(root_);
}

template<typename T>
void AABBTree<T>::update(const T& value, const AABB& new_aabb) {
    auto node_opt = find_node(value);
    if (!node_opt) {
        return;
    }
    
    auto node = *node_opt;
    node->aabb_ = new_aabb;
    update_aabbs_upward(root_);
}

template<typename T>
void AABBTree<T>::query_recursive(const std::shared_ptr<AABBNode<T>>& node,
                                  const AABB& query, std::vector<T>& results) const {
    if (!node || !node->aabb_.overlaps(query)) {
        return;
    }
    
    if (node->is_leaf()) {
        results.push_back(node->value_);
    }
    else {
        query_recursive(node->left_, query, results);
        query_recursive(node->right_, query, results);
    }
}

template<typename T>
std::vector<T> AABBTree<T>::query_overlaps(const AABB& query) const {
    std::vector<T> results;
    if (!root_) {
        return results;
    }
    
    query_recursive(root_, query, results);
    return results;
}

template<typename T>
T AABBTree<T>::nearest_neighbor(const point_t& point) const {
    if (!root_) {
        throw std::runtime_error("Tree is empty");
    }
    
    float best_dist = std::numeric_limits<float>::infinity();
    return nearest_recursive(root_, point, best_dist);
}

template<typename T>
T AABBTree<T>::nearest_recursive(const std::shared_ptr<AABBNode<T>>& node,
                                 const point_t& point, float& best_dist) const {
    if (!node) throw std::runtime_error("Unexpected null");
    float dist = node->aabb_.distance_to_point(point);
    T best_val{};
    if (dist >= best_dist) {
        return best_val;
    }
    if (node->is_leaf()) {
        best_dist = dist;
        return node->value_;
    }

    auto d_left = node->left_->aabb_.distance_to_point(point);
    auto d_right = node->right_->aabb_.distance_to_point(point);
    auto first = d_left < d_right ? node->left_ : node->right_;
    auto second = first == node->left_ ? node->right_ : node->left_;

    best_val = nearest_recursive(first, point, best_dist);
    if (d_left < d_right) {
        best_val = nearest_recursive(second, point, best_dist);
    }
    
    return best_val;
}

template<typename T>
void AABBTree<T>::collect_leaves(std::shared_ptr<AABBNode<T>> node,
                                 std::vector<std::shared_ptr<AABBNode<T>>>& leaves) {
    if (!node) {
        return;
    }

    if (node->is_leaf()) {
        leaves.push_back(node);
    }
    else {
        collect_leaves(node->left_, leaves);
        collect_leaves(node->right_, leaves);
    }
}

template<typename T>
std::shared_ptr<AABBNode<T>> AABBTree<T>::build_balanced(
        std::vector<std::shared_ptr<AABBNode<T>>>& leaves, int l, int r) {
    if (l > r) {
        return nullptr;
    }
    
    int m = (l + r) / 2;
    auto node = leaves[m];
    node->left_.reset(); node->right_.reset();
    if (l < m) {
        node->left_ = build_balanced(leaves, l, m - 1);
    }
    if (m < r) {
        node->right_ = build_balanced(leaves, m + 1, r);
    }

    if (node->left_) {
        node->aabb_.extend(node->left_->aabb_);
    }
    if (node->right_) {
        node->aabb_.extend(node->right_->aabb_);
    }
    
    return node;
}

template<typename T>
void AABBTree<T>::rebalance() {
    if (!root_) {
        return;
    }
    
    std::vector<std::shared_ptr<AABBNode<T>>> leaves;
    collect_leaves(root_, leaves);
    std::sort(leaves.begin(), leaves.end(),
              [](auto a, auto b) {
                  const auto& amin = a->aabb_.min();
                  const auto& bmin = b->aabb_.min();
                  return amin[0] < bmin[0];
              });
    
    root_ = build_balanced(leaves, 0, (int)leaves.size() - 1);
}

template<typename T>
void AABBTree<T>::replace_child(const std::shared_ptr<AABBNode<T>>& current,
                                const std::shared_ptr<AABBNode<T>>& target,
                                const std::shared_ptr<AABBNode<T>>& replacement) {
    if (!current) {
        return;
    }
    
    if (current->left_ == target) {
        current->left_ = replacement;
    }
    else if (current->right_ == target) {
        current->right_ = replacement;
    }
    else {
        replace_child(current->left_, target, replacement);
        replace_child(current->right_, target, replacement);
    }
}

template<typename T>
void AABBTree<T>::update_aabbs_upward(std::shared_ptr<AABBNode<T>> node) {
    if (!node || node->is_leaf()) {
        return;
    }
    if (node->left_ && node->right_) {
        node->aabb_ = node->left_->aabb_;
        node->aabb_.extend(node->right_->aabb_);
    }
    
    update_aabbs_upward(node->left_);
    update_aabbs_upward(node->right_);
}


template<typename T>
void AABBTree<T>::print() const {
    print_node(root_, 0);
}

template<typename T>
void AABBTree<T>::print_node(const std::shared_ptr<AABBNode<T>>& node, int depth) const {
    if (!node) {
        return;
    }
    
    std::string indent(depth * 2, ' ');
    std::cout << indent << (node->is_leaf() ? "Leaf: " : "Node: ");
    std::cout << "Area=" << node->aabb_.area()
    << ", Min=(" << node->aabb_.min()[0] << ", ..." << ")"
              << ", Max=(" << node->aabb_.max()[0] << ", ...)";
    if (node->is_leaf()) {
        if constexpr(is_streamable<T>::value) {
            std::cout << ", Value=" << node->value_;
        }
    }
    
    std::cout << "\n";
    print_node(node->left_, depth + 1);
    print_node(node->right_, depth + 1);
}

template<typename T>
bool AABBTree<T>::validate() const {
    std::function<bool(const std::shared_ptr<AABBNode<T>>&)> dfs =
        [&](auto node) -> bool {
            if (!node) {
            return true;
        }
        if (!node->is_leaf()) {
            if (!node->aabb_.overlaps(node->left_->aabb_)) {
                return false;
            }
            if (!node->aabb_.overlaps(node->right_->aabb_)) {
                return false;
            }
            
            return dfs(node->left_) && dfs(node->right_);
        }

        return true;
    };

    return dfs(root_);
}

template<typename T>
std::vector<std::tuple<point_t, point_t>> AABBTree<T>::export_aabbs() const {
    std::vector<std::tuple<point_t, point_t>> out;
    export_recursive(root_, out);
    return out;
}

template<typename T>
void AABBTree<T>::export_recursive(const std::shared_ptr<AABBNode<T>>& node,
                                   std::vector<std::tuple<point_t, point_t>>& out) const {
                                       if (!node) {
        return;
    }
    
    out.emplace_back(node->aabb_.min(), node->aabb_.max());
    export_recursive(node->left_, out);
    export_recursive(node->right_, out);
}

// template<typename T>
// void AABBTree<T>::save(const std::string& filename) const {
//     json j;
//     std::function<void(std::shared_ptr<AABBNode<T>>&)> dfs = [&](auto node){
//         if (!node) return;
//         json n;
//         n["min"] = node->aabb_.min();
//         n["max"] = node->aabb_.max();
//         if (node->is_leaf()) {
//             if constexpr(is_streamable<T>::value) {
//                 n["value"] = node->value_;
//             } else {
//                 n["value"] = "<non-printable>";
//             }
//         }
//         j["nodes"].push_back(n);
//         dfs(node->left_); dfs(node->right_);
//     };
//     dfs(root_);
//     std::ofstream o(filename);
//     o << std::setw(4) << j;
// }

// template<typename T>
// void AABBTree<T>::load(const std::string& filename) {
//     // For brevity: loading not fully implemented
//     throw std::runtime_error("load() not implemented");
// }

#endif // AABB_TREE_HPP

#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <functional>
#include <queue>
#include <cstddef>

template <typename T>
struct Node {
    T val;
    Node* parent;
    Node* left;
    Node* right;

    Node(const T& value);
    Node(T&& value);
};

template <typename T, typename Comp = std::less<T>>
class binary_tree {
public:
    using value_type = T;
    using NodeType = Node<T>;

    binary_tree();
    ~binary_tree();

    bool empty() const;
    size_t size() const;

    void insert(const T& value);

    template <typename... Args>
    void insert(const T& value, Args&&... args);

    template <typename... Args>
    void implant(Args&&... args);

    NodeType* find(const T& value) const;
    void inorder(std::function<void(const T&)> visit) const;
    void level_order(std::function<void(const T&)> visit) const;

    const T* min() const;
    const T* max() const;

    void erase(const T& value);
    bool is_valid() const;

private:
    NodeType* root_;
    size_t size_;
    Comp comp_;

    NodeType* insertNode(NodeType* node, NodeType* parent, const T& value);
    NodeType* findNode(NodeType* node, const T& value) const;
    void inorderTraversal(NodeType* node, std::function<void(const T&)> visit) const;
    NodeType* minNode(NodeType* node) const;
    NodeType* maxNode(NodeType* node) const;
    NodeType* eraseNode(NodeType* node, const T& value);
    void clear(NodeType* node);
    bool validate(NodeType* node, long min_val, long max_val) const;
};

#include "tree.tpp"

#endif // BINARYTREE_HPP

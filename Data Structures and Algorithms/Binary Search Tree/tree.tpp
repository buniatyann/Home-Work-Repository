#include <utility>
#include <climits>
#include "tree.hpp"

template <typename T>
Node<T>::Node(const T& value) : val(value), parent(nullptr), left(nullptr), right(nullptr) {}

template <typename T>
Node<T>::Node(T&& value) : val(std::move(value)), parent(nullptr), left(nullptr), right(nullptr) {}

template <typename T, typename Comp>
binary_tree<T, Comp>::binary_tree() : root_(nullptr), size_(0), comp_(Comp()) {}

template <typename T, typename Comp>
binary_tree<T, Comp>::~binary_tree() {
    clear(root_);
}

template <typename T, typename Comp>
bool binary_tree<T, Comp>::empty() const {
    return root_ == nullptr;
}

template <typename T, typename Comp>
size_t binary_tree<T, Comp>::size() const {
    return size_;
}

template <typename T, typename Comp>
void binary_tree<T, Comp>::insert(const T& value) {
    root_ = insertNode(root_, nullptr, value);
}

template <typename T, typename Comp>
template <typename... Args>
void binary_tree<T, Comp>::insert(const T& value, Args&&... args) {
    insert(value);
    insert(std::forward<Args>(args)...);
}

template <typename T, typename Comp>
template <typename... Args>
void binary_tree<T, Comp>::implant(Args&&... args) {
    (insert(std::forward<Args>(args)), ...);
}

template <typename T, typename Comp>
typename binary_tree<T, Comp>::NodeType* binary_tree<T, Comp>::find(const T& value) const {
    return findNode(root_, value);
}

template <typename T, typename Comp>
void binary_tree<T, Comp>::inorder(std::function<void(const T&)> visit) const {
    inorderTraversal(root_, visit);
}

template <typename T, typename Comp>
void binary_tree<T, Comp>::level_order(std::function<void(const T&)> visit) const {
    if (!root_) return;

    std::queue<NodeType*> q;
    q.push(root_);

    while (!q.empty()) {
        NodeType* current = q.front();
        q.pop();

        visit(current->val);

        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}

template <typename T, typename Comp>
const T* binary_tree<T, Comp>::min() const {
    auto node = minNode(root_);
    
    return node ? &node->val : nullptr;
}

template <typename T, typename Comp>
const T* binary_tree<T, Comp>::max() const {
    auto node = maxNode(root_);
    
    return node ? &node->val : nullptr;
}

template <typename T, typename Comp>
void binary_tree<T, Comp>::erase(const T& value) {
    root_ = eraseNode(root_, value);
}

template <typename T, typename Comp>
bool binary_tree<T, Comp>::is_valid() const {
    return validate(root_, LONG_MIN, LONG_MAX);
}

template <typename T, typename Comp>
typename binary_tree<T, Comp>::NodeType* binary_tree<T, Comp>::insertNode(NodeType* node, NodeType* parent, const T& value) {
    if (!node) {
        ++size_;
        NodeType* newNode = new NodeType(value);
        newNode->parent = parent;
        return newNode;
    }

    if (comp_(value, node->val)) {
        node->left = insertNode(node->left, node, value);
    } 
    else {
        node->right = insertNode(node->right, node, value);
    }

    return node;
}

template <typename T, typename Comp>
typename binary_tree<T, Comp>::NodeType* binary_tree<T, Comp>::findNode(NodeType* node, const T& value) const {
    if (!node) return nullptr;
    if (value == node->val) return node;

    if (comp_(value, node->val)) {
        return findNode(node->left, value);
    }
    else {
        return findNode(node->right, value);
    }
}

template <typename T, typename Comp>
void binary_tree<T, Comp>::inorderTraversal(NodeType* node, std::function<void(const T&)> visit) const {
    if (!node) return;
    inorderTraversal(node->left, visit);
    visit(node->val);
    inorderTraversal(node->right, visit);
}

template <typename T, typename Comp>
typename binary_tree<T, Comp>::NodeType* binary_tree<T, Comp>::minNode(NodeType* node) const {
    if (!node) return nullptr;
    while (node->left) {
        node = node->left;
    }
    
    return node;
}

template <typename T, typename Comp>
typename binary_tree<T, Comp>::NodeType* binary_tree<T, Comp>::maxNode(NodeType* node) const {
    if (!node) return nullptr;
    while (node->right){ 
        node = node->right;
    }

    return node;
}

template <typename T, typename Comp>
typename binary_tree<T, Comp>::NodeType* binary_tree<T, Comp>::eraseNode(NodeType* node, const T& value) {
    if (!node) return nullptr;

    if (comp_(value, node->val)) {
        node->left = eraseNode(node->left, value);
    } 
    else if (comp_(node->val, value)) {
        node->right = eraseNode(node->right, value);
    } 
    else {
        if (!node->left) {
            NodeType* temp = node->right;
            if (temp) temp->parent = node->parent;
            delete node;
            --size_;
        
            return temp;
        } 
        else if (!node->right) {
            NodeType* temp = node->left;
            if (temp) temp->parent = node->parent;
            delete node;
            --size_;
        
            return temp;
        }

        NodeType* succ = minNode(node->right);
        node->val = succ->val;
        node->right = eraseNode(node->right, succ->val);
    }

    return node;
}

template <typename T, typename Comp>
void binary_tree<T, Comp>::clear(NodeType* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T, typename Comp>
bool binary_tree<T, Comp>::validate(NodeType* node, long min_val, long max_val) const {
    if (!node) return true;

    if (node->val <= min_val || node->val >= max_val) {
        return false;
    }

    return validate(node->left, min_val, node->val) && validate(node->right, node->val, max_val);
}

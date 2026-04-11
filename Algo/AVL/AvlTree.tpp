#ifndef AVL_TPP
#define AVL_TPP

#include "AvlTree.h"

#include <algorithm>
#include <utility>

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator&
AVL<T, Compare>::iterator::operator++() {
    if (!node_) return *this;

    if (node_->right) {
        node_ = node_->right.get();
        while (node_->left)
            node_ = node_->left.get();
    }
    else {
        Node* p = node_->parent;
        while (p && node_ == p->right.get()) {
            node_ = p;
            p = p->parent;
        }

        node_ = p;
    }

    return *this;
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);

    return tmp;
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator&
AVL<T, Compare>::iterator::operator--() {
    if (!node_) {
        node_ = max_node(tree_->root_.get());
        return *this;
    }

    if (node_->left) {
        node_ = node_->left.get();
        while (node_->right)
            node_ = node_->right.get();
    }
    else {
        Node* p = node_->parent;
        while (p && node_ == p->left.get()) {
            node_ = p;
            p = p->parent;
        }

        node_ = p;
    }

    return *this;
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::iterator::operator--(int) {
    iterator tmp = *this;
    --(*this);

    return tmp;
}

template <typename T, typename Compare>
template <typename InputIt>
AVL<T, Compare>::AVL(InputIt first, InputIt last, const Compare& comp)
    : root_(nullptr), size_(0), comp_(comp) {
    for (; first != last; ++first)
        insert(*first);
}

template <typename T, typename Compare>
AVL<T, Compare>::AVL(std::initializer_list<T> init, const Compare& comp)
    : root_(nullptr), size_(0), comp_(comp) {
    for (const auto& v : init)
        insert(v);
}

template <typename T, typename Compare>
AVL<T, Compare>::AVL(const AVL& other)
    : root_(nullptr), size_(other.size_), comp_(other.comp_) {
    root_ = clone(other.root_.get(), nullptr);
}

template <typename T, typename Compare>
AVL<T, Compare>::AVL(AVL&& other) noexcept
    : root_(std::move(other.root_)), size_(other.size_), comp_(std::move(other.comp_)) {
    other.size_ = 0;
}

template <typename T, typename Compare>
AVL<T, Compare>& AVL<T, Compare>::operator=(const AVL& other) {
    if (this != &other) {
        AVL tmp(other);
        swap(tmp);
    }

    return *this;
}

template <typename T, typename Compare>
AVL<T, Compare>& AVL<T, Compare>::operator=(AVL&& other) noexcept {
    if (this != &other) {
        root_ = std::move(other.root_);
        size_ = other.size_;
        comp_ = std::move(other.comp_);
        other.size_ = 0;
    }

    return *this;
}

template <typename T, typename Compare>
AVL<T, Compare>& AVL<T, Compare>::operator=(std::initializer_list<T> init) {
    clear();
    for (const auto& v : init)
        insert(v);

    return *this;
}

template <typename T, typename Compare>
bool AVL<T, Compare>::empty() const noexcept { return size_ == 0; }

template <typename T, typename Compare>
typename AVL<T, Compare>::size_type
AVL<T, Compare>::size() const noexcept { return size_; }

template <typename T, typename Compare>
std::size_t AVL<T, Compare>::height_of(const Node* node) {
    return node ? node->height : 0;
}

template <typename T, typename Compare>
void AVL<T, Compare>::update_height(Node* node) {
    if (!node) return;
    node->height = 1 + std::max(height_of(node->left.get()),
                                height_of(node->right.get()));
}

template <typename T, typename Compare>
int AVL<T, Compare>::balance_factor(const Node* node) {
    if (!node) return 0;
    return static_cast<int>(height_of(node->left.get()))
         - static_cast<int>(height_of(node->right.get()));
}

template <typename T, typename Compare>
std::unique_ptr<typename AVL<T, Compare>::Node>&
AVL<T, Compare>::owner_of(Node* node) {
    if (!node->parent) return root_;
    if (node == node->parent->left.get()) return node->parent->left;

    return node->parent->right;
}

template <typename T, typename Compare>
std::unique_ptr<typename AVL<T, Compare>::Node>
AVL<T, Compare>::detach(Node* node) {
    std::unique_ptr<Node>& slot = owner_of(node);
    return std::move(slot);
}

template <typename T, typename Compare>
std::unique_ptr<typename AVL<T, Compare>::Node>
AVL<T, Compare>::rotate_left(std::unique_ptr<Node> x) {
    // x->right becomes new root of this subtree
    std::unique_ptr<Node> y = std::move(x->right);
    Node* x_raw = x.get();
    Node* y_raw = y.get();

    x->right = std::move(y->left);
    if (x->right) x->right->parent = x_raw;

    y->parent = x->parent;
    x->parent = y_raw;
    y->left = std::move(x);

    update_height(y->left.get());
    update_height(y_raw);

    return y;
}

template <typename T, typename Compare>
std::unique_ptr<typename AVL<T, Compare>::Node>
AVL<T, Compare>::rotate_right(std::unique_ptr<Node> x) {
    std::unique_ptr<Node> y = std::move(x->left);
    Node* x_raw = x.get();
    Node* y_raw = y.get();

    x->left = std::move(y->right);
    if (x->left) x->left->parent = x_raw;

    y->parent = x->parent;
    x->parent = y_raw;
    y->right = std::move(x);

    update_height(y->right.get());
    update_height(y_raw);

    return y;
}

template <typename T, typename Compare>
std::unique_ptr<typename AVL<T, Compare>::Node>
AVL<T, Compare>::rebalance(std::unique_ptr<Node> node) {
    update_height(node.get());
    int bf = balance_factor(node.get());

    if (bf > 1) {
        if (balance_factor(node->left.get()) < 0) {
            // LR: rotate left on left child, then right on node
            node->left = rotate_left(std::move(node->left));
            node->left->parent = node.get();
        }

        return rotate_right(std::move(node));
    }
    if (bf < -1) {
        if (balance_factor(node->right.get()) > 0) {
            // RL: rotate right on right child, then left on node
            node->right = rotate_right(std::move(node->right));
            node->right->parent = node.get();
        }

        return rotate_left(std::move(node));
    }

    return node;
}

template <typename T, typename Compare>
void AVL<T, Compare>::rebalance_path(Node* from) {
    Node* p = from;
    while (p) {
        Node* grand = p->parent;
        // Determine which side of grand holds p (or null if p is root).
        // Record this BEFORE moving p out.
        std::unique_ptr<Node>* slot_ptr;
        if (!grand) {
            slot_ptr = &root_;
        }
        else if (grand->left.get() == p) {
            slot_ptr = &grand->left;
        }
        else {
            slot_ptr = &grand->right;
        }

        std::unique_ptr<Node> subtree = std::move(*slot_ptr);
        subtree = rebalance(std::move(subtree));
        subtree->parent = grand;
        Node* new_top = subtree.get();
        *slot_ptr = std::move(subtree);
        // If a rotation happened, new_top != p, but we continue from new_top's parent
        // (which equals grand), so just keep walking up.
        p = grand;
        (void)new_top;
    }
}

template <typename T, typename Compare>
template <typename V>
std::pair<typename AVL<T, Compare>::Node*, bool>
AVL<T, Compare>::insert_impl(V&& value) {
    Node* parent = nullptr;
    Node* curr = root_.get();
    bool go_left = false;

    while (curr) {
        parent = curr;
        if (comp_(value, curr->value)) {
            curr = curr->left.get();
            go_left = true;
        }
        else if (comp_(curr->value, value)) {
            curr = curr->right.get();
            go_left = false;
        }
        else {
            return {curr, false};
        }
    }

    auto new_node = std::make_unique<Node>(std::forward<V>(value), parent);
    Node* raw = new_node.get();

    if (!parent) {
        root_ = std::move(new_node);
    }
    else if (go_left) {
        parent->left = std::move(new_node);
    }
    else {
        parent->right = std::move(new_node);
    }

    ++size_;
    rebalance_path(parent);

    return {raw, true};
}

template <typename T, typename Compare>
std::pair<typename AVL<T, Compare>::iterator, bool>
AVL<T, Compare>::insert(const T& value) {
    auto [node, inserted] = insert_impl(value);
    return {iterator(node, this), inserted};
}

template <typename T, typename Compare>
std::pair<typename AVL<T, Compare>::iterator, bool>
AVL<T, Compare>::insert(T&& value) {
    auto [node, inserted] = insert_impl(std::move(value));
    return {iterator(node, this), inserted};
}

template <typename T, typename Compare>
template <typename... Args>
std::pair<typename AVL<T, Compare>::iterator, bool>
AVL<T, Compare>::emplace(Args&&... args) {
    return insert(T(std::forward<Args>(args)...));
}

template <typename T, typename Compare>
void AVL<T, Compare>::erase_node(Node* z) {
    Node* fixup_from = nullptr;

    if (!z->left || !z->right) {
        // Zero or one child: splice out
        std::unique_ptr<Node> child = z->left ? std::move(z->left) : std::move(z->right);
        Node* parent = z->parent;
        if (child) child->parent = parent;
        fixup_from = parent;
        owner_of(z) = std::move(child);
    }
    else {
        // Two children: swap value with in-order successor, erase successor
        Node* succ = min_node(z->right.get());
        z->value = std::move(succ->value);
        erase_node(succ);

        return;
    }

    --size_;
    rebalance_path(fixup_from);
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::erase(iterator pos) {
    if (!pos.node_) return end();
    iterator next = pos;
    ++next;
    erase_node(pos.node_);

    return next;
}

template <typename T, typename Compare>
typename AVL<T, Compare>::size_type
AVL<T, Compare>::erase(const T& value) {
    Node* z = root_.get();
    while (z) {
        if (comp_(value, z->value))
            z = z->left.get();
        else if (comp_(z->value, value))
            z = z->right.get();
        else {
            erase_node(z);
            return 1;
        }
    }

    return 0;
}

template <typename T, typename Compare>
void AVL<T, Compare>::clear() noexcept {
    root_.reset();
    size_ = 0;
}

template <typename T, typename Compare>
void AVL<T, Compare>::swap(AVL& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::find(const T& value) const {
    Node* curr = root_.get();
    while (curr) {
        if (comp_(value, curr->value))
            curr = curr->left.get();
        else if (comp_(curr->value, value))
            curr = curr->right.get();
        else
            return iterator(curr, this);
    }

    return end();
}

template <typename T, typename Compare>
typename AVL<T, Compare>::size_type
AVL<T, Compare>::count(const T& value) const {
    return find(value) != end() ? 1 : 0;
}

template <typename T, typename Compare>
bool AVL<T, Compare>::contains(const T& value) const {
    return find(value) != end();
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::lower_bound(const T& value) const {
    Node* curr = root_.get();
    Node* result = nullptr;
    while (curr) {
        if (!comp_(curr->value, value)) {
            result = curr;
            curr = curr->left.get();
        }
        else {
            curr = curr->right.get();
        }
    }

    return iterator(result, this);
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::upper_bound(const T& value) const {
    Node* curr = root_.get();
    Node* result = nullptr;
    while (curr) {
        if (comp_(value, curr->value)) {
            result = curr;
            curr = curr->left.get();
        }
        else {
            curr = curr->right.get();
        }
    }

    return iterator(result, this);
}

template <typename T, typename Compare>
std::pair<typename AVL<T, Compare>::iterator, typename AVL<T, Compare>::iterator>
AVL<T, Compare>::equal_range(const T& value) const {
    return {lower_bound(value), upper_bound(value)};
}

template <typename T, typename Compare>
typename AVL<T, Compare>::Node*
AVL<T, Compare>::min_node(Node* node) {
    if (!node) return nullptr;
    while (node->left) 
        node = node->left.get();

    return node;
}

template <typename T, typename Compare>
typename AVL<T, Compare>::Node*
AVL<T, Compare>::max_node(Node* node) {
    if (!node) return nullptr;
    while (node->right) 
        node = node->right.get();

    return node;
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::begin() const noexcept {
    return iterator(min_node(root_.get()), this);
}

template <typename T, typename Compare>
typename AVL<T, Compare>::iterator
AVL<T, Compare>::end() const noexcept {
    return iterator(nullptr, this);
}

template <typename T, typename Compare>
typename AVL<T, Compare>::const_iterator
AVL<T, Compare>::cbegin() const noexcept { return begin(); }

template <typename T, typename Compare>
typename AVL<T, Compare>::const_iterator
AVL<T, Compare>::cend() const noexcept { return end(); }

template <typename T, typename Compare>
typename AVL<T, Compare>::reverse_iterator
AVL<T, Compare>::rbegin() const noexcept { return reverse_iterator(end()); }

template <typename T, typename Compare>
typename AVL<T, Compare>::reverse_iterator
AVL<T, Compare>::rend() const noexcept { return reverse_iterator(begin()); }

template <typename T, typename Compare>
typename AVL<T, Compare>::const_reverse_iterator
AVL<T, Compare>::crbegin() const noexcept { return const_reverse_iterator(end()); }

template <typename T, typename Compare>
typename AVL<T, Compare>::const_reverse_iterator
AVL<T, Compare>::crend() const noexcept { return const_reverse_iterator(begin()); }

template <typename T, typename Compare>
template <typename F>
void AVL<T, Compare>::pre_order_impl(const Node* node, F& f) {
    if (!node) return;
    f(node->value);
    pre_order_impl(node->left.get(), f);
    pre_order_impl(node->right.get(), f);
}

template <typename T, typename Compare>
template <typename F>
void AVL<T, Compare>::in_order_impl(const Node* node, F& f) {
    if (!node) return;
    in_order_impl(node->left.get(), f);
    f(node->value);
    in_order_impl(node->right.get(), f);
}

template <typename T, typename Compare>
template <typename F>
void AVL<T, Compare>::post_order_impl(const Node* node, F& f) {
    if (!node) return;
    post_order_impl(node->left.get(), f);
    post_order_impl(node->right.get(), f);
    f(node->value);
}

template <typename T, typename Compare>
template <typename F>
void AVL<T, Compare>::pre_order(F f) const { pre_order_impl(root_.get(), f); }

template <typename T, typename Compare>
template <typename F>
void AVL<T, Compare>::in_order(F f) const { in_order_impl(root_.get(), f); }

template <typename T, typename Compare>
template <typename F>
void AVL<T, Compare>::post_order(F f) const { post_order_impl(root_.get(), f); }

template <typename T, typename Compare>
std::unique_ptr<typename AVL<T, Compare>::Node>
AVL<T, Compare>::clone(const Node* src, Node* parent) {
    if (!src) return nullptr;
    auto node = std::make_unique<Node>(src->value, parent);
    node->height = src->height;
    node->left = clone(src->left.get(), node.get());
    node->right = clone(src->right.get(), node.get());

    return node;
}

template <typename T, typename Compare>
bool operator==(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    auto it1 = lhs.begin(), it2 = rhs.begin();
    for (; it1 != lhs.end(); ++it1, ++it2)
        if (*it1 != *it2) return false;

    return true;
}

template <typename T, typename Compare>
bool operator!=(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Compare>
bool operator<(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end());
}

template <typename T, typename Compare>
bool operator<=(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs) {
    return !(rhs < lhs);
}

template <typename T, typename Compare>
bool operator>(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs) {
    return rhs < lhs;
}

template <typename T, typename Compare>
bool operator>=(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs) {
    return !(lhs < rhs);
}

template <typename T, typename Compare>
void swap(AVL<T, Compare>& lhs, AVL<T, Compare>& rhs) noexcept {
    lhs.swap(rhs);
}

#endif // AVL_TPP

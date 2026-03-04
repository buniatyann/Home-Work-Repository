#ifndef RB_TREE_TPP
#define RB_TREE_TPP

#include "RBTree.hpp"


template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator&
RedBlackTree<Key, Compare>::iterator::operator++() {
    auto n = node_.lock();
    if (!n) return *this;

    if (n->right) {
        auto cur = n->right;
        while (cur->left)
            cur = cur->left;
        node_ = cur;
    }
    else {
        auto p = n->parent.lock();
        while (p && n == p->right) {
            n = p;
            p = p->parent.lock();
        }
        node_ = p ? std::weak_ptr<Node>(p) : std::weak_ptr<Node>();
    }
    return *this;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator&
RedBlackTree<Key, Compare>::iterator::operator--() {
    auto n = node_.lock();
    if (!n) {
        node_ = tree_->max_node(tree_->root_);
        return *this;
    }

    if (n->left) {
        auto cur = n->left;
        while (cur->right)
            cur = cur->right;
        node_ = cur;
    }
    else {
        auto p = n->parent.lock();
        while (p && n == p->left) {
            n = p;
            p = p->parent.lock();
        }
        node_ = p ? std::weak_ptr<Node>(p) : std::weak_ptr<Node>();
    }
    return *this;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::iterator::operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
}


template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::NodePtr
RedBlackTree<Key, Compare>::deep_copy(const NodePtr& src, NodePtr parent) const {
    if (!src) return nullptr;

    auto node = std::make_shared<Node>(src->data, src->color);
    node->parent = parent;
    node->left = deep_copy(src->left, node);
    node->right = deep_copy(src->right, node);
    return node;
}


template <typename Key, typename Compare>
template <typename InputIt>
RedBlackTree<Key, Compare>::RedBlackTree(InputIt first, InputIt last, const Compare& comp)
    : size_(0), comp_(comp)
{
    for (; first != last; ++first)
        insert(*first);
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(std::initializer_list<Key> init, const Compare& comp)
    : size_(0), comp_(comp)
{
    for (const auto& v : init)
        insert(v);
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(const RedBlackTree& other)
    : size_(other.size_), comp_(other.comp_)
{
    root_ = deep_copy(other.root_, nullptr);
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(RedBlackTree&& other) noexcept
    : root_(std::move(other.root_)), size_(other.size_), comp_(std::move(other.comp_))
{
    other.size_ = 0;
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>&
RedBlackTree<Key, Compare>::operator=(const RedBlackTree& other) {
    if (this != &other) {
        RedBlackTree tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>&
RedBlackTree<Key, Compare>::operator=(RedBlackTree&& other) noexcept {
    if (this != &other) {
        root_ = std::move(other.root_);
        size_ = other.size_;
        comp_ = std::move(other.comp_);
        other.size_ = 0;
    }
    return *this;
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>&
RedBlackTree<Key, Compare>::operator=(std::initializer_list<Key> init) {
    clear();
    for (const auto& v : init)
        insert(v);
    return *this;
}


template <typename Key, typename Compare>
bool RedBlackTree<Key, Compare>::empty() const noexcept {
    return size_ == 0;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::size_type
RedBlackTree<Key, Compare>::size() const noexcept {
    return size_;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::NodePtr&
RedBlackTree<Key, Compare>::owner_of(const NodePtr& node) {
    auto par = node->parent.lock();
    if (!par) return root_;
    if (node == par->left) return par->left;
    return par->right;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::rotate_left(NodePtr node) {
    auto child = node->right;

    // child's left becomes node's right
    node->right = child->left;
    if (node->right)
        node->right->parent = node;

    // child takes node's place
    child->parent = node->parent;
    NodePtr& slot = owner_of(node);
    slot = child;

    // node becomes child's left
    child->left = node;
    node->parent = child;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::rotate_right(NodePtr node) {
    auto child = node->left;
    node->left = child->right;
    if (node->left)
        node->left->parent = node;

    child->parent = node->parent;
    NodePtr& slot = owner_of(node);
    slot = child;
    child->right = node;
    node->parent = child;
}

template <typename Key, typename Compare>
template <typename K>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::insert_impl(K&& key) {
    NodePtr parent = nullptr;
    NodePtr curr = root_;
    while (curr) {
        parent = curr;
        if (comp_(key, curr->data))
            curr = curr->left;
        else if (comp_(curr->data, key))
            curr = curr->right;
        else
            return {iterator(curr, this), false};
    }

    auto node = std::make_shared<Node>(std::forward<K>(key), RBColor::RED, parent);
    if (!parent)
        root_ = node;
    else if (comp_(node->data, parent->data))
        parent->left = node;
    else
        parent->right = node;

    ++size_;
    fix_insert(node);

    return {iterator(node, this), true};
}

template <typename Key, typename Compare>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::insert(const Key& key) {
    return insert_impl(key);
}

template <typename Key, typename Compare>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::insert(Key&& key) {
    return insert_impl(std::move(key));
}

template <typename Key, typename Compare>
template <typename... Args>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::emplace(Args&&... args) {
    return insert_impl(Key(std::forward<Args>(args)...));
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::erase(iterator pos) {
    auto n = pos.node_.lock();
    if (!n) 
        return end();

    iterator next = pos;
    ++next;
    erase_node(n);

    return next;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::size_type
RedBlackTree<Key, Compare>::erase(const Key& key) {
    auto z = root_;
    while (z) {
        if (comp_(key, z->data))
            z = z->left;
        else if (comp_(z->data, key))
            z = z->right;
        else {
            erase_node(z);
            return 1;
        }
    }

    return 0;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::erase_node(NodePtr z) {
    NodePtr x;
    NodePtr x_parent;
    RBColor y_original_color;
    if (!z->left) {
        x = z->right;
        x_parent = z->parent.lock();
        y_original_color = z->color;
        if (x) 
            x->parent = z->parent;

        owner_of(z) = x;
    }
    else if (!z->right) {
        x = z->left;
        x_parent = z->parent.lock();
        y_original_color = z->color;
        if (x) 
            x->parent = z->parent;

        owner_of(z) = x;
    }
    else {
        auto y = min_node(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent.lock() == z) {
            x_parent = y;
            if (x) x->parent = y;

            // y takes z's place
            y->left = z->left;
            if (y->left)    
                y->left->parent = y;
                
            y->color = z->color;
            y->parent = z->parent;
            owner_of(z) = y;
        }
        else {
            x_parent = y->parent.lock();

            // Detach y: y's right child replaces y
            if (x) x->parent = y->parent;
            owner_of(y) = x;

            // y takes z's subtrees
            y->right = z->right;
            if (y->right) y->right->parent = y;
            y->left = z->left;
            if (y->left) y->left->parent = y;
            y->color = z->color;
            y->parent = z->parent;
            owner_of(z) = y;
        }
    }

    --size_;
    if (y_original_color == RBColor::BLACK && x)
        fix_delete(x);
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::clear() noexcept {
    root_.reset();
    size_ = 0;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::swap(RedBlackTree& other) noexcept {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::fix_insert(NodePtr node) {
    while (node != root_ && node->color == RBColor::RED
           && node->parent.lock()->color == RBColor::RED) {
        auto par = node->parent.lock();
        auto gp = par->parent.lock();

        if (par == gp->left) {
            auto uncle = gp->right;
            if (uncle && uncle->color == RBColor::RED) {
                gp->color = RBColor::RED;
                par->color = RBColor::BLACK;
                uncle->color = RBColor::BLACK;
                node = gp;
            }
            else {
                if (node == par->right) {
                    rotate_left(par);
                    node = par;
                    par = node->parent.lock();
                }
                rotate_right(gp);
                std::swap(par->color, gp->color);
                node = par;
            }
        }
        else {
            auto uncle = gp->left;
            if (uncle && uncle->color == RBColor::RED) {
                gp->color = RBColor::RED;
                uncle->color = RBColor::BLACK;
                par->color = RBColor::BLACK;
                node = gp;
            }
            else {
                if (node == par->left) {
                    rotate_right(par);
                    node = par;
                    par = node->parent.lock();
                }
                rotate_left(gp);
                std::swap(par->color, gp->color);
                node = par;
            }
        }
    }
    root_->color = RBColor::BLACK;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::fix_delete(NodePtr node) {
    while (node != root_ && node->color == RBColor::BLACK) {
        auto par = node->parent.lock();
        if (node == par->left) {
            auto s = par->right;
            if (s->color == RBColor::RED) {
                s->color = RBColor::BLACK;
                par->color = RBColor::RED;
                rotate_left(par);
                par = node->parent.lock();
                s = par->right;
            }
            if ((!s->left || s->left->color == RBColor::BLACK) &&
                (!s->right || s->right->color == RBColor::BLACK)) {
                s->color = RBColor::RED;
                node = par;
            }
            else {
                if (!s->right || s->right->color == RBColor::BLACK) {
                    if (s->left) s->left->color = RBColor::BLACK;
                    s->color = RBColor::RED;
                    rotate_right(s);
                    par = node->parent.lock();
                    s = par->right;
                }
                s->color = par->color;
                par->color = RBColor::BLACK;
                if (s->right) 
                    s->right->color = RBColor::BLACK;

                rotate_left(par);
                node = root_;
            }
        }
        else {
            auto s = par->left;
            if (s->color == RBColor::RED) {
                s->color = RBColor::BLACK;
                par->color = RBColor::RED;
                rotate_right(par);
                par = node->parent.lock();
                s = par->left;
            }
            if ((!s->left || s->left->color == RBColor::BLACK) &&
                (!s->right || s->right->color == RBColor::BLACK)) {
                s->color = RBColor::RED;
                node = par;
            }
            else {
                if (!s->left || s->left->color == RBColor::BLACK) {
                    if (s->right) s->right->color = RBColor::BLACK;
                    s->color = RBColor::RED;
                    rotate_left(s);
                    par = node->parent.lock();
                    s = par->left;
                }

                s->color = par->color;
                par->color = RBColor::BLACK;
                if (s->left) 
                    s->left->color = RBColor::BLACK;

                rotate_right(par);
                node = root_;
            }
        }
    }
    node->color = RBColor::BLACK;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::find(const Key& key) const {
    auto curr = root_;
    while (curr) {
        if (comp_(key, curr->data))
            curr = curr->left;
        else if (comp_(curr->data, key))
            curr = curr->right;
        else
            return iterator(curr, this);
    }

    return end();
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::size_type
RedBlackTree<Key, Compare>::count(const Key& key) const {
    return find(key) != end() ? 1 : 0;
}

template <typename Key, typename Compare>
bool RedBlackTree<Key, Compare>::contains(const Key& key) const {
    return find(key) != end();
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::lower_bound(const Key& key) const {
    auto curr = root_;
    NodePtr result;
    while (curr) {
        if (!comp_(curr->data, key)) {
            result = curr;
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return iterator(result, this);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::upper_bound(const Key& key) const {
    auto curr = root_;
    NodePtr result;
    while (curr) {
        if (comp_(key, curr->data)) {
            result = curr;
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return iterator(result, this);
}

template <typename Key, typename Compare>
std::pair<typename RedBlackTree<Key, Compare>::iterator,
          typename RedBlackTree<Key, Compare>::iterator>
RedBlackTree<Key, Compare>::equal_range(const Key& key) const {
    return {lower_bound(key), upper_bound(key)};
}

// --- Min / Max ---

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::NodePtr
RedBlackTree<Key, Compare>::min_node(NodePtr node) const {
    while (node->left)
        node = node->left;

    return node;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::NodePtr
RedBlackTree<Key, Compare>::max_node(NodePtr node) const {
    while (node->right)
        node = node->right;

    return node;
}

// --- Iterators ---

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::begin() const noexcept {
    if (!root_) 
        return end();

    return iterator(min_node(root_), this);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::end() const noexcept {
    return iterator(nullptr, this);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::const_iterator
RedBlackTree<Key, Compare>::cbegin() const noexcept { return begin(); }

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::const_iterator
RedBlackTree<Key, Compare>::cend() const noexcept { return end(); }

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::reverse_iterator
RedBlackTree<Key, Compare>::rbegin() const noexcept { return reverse_iterator(end()); }

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::reverse_iterator
RedBlackTree<Key, Compare>::rend() const noexcept { return reverse_iterator(begin()); }

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::const_reverse_iterator
RedBlackTree<Key, Compare>::crbegin() const noexcept { return const_reverse_iterator(end()); }

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::const_reverse_iterator
RedBlackTree<Key, Compare>::crend() const noexcept { return const_reverse_iterator(begin()); }

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::key_compare
RedBlackTree<Key, Compare>::key_comp() const { return comp_; }

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::value_compare
RedBlackTree<Key, Compare>::value_comp() const { return comp_; }


template <typename Key, typename Compare>
bool operator==(const RedBlackTree<Key, Compare>& lhs,
                const RedBlackTree<Key, Compare>& rhs) {
    if (lhs.size() != rhs.size()) 
        return false;

    auto it1 = lhs.begin(), it2 = rhs.begin();
    for (; it1 != lhs.end(); ++it1, ++it2)
        if (*it1 != *it2) 
            return false;
            
    return true;
}

template <typename Key, typename Compare>
bool operator!=(const RedBlackTree<Key, Compare>& lhs,
                const RedBlackTree<Key, Compare>& rhs) {
    return !(lhs == rhs);
}

template <typename Key, typename Compare>
bool operator<(const RedBlackTree<Key, Compare>& lhs,
               const RedBlackTree<Key, Compare>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                        rhs.begin(), rhs.end());
}

template <typename Key, typename Compare>
bool operator<=(const RedBlackTree<Key, Compare>& lhs,
                const RedBlackTree<Key, Compare>& rhs) {
    return !(rhs < lhs);
}

template <typename Key, typename Compare>
bool operator>(const RedBlackTree<Key, Compare>& lhs,
               const RedBlackTree<Key, Compare>& rhs) {
    return rhs < lhs;
}

template <typename Key, typename Compare>
bool operator>=(const RedBlackTree<Key, Compare>& lhs,
                const RedBlackTree<Key, Compare>& rhs) {
    return !(lhs < rhs);
}

template <typename Key, typename Compare>
void swap(RedBlackTree<Key, Compare>& lhs,
          RedBlackTree<Key, Compare>& rhs) noexcept {
    lhs.swap(rhs);
}

#endif // RB_TREE_TPP

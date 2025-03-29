#include "Set.hpp"

template <typename T, typename Compare, typename Alloc>
Set<T, Compare, Alloc>::iterator::iterator() : node_(nullptr) {}

template <typename T, typename Compare, typename Alloc>
Set<T, Compare, Alloc>::iterator::iterator(Node<T>* node) : node_(node) {}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator::reference 
Set<T, Compare, Alloc>::iterator::operator*() const { 
    return node_->data; 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator::pointer 
Set<T, Compare, Alloc>::iterator::operator->() const { 
    return &(node_->data); 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator& 
Set<T, Compare, Alloc>::iterator::operator++() { 
    node_ = successor(node_); 
    return *this; 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::iterator::operator++(int) { 
    iterator tmp = *this; 
    node_ = successor(node_); 
    
    return tmp; 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator& 
Set<T, Compare, Alloc>::iterator::operator--() { 
    node_ = predecessor(node_); 
    return *this; 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::iterator::operator--(int) { 
    iterator tmp = *this; 
    node_ = predecessor(node_); 
    
    return tmp; 
}

template <typename T, typename Compare, typename Alloc>
bool Set<T, Compare, Alloc>::iterator::operator==(const iterator& other) const { 
    return node_ == other.node_; 
}

template <typename T, typename Compare, typename Alloc>
bool Set<T, Compare, Alloc>::iterator::operator!=(const iterator& other) const { 
    return node_ != other.node_; 
}

template <typename T, typename Compare, typename Alloc>
Set<T, Compare, Alloc>::Set() : root_(nullptr) {}

template <typename T, typename Compare, typename Alloc>
Set<T, Compare, Alloc>::Set(const Compare& comp) : root_(nullptr), comp_(comp) {}

template <typename T, typename Compare, typename Alloc>
template<typename InputIt>
Set<T, Compare, Alloc>::Set(InputIt first, InputIt last, const Compare& comp, const Alloc& alloc)
    : root_(nullptr), comp_(comp), allocator_(alloc) {
    insert(first, last);
}

template <typename T, typename Compare, typename Alloc>
Set<T, Compare, Alloc>::Set(std::initializer_list<T> init, const Compare& comp, const Alloc& alloc)
    : root_(nullptr), comp_(comp), allocator_(alloc) {
    insert(init.begin(), init.end());
}

template <typename T, typename Compare, typename Alloc>
Set<T, Compare, Alloc>::~Set() { 
    clear(); 
}

template <typename T, typename Compare, typename Alloc>
bool Set<T, Compare, Alloc>::empty() const { 
    return root_ == nullptr; 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::size_type 
Set<T, Compare, Alloc>::size() const { 
    return size_helper(root_); 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::size_type 
Set<T, Compare, Alloc>::max_size() const { 
    return allocator_.max_size(); 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::begin() { 
    return iterator(minimum(root_)); 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::end() { 
    return iterator(nullptr); 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::const_iterator 
Set<T, Compare, Alloc>::begin() const { 
    return const_iterator(minimum(root_)); 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::const_iterator 
Set<T, Compare, Alloc>::end() const { 
    return const_iterator(nullptr); 
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::clear() { 
    delete_tree(root_); 
    root_ = nullptr; 
}

template <typename T, typename Compare, typename Alloc>
std::pair<typename Set<T, Compare, Alloc>::iterator, bool> 
Set<T, Compare, Alloc>::insert(const T& key) {
    Node<T>* existing = find_node(key);
    if (existing){ 
        return std::make_pair(iterator(existing), false);
    }
    
    Node<T>* node = allocator_.allocate(1);
    std::allocator_traits<Alloc>::construct(allocator_, node, key);
    insert_node(node);

    return std::make_pair(iterator(node), true);
}

template <typename T, typename Compare, typename Alloc>
template<typename InputIt>
void Set<T, Compare, Alloc>::insert(InputIt first, InputIt last) {
    for (; first != last; ++first) {
        insert(*first);
    }
}

template <typename T, typename Compare, typename Alloc>
template<typename... Args>
std::pair<typename Set<T, Compare, Alloc>::iterator, bool> 
Set<T, Compare, Alloc>::emplace(Args&&... args) {
    Node<T>* node = allocator_.allocate(1);
    std::allocator_traits<Alloc>::construct(allocator_, node, std::forward<Args>(args)...);
    
    Node<T>* existing = find_node(node->data);
    if (existing) {
        std::allocator_traits<Alloc>::destroy(allocator_, node);
        allocator_.deallocate(node, 1);
        
        return std::make_pair(iterator(existing), false);
    }
    
    insert_node(node);
    return std::make_pair(iterator(node), true);
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::erase(iterator pos) {
    if (pos == end()){
        return end();
    }
    
    iterator next = pos;
    ++next;
    erase(*pos);
    
    return next;
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::size_type 
Set<T, Compare, Alloc>::erase(const T& key) {
    Node<T>* node = find_node(key);
    if (node) {
        remove(key);
        return 1;
    }
    
    return 0;
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::swap(Set& other) noexcept(
    std::allocator_traits<Alloc>::is_always_equal::value &&
    std::is_nothrow_swappable<Compare>::value) 
{
    std::swap(root_, other.root_);
    std::swap(comp_, other.comp_);
    std::swap(allocator_, other.allocator_);
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::size_type 
Set<T, Compare, Alloc>::count(const T& key) const { 
    return find_node(key) ? 1 : 0; 
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::find(const T& key) { 
    return iterator(find_node(key)); 
}

template <typename T, typename Compare, typename Alloc>
bool Set<T, Compare, Alloc>::contains(const T& key) const { 
    return find_node(key) != nullptr; 
}

template <typename T, typename Compare, typename Alloc>
std::pair<typename Set<T, Compare, Alloc>::iterator, typename Set<T, Compare, Alloc>::iterator> 
Set<T, Compare, Alloc>::equal_range(const T& key) {
    iterator lower = lower_bound(key);
    iterator upper = upper_bound(key);
    
    return std::make_pair(lower, upper);
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::lower_bound(const T& key) {
    Node<T>* node = root_;
    Node<T>* result = nullptr;
    
    while (node) {
        if (!comp_(node->data, key)) {
            result = node;
            node = node->left;
        } 
        else {
            node = node->right;
        }
    }

    return iterator(result);
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::iterator 
Set<T, Compare, Alloc>::upper_bound(const T& key) {
    Node<T>* node = root_;
    Node<T>* result = nullptr;
    
    while (node) {
        if (comp_(key, node->data)) {
            result = node;
            node = node->left;
        } 
        else {
            node = node->right;
        }
    }

    return iterator(result);
}

template <typename T, typename Compare, typename Alloc>
Compare Set<T, Compare, Alloc>::key_comp() const { 
    return comp_; 
}

template <typename T, typename Compare, typename Alloc>
Compare Set<T, Compare, Alloc>::value_comp() const { 
    return comp_; 
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::insert_node(Node<T>* node) {
    Node<T>* parent = nullptr;
    Node<T>* curr = root_;

    while (curr != nullptr) {
        parent = curr;
        if (comp_(node->data, curr->data)) {
            curr = curr->left;
        } 
        else {
            curr = curr->right;
        }
    }

    node->parent = parent;
    if (parent == nullptr) {
        root_ = node;
    } 
    else if (comp_(node->data, parent->data)) {
        parent->left = node;
    } 
    else {
        parent->right = node;
    }

    fix_insert(node);
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::remove(const T& key) {
    Node<T>* node = find_node(key);
    if (!node) return;
    
    Node<T>* y = node;
    Node<T>* x;
    COLOR y_original_color = y->color;

    if (node->left == nullptr) {
        x = node->right;
        transplant(node, node->right);
    }
    else if (node->right == nullptr) {
        x = node->left;
        transplant(node, node->left);
    } 
    else {
        y = minimum(node->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == node) {
            if (x) x->parent = y;
        } 
        else {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }

        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    std::allocator_traits<Alloc>::destroy(allocator_, node);
    allocator_.deallocate(node, 1);
    
    if (y_original_color == COLOR::BLACK) {
        fix_delete(x);
    }
}

template <typename T, typename Compare, typename Alloc>
Node<T>* Set<T, Compare, Alloc>::find_node(const T& key) const {
    Node<T>* curr = root_;
    while (curr != nullptr) {
        if (!comp_(key, curr->data) && !comp_(curr->data, key)) {
            return curr;
        }
        
        curr = comp_(key, curr->data) ? curr->left : curr->right;
    }

    return nullptr;
}

template <typename T, typename Compare, typename Alloc>
Node<T>* Set<T, Compare, Alloc>::minimum(Node<T>* node) const {
    while(node && node->left){
        node = node->left;
    }

    return node;
}

template <typename T, typename Compare, typename Alloc>
Node<T>* Set<T, Compare, Alloc>::maximum(Node<T>* node) const {
    while (node && node->right){
        node = node->right;
    }

    return node;
}

template <typename T, typename Compare, typename Alloc>
Node<T>* Set<T, Compare, Alloc>::successor(Node<T>* node) const {
    if(!node){
        return nullptr;
    }
    if(node->right){ 
        return minimum(node->right);
    }

    Node<T>* parent = node->parent;
    while(parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

template <typename T, typename Compare, typename Alloc>
Node<T>* Set<T, Compare, Alloc>::predecessor(Node<T>* node) const {
    if (!node){ 
        return nullptr;
    }
    if (node->left){ 
        return maximum(node->left);
    }

    Node<T>* parent = node->parent;
    while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::rotate_left(Node<T>* node) {
    Node<T>* child = node->right;
    node->right = child->left;
    if (node->right){
        node->right->parent = node;
    }
    
    child->parent = node->parent;
    if (!node->parent) {
        root_ = child;
    } 
    else if (node == node->parent->left) {
        node->parent->left = child;
    } 
    else {
        node->parent->right = child;
    }

    child->left = node;
    node->parent = child;
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::rotate_right(Node<T>* node) {
    Node<T>* child = node->left;
    node->left = child->right;
    if (node->left){ 
        node->left->parent = node;
    }
    
    child->parent = node->parent;
    if (!node->parent) {
        root_ = child;
    } 
    else if (node == node->parent->left) {
        node->parent->left = child;
    } 
    else {
        node->parent->right = child;
    }
    
    child->right = node;
    node->parent = child;
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::fix_insert(Node<T>* node) {
    while (node != root_ && node->parent->color == COLOR::RED) {
        Node<T>* parent = node->parent;
        Node<T>* grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node<T>* uncle = grandparent->right;
            if (uncle && uncle->color == COLOR::RED) {
                grandparent->color = COLOR::RED;
                parent->color = COLOR::BLACK;
                uncle->color = COLOR::BLACK;
                node = grandparent;
            } 
            else {
                if (node == parent->right) {
                    rotate_left(parent);
                    node = parent;
                    parent = node->parent;
                }
                
                rotate_right(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } 
        else {
            Node<T>* uncle = grandparent->left;
            if (uncle && uncle->color == COLOR::RED) {
                grandparent->color = COLOR::RED;
                parent->color = COLOR::BLACK;
                uncle->color = COLOR::BLACK;
                node = grandparent;
            } 
            else {
                if (node == parent->left) {
                    rotate_right(parent);
                    node = parent;
                    parent = node->parent;
                }
                
                rotate_left(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    root_->color = COLOR::BLACK;
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::fix_delete(Node<T>* node) {
    while (node != root_ && (!node || node->color == COLOR::BLACK)) {
        if (node == node->parent->left) {
            Node<T>* sibling = node->parent->right;
            if (sibling->color == COLOR::RED) {
                sibling->color = COLOR::BLACK;
                node->parent->color = COLOR::RED;
                rotate_left(node->parent);
                sibling = node->parent->right;
            }
            
            if ((!sibling->left || sibling->left->color == COLOR::BLACK) &&
                (!sibling->right || sibling->right->color == COLOR::BLACK)) {
                sibling->color = COLOR::RED;
                node = node->parent;
            } 
            else {
                if (!sibling->right || sibling->right->color == COLOR::BLACK) {
                    if (sibling->left){
                        sibling->left->color = COLOR::BLACK;
                    }

                    sibling->color = COLOR::RED;
                    rotate_right(sibling);
                    sibling = node->parent->right;
                }

                sibling->color = node->parent->color;
                node->parent->color = COLOR::BLACK;
                if (sibling->right){
                    sibling->right->color = COLOR::BLACK;
                }

                rotate_left(node->parent);
                node = root_;
            }
        } 
        else {
            Node<T>* sibling = node->parent->left;
            if (sibling->color == COLOR::RED) {
                sibling->color = COLOR::BLACK;
                node->parent->color = COLOR::RED;
                rotate_right(node->parent);
                sibling = node->parent->left;
            }
            if ((!sibling->left || sibling->left->color == COLOR::BLACK) &&
                (!sibling->right || sibling->right->color == COLOR::BLACK)) {
                sibling->color = COLOR::RED;
                node = node->parent;
            } 
            else {
                if (!sibling->left || sibling->left->color == COLOR::BLACK) {
                    if (sibling->right){
                        sibling->right->color = COLOR::BLACK;
                    }

                    sibling->color = COLOR::RED;
                    rotate_left(sibling);
                    sibling = node->parent->left;
                }

                sibling->color = node->parent->color;
                node->parent->color = COLOR::BLACK;
                if (sibling->left){
                    sibling->left->color = COLOR::BLACK;
                }
                
                rotate_right(node->parent);
                node = root_;
            }
        }
    }
    if (node){ 
        node->color = COLOR::BLACK;
    }
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::transplant(Node<T>* u, Node<T>* v) {
    if (!u->parent) {
        root_ = v;
    } 
    else if (u == u->parent->left) {
        u->parent->left = v;
    } 
    else {
        u->parent->right = v;
    }

    if (v){ 
        v->parent = u->parent;
    }
}

template <typename T, typename Compare, typename Alloc>
void Set<T, Compare, Alloc>::delete_tree(Node<T>* node) {
    if (node) {
        delete_tree(node->left);
        delete_tree(node->right);
        std::allocator_traits<Alloc>::destroy(allocator_, node);
        allocator_.deallocate(node, 1);
    }
}

template <typename T, typename Compare, typename Alloc>
typename Set<T, Compare, Alloc>::size_type 
Set<T, Compare, Alloc>::size_helper(Node<T>* node) const {
    if (!node){ 
        return 0;
    }

    return 1 + size_helper(node->left) + size_helper(node->right);
}

template<typename T, typename Compare, typename Alloc>
bool operator==(const Set<T, Compare, Alloc>& lhs, const Set<T, Compare, Alloc>& rhs) {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename Compare, typename Alloc>
bool operator<(const Set<T, Compare, Alloc>& lhs,const Set<T, Compare, Alloc>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs.key_comp());
}

template<typename T, typename Compare, typename Alloc>
void swap(Set<T, Compare, Alloc>& lhs, Set<T, Compare, Alloc>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

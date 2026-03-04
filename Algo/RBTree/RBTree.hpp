#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "RBNode.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>

template <typename Key, typename Compare = std::less<Key>>
class RedBlackTree {
public:
    // --- Standard container type aliases ---
    using key_type        = Key;
    using value_type      = Key;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare     = Compare;
    using value_compare   = Compare;
    using reference       = const value_type&;
    using const_reference = const value_type&;

private:
    using Node    = RBNode<Key>;
    using NodePtr = std::shared_ptr<Node>;

public:
    // --- Iterator ---
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type      = Key;
        using difference_type = std::ptrdiff_t;
        using pointer         = const Key*;
        using reference       = const Key&;

        iterator() = default;

        reference operator*() const { return node_.lock()->data; }
        pointer operator->() const { return &node_.lock()->data; }

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        bool operator==(const iterator& other) const {
            return node_.lock() == other.node_.lock();
        }
        bool operator!=(const iterator& other) const {
            return node_.lock() != other.node_.lock();
        }

    private:
        friend class RedBlackTree;
        std::weak_ptr<Node> node_;
        const RedBlackTree* tree_ = nullptr;

        iterator(NodePtr node, const RedBlackTree* tree)
            : node_(node), tree_(tree) {}
    };

    using const_iterator         = iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // --- Constructors / destructor / assignment ---
    RedBlackTree() : size_(0), comp_() {}
    explicit RedBlackTree(const Compare& comp) : size_(0), comp_(comp) {}

    template <typename InputIt>
    RedBlackTree(InputIt first, InputIt last, const Compare& comp = Compare());

    RedBlackTree(std::initializer_list<Key> init, const Compare& comp = Compare());

    RedBlackTree(const RedBlackTree& other);
    RedBlackTree(RedBlackTree&& other) noexcept;

    RedBlackTree& operator=(const RedBlackTree& other);
    RedBlackTree& operator=(RedBlackTree&& other) noexcept;
    RedBlackTree& operator=(std::initializer_list<Key> init);

    ~RedBlackTree() = default;

    // --- Capacity ---
    bool empty() const noexcept;
    size_type size() const noexcept;

    // --- Modifiers ---
    std::pair<iterator, bool> insert(const Key& key);
    std::pair<iterator, bool> insert(Key&& key);

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    iterator erase(iterator pos);
    size_type erase(const Key& key);

    void clear() noexcept;
    void swap(RedBlackTree& other) noexcept;

    // --- Lookup ---
    iterator find(const Key& key) const;
    size_type count(const Key& key) const;
    bool contains(const Key& key) const;

    iterator lower_bound(const Key& key) const;
    iterator upper_bound(const Key& key) const;
    std::pair<iterator, iterator> equal_range(const Key& key) const;

    // --- Iterators ---
    iterator begin() const noexcept;
    iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // --- Observers ---
    key_compare key_comp() const;
    value_compare value_comp() const;

private:
    NodePtr root_;
    size_type size_;
    Compare comp_;

    void rotate_left(NodePtr node);
    void rotate_right(NodePtr node);
    void fix_insert(NodePtr node);
    void fix_delete(NodePtr node);

    NodePtr min_node(NodePtr node) const;
    NodePtr max_node(NodePtr node) const;

    NodePtr& owner_of(const NodePtr& node);

    template <typename K>
    std::pair<iterator, bool> insert_impl(K&& key);

    void erase_node(NodePtr z);

    NodePtr deep_copy(const NodePtr& src, NodePtr parent) const;
};

template <typename Key, typename Compare>
bool operator==(const RedBlackTree<Key, Compare>& lhs, const RedBlackTree<Key, Compare>& rhs);

template <typename Key, typename Compare>
bool operator!=(const RedBlackTree<Key, Compare>& lhs, const RedBlackTree<Key, Compare>& rhs);

template <typename Key, typename Compare>
bool operator<(const RedBlackTree<Key, Compare>& lhs, const RedBlackTree<Key, Compare>& rhs);

template <typename Key, typename Compare>
bool operator<=(const RedBlackTree<Key, Compare>& lhs, const RedBlackTree<Key, Compare>& rhs);

template <typename Key, typename Compare>
bool operator>(const RedBlackTree<Key, Compare>& lhs, const RedBlackTree<Key, Compare>& rhs);

template <typename Key, typename Compare>
bool operator>=(const RedBlackTree<Key, Compare>& lhs, const RedBlackTree<Key, Compare>& rhs);

template <typename Key, typename Compare>
void swap(RedBlackTree<Key, Compare>& lhs, RedBlackTree<Key, Compare>& rhs) noexcept;

#include "RBTree.tpp"

#endif // RB_TREE_HPP

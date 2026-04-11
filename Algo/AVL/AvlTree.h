#ifndef AVL_H
#define AVL_H

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>

template <typename T, typename Compare = std::less<T>>
class AVL {
private:
    struct Node {
        T value;
        std::size_t height;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent;

        explicit Node(const T& v, Node* p = nullptr)
            : value(v), height(1), parent(p) {}
        explicit Node(T&& v, Node* p = nullptr)
            : value(std::move(v)), height(1), parent(p) {}
    };

public:
    using key_type        = T;
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare     = Compare;
    using value_compare   = Compare;
    using reference       = const value_type&;
    using const_reference = const value_type&;

    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type      = T;
        using difference_type = std::ptrdiff_t;
        using pointer         = const T*;
        using reference       = const T&;

        iterator() = default;

        reference operator*() const { return node_->value; }
        pointer operator->() const { return &node_->value; }

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        bool operator==(const iterator& other) const { return node_ == other.node_; }
        bool operator!=(const iterator& other) const { return node_ != other.node_; }

    private:
        friend class AVL;
        Node* node_ = nullptr;
        const AVL* tree_ = nullptr;

        iterator(Node* n, const AVL* t) : node_(n), tree_(t) {}
    };

    using const_iterator         = iterator;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    AVL() : root_(nullptr), size_(0), comp_() {}
    explicit AVL(const Compare& comp) : root_(nullptr), size_(0), comp_(comp) {}

    template <typename InputIt>
    AVL(InputIt first, InputIt last, const Compare& comp = Compare());

    AVL(std::initializer_list<T> init, const Compare& comp = Compare());

    AVL(const AVL& other);
    AVL(AVL&& other) noexcept;

    AVL& operator=(const AVL& other);
    AVL& operator=(AVL&& other) noexcept;
    AVL& operator=(std::initializer_list<T> init);

    ~AVL() = default;

    bool empty() const noexcept;
    size_type size() const noexcept;

    std::pair<iterator, bool> insert(const T& value);
    std::pair<iterator, bool> insert(T&& value);

    template <typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    iterator erase(iterator pos);
    size_type erase(const T& value);

    void clear() noexcept;
    void swap(AVL& other) noexcept;

    iterator find(const T& value) const;
    size_type count(const T& value) const;
    bool contains(const T& value) const;

    iterator lower_bound(const T& value) const;
    iterator upper_bound(const T& value) const;
    std::pair<iterator, iterator> equal_range(const T& value) const;

    iterator begin() const noexcept;
    iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    template <typename F> void pre_order(F f) const;
    template <typename F> void in_order(F f) const;
    template <typename F> void post_order(F f) const;

    key_compare key_comp() const { return comp_; }
    value_compare value_comp() const { return comp_; }

private:
    std::unique_ptr<Node> root_;
    size_type size_;
    Compare comp_;

    std::unique_ptr<Node>& owner_of(Node* node);
    std::unique_ptr<Node> detach(Node* node);
    void attach_as_child(Node* parent, std::unique_ptr<Node> child, bool as_left);

    static std::size_t height_of(const Node* node);
    static void update_height(Node* node);
    static int balance_factor(const Node* node);

    std::unique_ptr<Node> rotate_left(std::unique_ptr<Node> x);
    std::unique_ptr<Node> rotate_right(std::unique_ptr<Node> x);
    std::unique_ptr<Node> rebalance(std::unique_ptr<Node> node);
    void rebalance_path(Node* from);

    template <typename V>
    std::pair<Node*, bool> insert_impl(V&& value);

    void erase_node(Node* z);

    static Node* min_node(Node* node);
    static Node* max_node(Node* node);

    std::unique_ptr<Node> clone(const Node* src, Node* parent);

    template <typename F> static void pre_order_impl(const Node* node, F& f);
    template <typename F> static void in_order_impl(const Node* node, F& f);
    template <typename F> static void post_order_impl(const Node* node, F& f);
};

template <typename T, typename Compare>
bool operator==(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs);

template <typename T, typename Compare>
bool operator!=(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs);

template <typename T, typename Compare>
bool operator<(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs);

template <typename T, typename Compare>
bool operator<=(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs);

template <typename T, typename Compare>
bool operator>(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs);

template <typename T, typename Compare>
bool operator>=(const AVL<T, Compare>& lhs, const AVL<T, Compare>& rhs);

template <typename T, typename Compare>
void swap(AVL<T, Compare>& lhs, AVL<T, Compare>& rhs) noexcept;

#include "AvlTree.tpp"

#endif // AVL_H
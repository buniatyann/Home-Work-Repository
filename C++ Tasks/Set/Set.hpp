#ifndef SET_HPP
#define SET_HPP

#include <algorithm>
#include <iterator>
#include <memory>
#include <functional>
enum class COLOR { RED, BLACK };

template <typename T>
struct Node {
    T data;
    COLOR color;
    Node* left;
    Node* right;
    Node* parent;

    Node(const T& d) : data(d), color(COLOR::RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T>>
class Set {
public:
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator();
        explicit iterator(Node<T>* node);

        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

    private:
        Node<T>* node_;
    };

    using const_iterator = iterator; // ? 
    using size_type = std::size_t;

    // Constructors
    Set();
    explicit Set(const Compare& comp);
    
    template<typename InputIt>
    Set(InputIt first, InputIt last, const Compare& comp = Compare(),
        const Alloc& alloc = Alloc());
    
    Set(std::initializer_list<T> init, const Compare& comp = Compare(),
        const Alloc& alloc = Alloc());
    
    ~Set();

    // Capacity
    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    // Iterators
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Modifiers
    void clear();
    std::pair<iterator, bool> insert(const T& key);
    
    template<typename InputIt>
    void insert(InputIt first, InputIt last);

    template<typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    iterator erase(iterator pos);
    size_type erase(const T& key);
    void swap(Set& other) noexcept(
        std::allocator_traits<Alloc>::is_always_equal::value &&
        std::is_nothrow_swappable<Compare>::value);

    // Lookup
    size_type count(const T& key) const;
    iterator find(const T& key);
    bool contains(const T& key) const;
    std::pair<iterator, iterator> equal_range(const T& key);
    iterator lower_bound(const T& key);
    iterator upper_bound(const T& key);

    // Observers
    Compare key_comp() const;
    Compare value_comp() const;

private:

    Node<T>* root_;
    Compare comp_;
    Alloc allocator_;

    void insert_node(Node<T>* node);
    void remove(const T& key);
    Node<T>* find_node(const T& key) const;
    Node<T>* minimum(Node<T>* node) const;
    Node<T>* maximum(Node<T>* node) const;
    Node<T>* successor(Node<T>* node) const;
    Node<T>* predecessor(Node<T>* node) const;
    void rotate_left(Node<T>* node);
    void rotate_right(Node<T>* node);
    void fix_insert(Node<T>* node);
    void fix_delete(Node<T>* node);
    void transplant(Node<T>* u, Node<T>* v);
    void delete_tree(Node<T>* node);
    size_type size_helper(Node<T>* node) const;
};


template<typename T, typename Compare, typename Alloc>
bool operator==(const Set<T, Compare, Alloc>& lhs, const Set<T, Compare, Alloc>& rhs);

template<typename T, typename Compare, typename Alloc>
bool operator<(const Set<T, Compare, Alloc>& lhs, const Set<T, Compare, Alloc>& rhs);

template<typename T, typename Compare, typename Alloc>
void swap(Set<T, Compare, Alloc>& lhs, Set<T, Compare, Alloc>& rhs) noexcept(noexcept(lhs.swap(rhs)));

#endif // SET_HPP
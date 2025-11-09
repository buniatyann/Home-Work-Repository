#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <cstddef>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <functional>
#include <initializer_list>
#include <algorithm>

template <typename T>
class DoubleLinkedList {
public:
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        reference operator*() const { return node_->value; }
        pointer operator->() const { return &(node_->value); }
        iterator& operator++() { node_ = node_->next; return *this; }
        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }
        iterator& operator--() { node_ = node_->prev; return *this; }
        iterator operator--(int) { iterator tmp(*this); --(*this); return tmp; }
        bool operator==(const iterator& o) const { return node_ == o.node_; }
        bool operator!=(const iterator& o) const { return !(*this == o); }

    private:
        friend class DoubleLinkedList;
        Node* node_;
        explicit iterator(Node* n) : node_(n) {}
    };

    class const_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        reference operator*() const { return node_->value; }
        pointer operator->() const { return &(node_->value); }
        const_iterator& operator++() { node_ = node_->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp(*this); ++(*this); return tmp; }
        const_iterator& operator--() { node_ = node_->prev; return *this; }
        const_iterator operator--(int) { const_iterator tmp(*this); --(*this); return tmp; }
        bool operator==(const const_iterator& o) const { return node_ == o.node_; }
        bool operator!=(const const_iterator& o) const { return !(*this == o); }

    private:
        friend class DoubleLinkedList;
        const Node* node_;
        explicit const_iterator(const Node* n) : node_(n) {}
    };

    class reverse_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        reference operator*() const { return node_->prev->value; }
        pointer operator->() const { return &(node_->prev->value); }
        reverse_iterator& operator++() { node_ = node_->prev; return *this; }
        reverse_iterator operator++(int) { reverse_iterator tmp(*this); ++(*this); return tmp; }
        reverse_iterator& operator--() { node_ = node_->next; return *this; }
        reverse_iterator operator--(int) { reverse_iterator tmp(*this); --(*this); return tmp; }
        bool operator==(const reverse_iterator& o) const { return node_ == o.node_; }
        bool operator!=(const reverse_iterator& o) const { return !(*this == o); }

    private:
        friend class DoubleLinkedList;
        Node* node_;
        explicit reverse_iterator(Node* n) : node_(n) {}

    };

    class const_reverse_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        reference operator*() const { return node_->prev->value; }
        pointer operator->() const { return &(node_->prev->value); }
        const_reverse_iterator& operator++() { node_ = node_->prev; return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator tmp(*this); ++(*this); return tmp; }
        const_reverse_iterator& operator--() { node_ = node_->next; return *this; }
        const_reverse_iterator operator--(int) { const_reverse_iterator tmp(*this); --(*this); return tmp; }
        bool operator==(const const_reverse_iterator& o) const { return node_ == o.node_; }
        bool operator!=(const const_reverse_iterator& o) const { return !(*this == o); }
        
    private:
        friend class DoubleLinkedList;
        const Node* node_;
        explicit const_reverse_iterator(const Node* n) : node_(n) {}
    };

public:
    DoubleLinkedList();
    DoubleLinkedList(std::initializer_list<T>);
    DoubleLinkedList(const DoubleLinkedList&);
    DoubleLinkedList(DoubleLinkedList&&) noexcept;
    ~DoubleLinkedList();

    DoubleLinkedList& operator=(const DoubleLinkedList&);
    DoubleLinkedList& operator=(DoubleLinkedList&&) noexcept;

    void clear();
    std::size_t size() const noexcept;
    bool empty() const noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void push_front(const T&);
    void push_front(T&&);
    void push_back(const T&);
    void push_back(T&&);

    template <typename... Args> void emplace_front(Args&&...);
    template <typename... Args> void emplace_back(Args&&...);

    void pop_front();
    void pop_back();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    void swap(DoubleLinkedList&) noexcept;
    void reverse() noexcept;

    void splice(DoubleLinkedList&) noexcept;
    void splice(iterator, DoubleLinkedList&, iterator, iterator) noexcept;

    void merge(DoubleLinkedList&);

    void remove(const T&);
    template <typename Predicate> void remove_if(Predicate);

    void unique();
    template <typename BinaryPredicate> 
    void unique(BinaryPredicate);

private:
    template <typename... Args> void insert_after(Node*, Args&&...);
    template <typename... Args> void insert_before(Node*, Args&&...);
    iterator erase(Node*);
    void move_node_after(Node*, Node*);

    Node* head_;
    Node* tail_;
    std::size_t size_;

private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        template <typename... Args>
        explicit Node(Args&&... args)
            : value(std::forward<Args>(args)...), prev(nullptr), next(nullptr) {}
    };

};

#endif // DOUBLE_LINKED_LIST_H
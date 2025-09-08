#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <utility>
#include <exception>
#include <iterator>

// Node definition
template <typename T>
struct Node {
    T value;
    Node* prev;
    Node* next;

    Node(T val) : value(std::move(val)), prev(nullptr), next(nullptr) {}
};

// DoubleLinkedList Class
template <typename T>
class DoubleLinkedList {
public:
    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        iterator(Node<T>* node);
        reference operator*() const;
        pointer operator->();
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

    private:
        Node<T>* node_;
    };

public:
    DoubleLinkedList();
    ~DoubleLinkedList();

public:
    void clear();
    std::size_t size() const;
    bool empty() const;
    void reverse();
    void splice(DoubleLinkedList& rhs);
    void merge(DoubleLinkedList& rhs);
    void push_front(const T& val);
    template <typename... Args> void insert_front(Args&&... vals);
    void push_back(const T& val);
    template <typename... Args> void insert_back(Args&&... vals);
    void pop_back();
    void pop_front();
    DoubleLinkedList& resize(std::size_t size);

    iterator begin();
    iterator end();

private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;
};


#endif // DOUBLE_LINKED_LIST_H

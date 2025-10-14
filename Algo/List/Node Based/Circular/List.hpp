#ifndef CIRCULAR_LIST_HPP
#define CIRCULAR_LIST_HPP

#include "IList.hpp"
#include <cassert>

template <typename T>
class List : public IList<T> {
public:
    List();
    List(const List& other);
    List& operator=(const List& other);
    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;
    ~List() override;

    void insert(const T& value, std::size_t pos) override;
    void insert(T&& value, std::size_t pos) override;
    void push_back(const T& value) override;
    void push_back(T&& value) override;
    void push_front(const T& value) override;
    void push_front(T&& value) override;
    void pop_back() override;
    void pop_front() override;
    void clear() override;
    const T& front() const override;
    T& front() override;
    const T& back() const override;
    T& back() override;
    std::size_t size() const noexcept override;
    bool empty() const noexcept override;
    std::size_t find(const T& value) override;
    const T& at(std::size_t ind) override;

private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value, Node* next = nullptr, Node* prev = nullptr);
        Node(T&& value, Node* next = nullptr, Node* prev = nullptr);
    };

    Node* head;
    Node* tail;
    std::size_t list_size;

    Node* get_node(std::size_t pos) const;
};

#include "List.tpp"

#endif // CIRCULAR_LIST_HPP
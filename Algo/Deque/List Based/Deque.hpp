#ifndef LIST_DEQUE_HPP
#define LIST_DEQUE_HPP

#include "IDeque.hpp"
#include <cstddef>

template <typename T>
class Deque : public IDeque<T> {
public:
    Deque();
    ~Deque() override;
    Deque(const Deque& other);
    Deque& operator=(const Deque& other);
    Deque(Deque&& other) noexcept;
    Deque& operator=(Deque&& other) noexcept;

    void push_front(const T& element) override;
    void push_front(T&& element) override;
    void pop_front() override;
    T& front() override;
    const T& front() const override;

    void push_back(const T& element) override;
    void push_back(T&& element) override;
    void pop_back() override;
    T& back() override;
    const T& back() const override;

    bool empty() const override;
    std::size_t size() const override;

    void clear() override;

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
        Node(T&& value) : data(std::move(value)), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t current_size;

    Node*& get_head();
    Node*& get_tail();
    std::size_t& get_current_size();
};

template <typename T>
void swap(Deque<T>& a, Deque<T>& b) noexcept;

#include "Deque.tpp"

#endif // LIST_DEQUE_HPP
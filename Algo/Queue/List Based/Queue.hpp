#ifndef LIST_QUEUE_HPP
#define LIST_QUEUE_HPP

#include "../Interface/IQueue.hpp"
#include <memory>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue : public IQueue<T> {
public:
    Queue();
    Queue(const Queue& rhs);
    Queue& operator=(const Queue& rhs);
    Queue(Queue&& rhs) noexcept;
    Queue& operator=(Queue&& rhs) noexcept;
    ~Queue() override;

    void enqueue(const T& val) override;
    void dequeue() override;
    std::size_t size() const override;
    bool empty() const override;
    T& front() override;
    const T& front() const override;
    T& back() override;
    const T& back() const override;
    void emplace(const T&);

    void swap(Queue& other) noexcept;

private:
    struct Node {
        T val;
        std::unique_ptr<Node> next;
        Node(const T& val) : val(val) {}
    };
    
    std::unique_ptr<Node> front_;
    std::unique_ptr<Node> back_;
    std::size_t size_;
};

#include "Queue.tpp"

#endif // LIST_QUEUE_HPP
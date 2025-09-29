#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP

#include "../Interface/IQueue.hpp"
#include <vector>
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
     
private:
    std::vector<T> data_;
    std::size_t front_;
    std::size_t rear_;
};

#include "Queue.tpp"

#endif // ARRAY_QUEUE_HPP
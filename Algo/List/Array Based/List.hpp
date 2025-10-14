#ifndef ARRAY_LINKED_LIST_HPP
#define ARRAY_LINKED_LIST_HPP

#include "../Interface/IList.hpp"
#include <cstddef>
#include <stdexcept>
#include <limits>
#include <memory>

template <typename T>
class List : public IList<T> {
public:
    List();
    ~List() = default;
    
    List(const List& other);
    List& operator=(const List& other);
    
    List(List&& other) noexcept;
    List& operator=(List&& other) noexcept;

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
    const T& back() const override;
    T& front() override;
    T& back() override;
    std::size_t size() const noexcept override;
    bool empty() const noexcept override;
    std::size_t find(const T& value) override;
    const T& at(std::size_t ind) const override;

private:
    std::unique_ptr<Node[]> array_;
    std::size_t capacity_;
    std::size_t size_;
    std::size_t head_;  

private:
    struct Node {
        T data;
        std::size_t next; 
        Node(const T& val) : data(val), next(SIZE_MAX) {}
        Node(T&& val) : data(std::move(val)), next(SIZE_MAX) {}
    };

    static constexpr std::size_t INITIAL_CAPACITY = 16;
    static constexpr std::size_t SIZE_MAX = std::numeric_limits<std::size_t>::max();
    
private:
    void resize(std::size_t new_capacity);
    void shrink();
    std::size_t allocate_node(const T& value);
    std::size_t allocate_node(T&& value);
    void deallocate_node(std::size_t idx);
    std::size_t get_node_at_position(std::size_t pos) const;
};

#include "List.tpp"

#endif // ARRAY_LINKED_LIST_HPP
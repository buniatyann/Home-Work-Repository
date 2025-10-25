#ifndef SINGLE_LINKED_LIST_HPP
#define SINGLE_LINKED_LIST_HPP

#include "../../Interface/IList.hpp"
#include "../../Node/Single Linked/SLLNode.hpp"
#include <utility>

template <typename T>
class List : public IList<T> {
public:
    List(std::size_t size = 0);
    List(const List& lst);
    List& operator=(const List& lst);
    List(List&& rhs) noexcept;
    List& operator=(List&& rhs) noexcept;
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
    const T& back() const override;
    T& front() override;
    T& back() override;

    std::size_t size() const noexcept override { return size_; }
    bool empty() const noexcept override { return size_ == 0; }

    std::size_t find(const T& value) override;
    const T& at(std::size_t ind) override;

    const INode<T>* frontNode() const override;
    INode<T>* frontNode() override;

    const INode<T>* backNode() const override;
    INode<T>* backNode() override;

private:
    std::size_t size_;
    SLLNode<T>* front_;
    SLLNode<T>* back_;
};

#include "./List.tpp"

#endif // SINGLE_LINKED_LIST_HPP

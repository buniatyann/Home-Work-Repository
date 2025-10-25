#ifndef CIRCULAR_LIST_HPP
#define CIRCULAR_LIST_HPP

#include "../../Interface/IList.hpp"
#include "../../Node/Single Linked/SLLNode.hpp"
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
    std::size_t find(const T& value) const override;
    const T& at(std::size_t ind) const override;
    const INode<T>* frontNode() const override;
    INode<T>* frontNode() override;
    const INode<T>* backNode() const override;
    INode<T>* backNode() override;

private:
    SLLNode<T>* front_;
    SLLNode<T>* back_;
    std::size_t size_;
};

#include "List.tpp"

#endif // CIRCULAR_LIST_HPP

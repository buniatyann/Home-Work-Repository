#ifndef DOUBLE_LINKED_LIST_NODE_HPP
#define DOUBLE_LINKED_LIST_NODE_HPP

#include "../Interface/INode.hpp"

template <typename T>
struct DLLNode : INode<T> {
    DLLNode(const T& value = T(), INode<T>* next = nullptr, INode<T>* prev = nullptr) 
        : val_(value), next(next), prev(prev) {} 
    DLLNode(T&& value, INode<T>* next = nullptr, INode<T>* prev = nullptr) 
        : val_(std::move(value)), next(next), prev(prev) {}

    const T& val() const override {
        return val_;
    }

    T& val() override {
        return val_;
    }

    ~DLLNode() override {
        prev = nullptr;
        next = nullptr;
    }

    T val_;
    INode<T>* next;
    INode<T>* prev;
};

#endif // DOUBLE_LINKED_LIST_NODE_HPP

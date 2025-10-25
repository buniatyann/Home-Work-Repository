#ifndef SINGLE_LINKED_LIST_NODE_HPP
#define SINGLE_LINKED_LIST_NODE_HPP

#include "../Interface/INode.hpp"

template <typename T>
struct SLLNode : INode<T> {
    SLLNode(const T& value = T(), INode<T>* next = nullptr) : val_(value), next(next) {} 
    SLLNode(T&& value, INode<T>* next = nullptr) : val_(std::move(value)), next(next) {}

    const T& val() const override {
        return val_;
    }

    T& val() override {
        return val_;
    }

    ~SLLNode() override {
        next = nullptr;
    }
    
    INode<T>* next() override {
        return next_;
    }

    T val_;
    SLLNode<T>* next;
};

#endif // SINGLE_LINKED_LIST_NODE_HPP

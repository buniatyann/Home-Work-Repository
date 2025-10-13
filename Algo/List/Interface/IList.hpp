#ifndef ILIST_HPP
#define ILIST_HPP

#include <cstddef>
#include <stdexcept>
#include <cassert>

template <typename T>
class IList {
public:
    virtual ~IList() = default;
    virtual void insert(const T& value, std::size_t pos) = 0;
    virtual void insert(T&& value, std::size_t pos) = 0;
    virtual void push_back(const T& value) = 0;
    virtual void push_back(T&& value) = 0;
    virtual void push_front(const T& value) = 0;
    virtual void push_front(T&& value) = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0; 
    virtual void clear() = 0;
    virtual const T& front() const = 0;
    virtual const T& back() const = 0;
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual std::size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;
    virtual std::size_t find(const T& value) = 0;
    virtual const T& at(std::size_t ind) = 0;
};

#endif // ILIST_HPP
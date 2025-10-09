#ifndef IDEQUE_HPP
#define IDEQUE_HPP

#include <cstddef>

template <typename T>
class IDeque {
public:
    virtual ~IDeque() = 0;
    virtual void push_front(const T& element) = 0;
    virtual void push_front(T&& element)= 0;
    virtual void pop_front() = 0;
    virtual T& front() = 0;
    virtual const T& front() const = 0;

    virtual void push_back(const T& element) = 0;
    virtual void push_back(T&& element) = 0;
    virtual void pop_back() = 0;
    virtual T& back() = 0;
    virtual const T& back() = 0;

    virtual bool empty() const = 0;
    virtual std::size_t size() const = 0;

    virtual void clear() = 0;
};

#endif // IDEQUE_HPP
#ifndef INODE_HPP
#define INODE_HPP

#include <utility>

template <typename T>
struct INode {
    virtual ~INode() = default;
    virtual const T& val() const = 0;
    virtual T& val() = 0;
    virtual INode<T>* next() = 0;
};

#endif // INODE_HPP

#ifndef RB_NODE_HPP
#define RB_NODE_HPP

#include <memory>
#include <utility>

enum class RBColor { RED, BLACK };

template <typename T>
struct RBNode {
    T data;
    RBColor color;
    std::shared_ptr<RBNode> left;
    std::shared_ptr<RBNode> right;
    std::weak_ptr<RBNode> parent;

    explicit RBNode(const T& data, RBColor color = RBColor::RED,
                    std::shared_ptr<RBNode> parent = nullptr)
        : data(data), color(color), parent(parent) {}

    explicit RBNode(T&& data, RBColor color = RBColor::RED,
                    std::shared_ptr<RBNode> parent = nullptr)
        : data(std::move(data)), color(color), parent(parent) {}

    RBNode(const RBNode& other)
        : data(other.data), color(other.color)
    {
        // Deep copy — parent is NOT copied (set by caller)
    }

    RBNode(RBNode&& other) noexcept
        : data(std::move(other.data)),
          color(other.color),
          left(std::move(other.left)),
          right(std::move(other.right)),
          parent(std::move(other.parent))
    {}

    RBNode& operator=(const RBNode& other) {
        if (this != &other) {
            data = other.data;
            color = other.color;
            left.reset();
            right.reset();
            parent.reset();
        }
        return *this;
    }

    RBNode& operator=(RBNode&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            color = other.color;
            left = std::move(other.left);
            right = std::move(other.right);
            parent = std::move(other.parent);
        }
        return *this;
    }

    ~RBNode() = default;
};

#endif // RB_NODE_HPP

#ifndef ARRAY_DEQUE_HPP
#define ARRAY_DEQUE_HPP

#include "IDeque.hpp"
#include <vector>
#include <cstddef>

template <typename T>
class Deque : public IDeque<T> {
public:
    Deque();
    ~Deque() override;
    Deque(const Deque& other);
    Deque& operator=(const Deque& other);
    Deque(Deque&& other) noexcept;
    Deque& operator=(Deque&& other) noexcept;

    void push_front(const T& element) override;
    void push_front(T&& element) override;
    void pop_front() override;
    T& front() override;
    const T& front() const override;

    void push_back(const T& element) override;
    void push_back(T&& element) override;
    void pop_back() override;
    T& back() override;
    const T& back() const override;

    bool empty() const override;
    std::size_t size() const override;

    void clear() override;

private:
    std::vector<T> data;
    std::size_t front_idx;
    std::size_t back_idx;
    std::size_t current_size;

    std::size_t next(std::size_t idx) const;
    std::size_t prev(std::size_t idx) const;
    void resize();

    // Added accessors for swap
    std::vector<T>& get_data();
    std::size_t& get_front_idx();
    std::size_t& get_back_idx();
    std::size_t& get_current_size();
};

template <typename T>
void swap(Deque<T>& a, Deque<T>& b) noexcept;

#include "Deque.tpp"

#endif // ARRAY_DEQUE_HPP
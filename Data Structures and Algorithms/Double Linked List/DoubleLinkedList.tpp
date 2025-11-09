#ifndef DOUBLE_LINKED_LIST_TPP
#define DOUBLE_LINKED_LIST_TPP

#include "DoubleLinkedList.h"

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
    : head_(new Node()), tail_(new Node()), size_(0) {
    head_->next = tail_;
    tail_->prev = head_;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(std::initializer_list<T> init)
    : head_(new Node()), tail_(new Node()), size_(0) {
    head_->next = tail_;
    tail_->prev = head_;
    for (const auto& v : init) 
        push_back(v);
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other)
    : head_(new Node()), tail_(new Node()), size_(0) {
    head_->next = tail_;
    tail_->prev = head_;
    for (const auto& v : other) 
        push_back(v);
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
    other.head_ = new Node();
    other.tail_ = new Node();
    other.head_->next = other.tail_;
    other.tail_->prev = other.head_;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
    delete head_;
    delete tail_;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& other) {
    if (this != &other) {
        clear();
        for (const auto& v : other) 
            push_back(v);
    }

    return *this;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        delete head_;
        delete tail_;
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
        other.head_ = new Node();
        other.tail_ = new Node();
        other.head_->next = other.tail_;
        other.tail_->prev = other.head_;
    }
    
    return *this;
}

template <typename T>
void DoubleLinkedList<T>::clear() {
    Node* cur = head_->next;
    while (cur != tail_) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    
    head_->next = tail_;
    tail_->prev = head_;
    size_ = 0;
}

template <typename T>
std::size_t DoubleLinkedList<T>::size() const noexcept { 
    return size_; 
}

template <typename T>
bool DoubleLinkedList<T>::empty() const noexcept { 
    return size_ == 0; 
}

template <typename T>
T& DoubleLinkedList<T>::front() { 
    return head_->next->value; 
}

template <typename T>
const T& DoubleLinkedList<T>::front() const { 
    return head_->next->value; 
}

template <typename T>
T& DoubleLinkedList<T>::back() { 
    return tail_->prev->value; 
}

template <typename T>
const T& DoubleLinkedList<T>::back() const { 
    return tail_->prev->value; 
}

template <typename T>
void DoubleLinkedList<T>::push_front(const T& val) { 
    insert_after(head_, val); 
}

template <typename T>
void DoubleLinkedList<T>::push_front(T&& val) { 
    insert_after(head_, std::move(val)); 
}

template <typename T>
void DoubleLinkedList<T>::push_back(const T& val) { 
    insert_before(tail_, val); 
}

template <typename T>
void DoubleLinkedList<T>::push_back(T&& val) { 
    insert_before(tail_, std::move(val)); 
}

template <typename T>
template <typename... Args>
void DoubleLinkedList<T>::emplace_front(Args&&... args) { 
    insert_after(head_, std::forward<Args>(args)...); 
}

template <typename T>
template <typename... Args>
void DoubleLinkedList<T>::emplace_back(Args&&... args) { 
    insert_before(tail_, std::forward<Args>(args)...); 
}

template <typename T>
void DoubleLinkedList<T>::pop_front() {
    if (empty()) 
        throw std::out_of_range("pop_front on empty list");

    erase(head_->next);
}

template <typename T>
void DoubleLinkedList<T>::pop_back() {
    if (empty()) 
        throw std::out_of_range("pop_back on empty list");

    erase(tail_->prev);
}

template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::begin() { 
    return iterator(head_->next); 
}

template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::end() { 
    return iterator(tail_); 
}

template <typename T>
typename DoubleLinkedList<T>::const_iterator DoubleLinkedList<T>::begin() const { 
    return const_iterator(head_->next); 
}

template <typename T>
typename DoubleLinkedList<T>::const_iterator DoubleLinkedList<T>::end() const { 
    return const_iterator(tail_); 
}

template <typename T>
typename DoubleLinkedList<T>::const_iterator DoubleLinkedList<T>::cbegin() const { 
    return const_iterator(head_->next); 
}

template <typename T>
typename DoubleLinkedList<T>::const_iterator DoubleLinkedList<T>::cend() const { 
    return const_iterator(tail_); 
}

template <typename T>
typename DoubleLinkedList<T>::reverse_iterator DoubleLinkedList<T>::rbegin() { 
    return reverse_iterator(tail_); 
}

template <typename T>
typename DoubleLinkedList<T>::reverse_iterator DoubleLinkedList<T>::rend() { 
    return reverse_iterator(head_); 
}

template <typename T>
typename DoubleLinkedList<T>::const_reverse_iterator DoubleLinkedList<T>::crbegin() const { 
    return const_reverse_iterator(tail_); 
}

template <typename T>
typename DoubleLinkedList<T>::const_reverse_iterator DoubleLinkedList<T>::crend() const { 
    return const_reverse_iterator(head_); 
}

template <typename T>
void DoubleLinkedList<T>::swap(DoubleLinkedList& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

template <typename T>
void DoubleLinkedList<T>::reverse() noexcept {
    Node* cur = head_;
    while (cur) {
        std::swap(cur->prev, cur->next);
        cur = cur->prev;
    }
    
    std::swap(head_, tail_);
}

template <typename T>
void DoubleLinkedList<T>::splice(DoubleLinkedList& rhs) noexcept {
    if (rhs.empty()) 
        return;

    splice(end(), rhs, rhs.begin(), rhs.end());
}

template <typename T>
void DoubleLinkedList<T>::splice(iterator pos, DoubleLinkedList& rhs, iterator first, iterator last) noexcept {
    if (first == last) 
        return;

    iterator it = first;
    while (first != last) {
        iterator next = std::next(first);
        move_node_after(pos.node_->prev, first.node_);
        ++pos;
        first = next;
    }
}

template <typename T>
void DoubleLinkedList<T>::merge(DoubleLinkedList& rhs) {
    if (this == &rhs || rhs.empty()) 
        return;

    Node* a = head_->next;
    Node* b = rhs.head_->next;
    Node* result = head_;
    while (a != tail_ && b != rhs.tail_) {
        if (b->value < a->value) {
            Node* next_b = b->next;
            move_node_after(result, b);
            result = b;
            b = next_b;
        } 
        else {
            result = a;
            a = a->next;
        }
    }

    if (b != rhs.tail_) {
        result->next = b;
        b->prev = result;
        tail_->prev = rhs.tail_->prev;
        rhs.tail_->prev->next = tail_;
    }
    
    size_ += rhs.size_;
    rhs.head_->next = rhs.tail_;
    rhs.tail_->prev = rhs.head_;
    rhs.size_ = 0;
}

template <typename T>
void DoubleLinkedList<T>::remove(const T& value) {
    remove_if([&](const T& v) { return v == value; });
}

template <typename T>
template <typename Predicate>
void DoubleLinkedList<T>::remove_if(Predicate pred) {
    Node* cur = head_->next;
    while (cur != tail_) {
        if (pred(cur->value)) {
            Node* next = cur->next;
            erase(cur);
            cur = next;
        } 
        else {
            cur = cur->next;
        }
    }
}

template <typename T>
void DoubleLinkedList<T>::unique() {
    unique(std::equal_to<>{});
}

template <typename T>
template <typename BinaryPredicate>
void DoubleLinkedList<T>::unique(BinaryPredicate pred) {
    if (size_ < 2) return;
    Node* cur = head_->next->next;
    while (cur != tail_) {
        if (pred(cur->prev->value, cur->value)) {
            Node* next = cur->next;
            erase(cur);
            cur = next;
        } 
        else {
            cur = cur->next;
        }
    }
}

template <typename T>
template <typename... Args>
void DoubleLinkedList<T>::insert_after(Node* pos, Args&&... args) {
    Node* n = new Node(std::forward<Args>(args)...);
    n->next = pos->next;
    n->prev = pos;
    pos->next->prev = n;
    pos->next = n;
    ++size_;
}

template <typename T>
template <typename... Args>
void DoubleLinkedList<T>::insert_before(Node* pos, Args&&... args) {
    insert_after(pos->prev, std::forward<Args>(args)...);
}

template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::erase(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    iterator next(node->next);
    delete node;
    --size_;
    
    return next;
}

template <typename T>
void DoubleLinkedList<T>::move_node_after(Node* pos, Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = pos->next;
    node->prev = pos;
    pos->next->prev = node;
    pos->next = node;
}

template class DoubleLinkedList<int>;
template class DoubleLinkedList<double>;
template class DoubleLinkedList<std::string>;

#endif // DOUBLE_LINKED_LIST_TPP
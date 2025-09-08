#include "DoubleLinkedList.h"

/*
================== Iterator Implementation ==================
*/

template <typename T>
DoubleLinkedList<T>::iterator::iterator(Node<T>* node) : node_(node) {}

template <typename T>
typename DoubleLinkedList<T>::iterator::reference DoubleLinkedList<T>::iterator::operator*() const {
    return node_->value;
}

template <typename T>
typename DoubleLinkedList<T>::iterator::pointer DoubleLinkedList<T>::iterator::operator->() {
    return &(node_->value);
}

template <typename T>
typename DoubleLinkedList<T>::iterator& DoubleLinkedList<T>::iterator::operator++() {
    if (node_){
        node_ = node_->next;
    }

    return *this;
}

// postfix increment
template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    
    return temp;
}

template <typename T>
typename DoubleLinkedList<T>::iterator& DoubleLinkedList<T>::iterator::operator--() {
    if(node_){
        node_ = node_->prev;
    }

    return *this;
}

template <typename T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::iterator::operator--(int) {
    iterator temp = *this;
    --(*this);
    
    return temp;
}

template <typename T>
bool DoubleLinkedList<T>::iterator::operator==(const iterator& rhs) const {
    return node_ == rhs.node_;
}

template <typename T>
bool DoubleLinkedList<T>::iterator::operator!=(const iterator& rhs) const {
    return node_ != rhs.node_;
}

/*
================== DoubleLinkedList Implementation ==================
*/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

template <typename T>
void DoubleLinkedList<T>::clear() {
    Node<T>* curr_node = nullptr;
    while (head_ != nullptr) {
        curr_node = head_;
        head_ = head_->next;
        delete curr_node;
    }

    tail_ = nullptr;
    size_ = 0;
}

template <typename T>
std::size_t DoubleLinkedList<T>::size() const {
    return size_;
}

template <typename T>
bool DoubleLinkedList<T>::empty() const {
    return size_ == 0;
}

template <typename T>
void DoubleLinkedList<T>::reverse() {
    Node<T>* curr = head_;
    Node<T>* temp = nullptr;

    while (curr != nullptr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp != nullptr) {
        head_ = temp->prev;
    }
}

template <typename T>
void DoubleLinkedList<T>::splice(DoubleLinkedList& rhs) {
    if (rhs.empty()) return;

    if (this->empty()) {
        *this = std::move(rhs);
        return;
    }

    tail_->next = rhs.head_;
    rhs.head_->prev = tail_;
    tail_ = rhs.tail_;
    size_ += rhs.size_;

    rhs.head_ = rhs.tail_ = nullptr;
    rhs.size_ = 0;
}

template <typename T>
void DoubleLinkedList<T>::merge(DoubleLinkedList& rhs) {
    if (rhs.empty()) return;

    if (this->empty()) {
        *this = std::move(rhs);
        return;
    }

    Node<T>* dummy = new Node<T>(T{});
    Node<T>* tail = dummy;
    Node<T>* left = head_;
    Node<T>* right = rhs.head_;

    while (left && right) {
        if (left->value < right->value) {
            tail->next = left;
            left->prev = tail;
            left = left->next;
        }
        else {
            tail->next = right;
            right->prev = tail;
            right = right->next;
        }
        
        tail = tail->next;
    }

    if (left) tail->next = left;
    if (right) tail->next = right;

    head_ = dummy->next;
    head_->prev = nullptr;
    delete dummy;

    rhs.head_ = rhs.tail_ = nullptr;
    rhs.size_ = 0;
}

template <typename T>
void DoubleLinkedList<T>::push_front(const T& val) {
    Node<T>* node = new Node<T>(val);
    if (empty()) {
        head_ = tail_ = node;
    } 
    else {
        node->next = head_;
        head_->prev = node;
        head_ = node;
    }
    
    ++size_;
}

template <typename T>
void DoubleLinkedList<T>::push_back(const T& val) {
    Node<T>* node = new Node<T>(val);
    if (empty()) {
        head_ = tail_ = node;
    } 
    else {
        node->prev = tail_;
        tail_->next = node;
        tail_ = node;
    }
    
    ++size_;
}

template <typename T>
void DoubleLinkedList<T>::pop_back() {
    if (empty()) return;

    Node<T>* to_delete = tail_;
    tail_ = tail_->prev;

    if (tail_) tail_->next = nullptr;
    else head_ = nullptr;

    delete to_delete;
    --size_;
}

template <typename T>
void DoubleLinkedList<T>::pop_front() {
    if (empty()) return;

    Node<T>* to_delete = head_;
    head_ = head_->next;

    if (head_) head_->prev = nullptr;
    else tail_ = nullptr;

    delete to_delete;
    --size_;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::resize(std::size_t new_size) {
    if (new_size > size_) {
        throw std::invalid_argument("resize() can only shrink the list.");
    }

    if (new_size == 0) {
        clear();
        return *this;
    }

    while (size_ > new_size) {
        pop_back();
    }

    return *this;
}

template <typename T>
template <typename... Args>
void DoubleLinkedList<T>::insert_front(Args&&... vals) {
    (push_front(std::forward<Args>(vals)), ...);
    size_ += sizeof...(vals);
}

template <typename T>
template <typename... Args>
void DoubleLinkedList<T>::insert_back(Args&&... vals) {
    (push_back(std::forward<Args>(vals)), ...);
    size_ += sizeof...(vals);
}

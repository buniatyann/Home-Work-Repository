#ifndef DOUBLE_LIST_TPP
#define DOUBLE_LIST_TPP

#include "List.hpp"

template <typename T>
Node<T>::Node(const T& val, Node* next, Node* prev) 
    : val(val), next(next), prev(prev) {}

template <typename T>
Node<T>::Node(T&& val, Node* next, Node* prev) 
    : val(std::move(val)), next(next), prev(prev) {}

template <typename T>
List<T>::List(std::size_t size) : size_(0), front_(nullptr), back_(nullptr) {
    for (std::size_t i = 0; i < size; ++i) {
        push_back(T());
    }
}

template <typename T>
List<T>::List(const List& lst) : size_(0), front_(nullptr), back_(nullptr) {
    Node<T>* current = lst.front_;
    while (current) {
        push_back(current->val);
        current = current->next;
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& lst) {
    if (this != &lst) {
        clear();
        Node<T>* current = lst.front_;
        while (current) {
            push_back(current->val);
            current = current->next;
        }
    }
    
    return *this;
}

template <typename T>
List<T>::List(List&& rhs) noexcept : size_(rhs.size_), front_(rhs.front_), back_(rhs.back_) {
    rhs.size_ = 0;
    rhs.front_ = nullptr;
    rhs.back_ = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(List&& rhs) noexcept {
    if (this != &rhs) {
        clear();
        size_ = rhs.size_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        rhs.size_ = 0;
        rhs.front_ = nullptr;
        rhs.back_ = nullptr;
    }
    
    return *this;
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::insert(const T& value, std::size_t pos) {
    if (pos > size_) {
        throw std::out_of_range("insert: pos > size");
    }
    if (pos == 0) {
        push_front(value);
        return;
    }
    
    Node<T>* current = front_;
    for (std::size_t i = 0; i < pos - 1; ++i) {
        current = current->next;
    }
    
    Node<T>* new_node = new Node<T>(value, current->next, current);
    if (current->next) {
        current->next->prev = new_node;
    }
    
    current->next = new_node;
    if (new_node->next == nullptr) {
        back_ = new_node;
    }
    
    ++size_;
}

template <typename T>
void List<T>::insert(T&& value, std::size_t pos) {
    if (pos > size_) {
        throw std::out_of_range("insert: pos > size");
    }
    if (pos == 0) {
        push_front(std::move(value));
        return;
    }
    
    Node<T>* current = front_;
    for (std::size_t i = 0; i < pos - 1; ++i) {
        current = current->next;
    }
    
    Node<T>* new_node = new Node<T>(std::move(value), current->next, current);
    if (current->next) {
        current->next->prev = new_node;
    }
    
    current->next = new_node;
    if (new_node->next == nullptr) {
        back_ = new_node;
    }
    
    ++size_;
}

template <typename T>
void List<T>::push_back(const T& value) {
    Node<T>* new_node = new Node<T>(value, nullptr, back_);
    if (!front_) {
        front_ = back_ = new_node;
    } 
    else {
        back_->next = new_node;
        back_ = new_node;
    }
    
    ++size_;
}

template <typename T>
void List<T>::push_back(T&& value) {
    Node<T>* new_node = new Node<T>(std::move(value), nullptr, back_);
    if (!front_) {
        front_ = back_ = new_node;
    } 
    else {
        back_->next = new_node;
        back_ = new_node;
    }
    
    ++size_;
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node<T>* new_node = new Node<T>(value, front_, nullptr);
    if (front_) {
        front_->prev = new_node;
    }
    
    front_ = new_node;
    if (!back_) {
        back_ = new_node;
    }
    
    ++size_;
}

template <typename T>
void List<T>::push_front(T&& value) {
    Node<T>* new_node = new Node<T>(std::move(value), front_, nullptr);
    if (front_) {
        front_->prev = new_node;
    }
    
    front_ = new_node;
    if (!back_) {
        back_ = new_node;
    }
    
    ++size_;
}

template <typename T>
void List<T>::pop_back() {
    if (size_ == 0) {
        throw std::runtime_error("pop_back: empty list");
    }
    if (size_ == 1) {
        delete front_;
        front_ = back_ = nullptr;
        size_ = 0;
        return;
    }
    
    Node<T>* temp = back_;
    back_ = back_->prev;
    back_->next = nullptr;
    delete temp;
    --size_;
}

template <typename T>
void List<T>::pop_front() {
    if (size_ == 0) {
        throw std::runtime_error("pop_front: empty list");
    }
    
    Node<T>* temp = front_;
    front_ = front_->next;
    if (front_) {
        front_->prev = nullptr;
    } 
    else {
        back_ = nullptr;
    }
    
    delete temp;
    --size_;
}

template <typename T>
void List<T>::clear() {
    Node<T>* current = front_;
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
    
    front_ = back_ = nullptr;
    size_ = 0;
}

template <typename T>
const T& List<T>::front() const {
    if (!front_) {
        throw std::runtime_error("front: empty list");
    }
    
    return front_->val;
}

template <typename T>
const T& List<T>::back() const {
    if (!back_) {
        throw std::runtime_error("back: empty list");
    }
    
    return back_->val;
}

template <typename T>
T& List<T>::front() {
    if (!front_) {
        throw std::runtime_error("front: empty list");
    }
    
    return front_->val;
}

template <typename T>
T& List<T>::back() {
    if (!back_) {
        throw std::runtime_error("back: empty list");
    }
    
    return back_->val;
}

template <typename T>
std::size_t List<T>::find(const T& value) {
    Node<T>* current = front_;
    std::size_t index = 0;
    while (current) {
        if (current->val == value) {
            return index;
        }
    
        current = current->next;
        ++index;
    }
    
    return size_;
}

template <typename T>
const T& List<T>::at(std::size_t ind) {
    if (ind >= size_) {
        throw std::out_of_range("at: ind >= size");
    }

    Node<T>* current = front_;
    for (std::size_t i = 0; i < ind; ++i) {
        current = current->next;
    }

    return current->val;
}

#endif // DOUBLE_LIST_TPP
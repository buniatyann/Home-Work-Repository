#ifndef DOUBLE_LIST_TPP
#define DOUBLE_LIST_TPP

#include "List.hpp"

template <typename T>
List<T>::List(std::size_t size) : size_(0), front_(nullptr), back_(nullptr) {
    for (std::size_t i = 0; i < size; ++i) {
        push_back(T());
    }
}

template <typename T>
List<T>::List(const List& lst) : size_(0), front_(nullptr), back_(nullptr) {
    DLLNode<T>* current = lst.front_;
    while (current) {
        push_back(current->val());
        current = static_cast<DLLNode<T>*>(current->next); // next is DLLNode<T>*
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& lst) {
    if (this != &lst) {
        clear();
        DLLNode<T>* current = lst.front_;
        while (current) {
            push_back(current->val());
            current = dynamic_cast<DLLNode<T>*>(current->next);
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

    DLLNode<T>* current = front_;
    for (std::size_t i = 0; i < pos - 1; ++i) {
        current = static_cast<DLLNode<T>*>(current->next); // next is DLLNode<T>*
    }

    DLLNode<T>* new_node = new DLLNode<T>(value, current->next, current);
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
void List<T>::insert(const T& value, std::size_t pos) {
    if (pos > size_) {
        throw std::out_of_range("insert: pos > size");
    }
    if (pos == 0) {
        push_front(value);
        return;
    }
 
    DLLNode<T>* current = front_;
    for (std::size_t i = 0; i < pos - 1; ++i) {
        current = static_cast<DLLNode<T>*>(current->next); // next is DLLNode<T>*
    }
 
    DLLNode<T>* new_node = new DLLNode<T>(value, current->next, current);
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
    DLLNode<T>* new_node = new DLLNode<T>(value, nullptr, back_);
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
    DLLNode<T>* new_node = new DLLNode<T>(std::move(value), nullptr, back_);
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
    DLLNode<T>* new_node = new DLLNode<T>(value, front_, nullptr);
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
    DLLNode<T>* new_node = new DLLNode<T>(std::move(value), front_, nullptr);
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

    DLLNode<T>* temp = back_;
    back_ = dynamic_cast<DLLNode<T>*>(back_->prev);
    back_->next = nullptr;
    delete temp;
    --size_;
}

template <typename T>
void List<T>::pop_front() {
    if (size_ == 0) {
        throw std::runtime_error("pop_front: empty list");
    }

    DLLNode<T>* temp = front_;
    front_ = dynamic_cast<DLLNode<T>*>(front_->next);
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
    DLLNode<T>* current = front_;
    while (current) {
        DLLNode<T>* temp = current;
        current = dynamic_cast<DLLNode<T>*>(current->next);
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
    
    return front_->val();
}

template <typename T>
const T& List<T>::back() const {
    if (!back_) {
        throw std::runtime_error("back: empty list");
    }
    
    return back_->val();
}

template <typename T>
T& List<T>::front() {
    if (!front_) {
        throw std::runtime_error("front: empty list");
    }
 
    return front_->val();
}

template <typename T>
T& List<T>::back() {
    if (!back_) {
        throw std::runtime_error("back: empty list");
    }
 
    return back_->val();
}

template <typename T>
std::size_t List<T>::find(const T& value) {
    DLLNode<T>* current = front_;
    std::size_t index = 0;
    while (current) {
        if (current->val() == value) {
            return index;
        }
 
        current = dynamic_cast<DLLNode<T>*>(current->next);
        ++index;
    }
 
    return size_;
}

template <typename T>
const T& List<T>::at(std::size_t ind) {
    if (ind >= size_) {
        throw std::out_of_range("at: ind >= size");
    }

    DLLNode<T>* current = front_;
    for (std::size_t i = 0; i < ind; ++i) {
        current = dynamic_cast<DLLNode<T>*>(current->next);
    }
 
    return current->val();
}

template <typename T>
const INode<T>* List<T>::frontNode() const {
    return front_;
}

template <typename T>
INode<T>* List<T>::frontNode() {
    return front_;
}

template <typename T>
const INode<T>* List<T>::backNode() const {
    return back_;
}

template <typename T>
INode<T>* List<T>::backNode() {
    return back_;
}

#endif // DOUBLE_LIST_TPP
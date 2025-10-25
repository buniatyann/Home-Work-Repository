#ifndef LIST_TPP
#define LIST_TPP

#include "List.hpp"

template <typename T>
List<T>::List() : front_(nullptr), back_(nullptr), size_(0) {}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
List<T>::List(const List& other) : front_(nullptr), back_(nullptr), size_(0) {
    if (other.size_ == 0) { 
        return;
    }

    SLLNode<T>* current = other.front_;
    while (current != other.front_ || size_ == 0) {
        push_back(current->val());
        current = current->next;
        if (current == other.front_) { 
            break; 
        }
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        if (other.size_ > 0) {
            SLLNode<T>* current = other.front_;
            while (current != other.front_ || size_ == 0) {
                push_back(current->val());
                current = current->next;
                if (current == other.front_) break; 
            }
        }
    }

    return *this;
}

template <typename T>
List<T>::List(List&& other) noexcept : front_(other.front_), back_(other.back_), size_(other.size_) {
    other.front_ = nullptr;
    other.back_ = nullptr;
    other.size_ = 0;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        clear();
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;
        other.front_ = nullptr;
        other.back_ = nullptr;
        other.size_ = 0;
    }

    return *this;
}

template <typename T>
void List<T>::insert(const T& value, std::size_t pos) {
    if (pos > size_) {
        throw std::out_of_range("Index out of bounds");
    }

    if (size_ == 0) {
        SLLNode<T>* new_node = new SLLNode<T>(value, nullptr);
        front_ = new_node;
        back_ = new_node;
        front_->next = front_;
    } 
    else if (pos == 0) {
        SLLNode<T>* new_node = new SLLNode<T>(value, front_);
        front_ = new_node;
        back_->next = front_;
    } 
    else {
        SLLNode<T>* current = front_;
        for (std::size_t i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
    
        SLLNode<T>* new_node = new SLLNode<T>(value, current->next);
        current->next = new_node;
        if (pos == size_) {
            back_ = new_node;
        }
    }
    
    ++size_;
}

template <typename T>
void List<T>::insert(T&& value, std::size_t pos) {
    if (pos > size_) {
        throw std::out_of_range("Index out of bounds");
    }

    if (size_ == 0) {
        SLLNode<T>* new_node = new SLLNode<T>(std::move(value), nullptr);
        front_ = new_node;
        back_ = new_node;
        front_->next = front_;
    } 
    else if (pos == 0) {
        SLLNode<T>* new_node = new SLLNode<T>(std::move(value), front_);
        front_ = new_node;
        back_->next = front_;
    } 
    else {
        SLLNode<T>* current = front_;
        for (std::size_t i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
    
        SLLNode<T>* new_node = new SLLNode<T>(std::move(value), current->next);
        current->next = new_node;
        if (pos == size_) {
            back_ = new_node;
        }
    }
    
    ++size_;
}

template <typename T>
void List<T>::push_back(const T& value) {
    insert(value, size_);
}

template <typename T>
void List<T>::push_back(T&& value) {
    insert(std::move(value), size_);
}

template <typename T>
void List<T>::push_front(const T& value) {
    insert(value, 0);
}

template <typename T>
void List<T>::push_front(T&& value) {
    insert(std::move(value), 0);
}

template <typename T>
void List<T>::pop_back() {
    assert(size_ > 0 && "Cannot pop_back from empty list");
    if (size_ == 1) {
        delete front_;
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
        return;
    }

    SLLNode<T>* current = front_;
    for (std::size_t i = 0; i < size_ - 2; ++i) {
        current = current->next;
    }
    
    delete current->next;
    current->next = front_;
    back_ = current;
    --size_;
}

template <typename T>
void List<T>::pop_front() {
    assert(size_ > 0 && "Cannot pop_front from empty list");
    if (size_ == 1) {
        delete front_;
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
        return;
    }

    SLLNode<T>* old_front = front_;
    front_ = front_->next;
    delete old_front;
    back_->next = front_;
    --size_;
}

template <typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
const T& List<T>::front() const {
    if (size_ == 0) {
        throw std::out_of_range("List is empty");
    }
    
    return front_->val();
}

template <typename T>
T& List<T>::front() {
    if (size_ == 0) {
        throw std::out_of_range("List is empty");
    }
    
    return front_->val();
}

template <typename T>
const T& List<T>::back() const {
    if (size_ == 0) {
        throw std::out_of_range("List is empty");
    }
    
    return back_->val();
}

template <typename T>
T& List<T>::back() {
    if (size_ == 0) {
        throw std::out_of_range("List is empty");
    }
    
    return back_->val();
}

template <typename T>
std::size_t List<T>::size() const noexcept {
    return size_;
}

template <typename T>
bool List<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
std::size_t List<T>::find(const T& value) const {
    SLLNode<T>* current = front_;
    for (std::size_t i = 0; i < size_; ++i) {
        if (current->val() == value) {
            return i;
        }
    
        current = current->next;
    }
    
    return static_cast<std::size_t>(-1);
}

template <typename T>
const T& List<T>::at(std::size_t ind) const {
    if (ind >= size_) {
        throw std::out_of_range("Index out of bounds");
    }

    SLLNode<T>* current = front_;
    for (std::size_t i = 0; i < ind; ++i) {
        current = current->next;
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

#endif // LIST_TPP

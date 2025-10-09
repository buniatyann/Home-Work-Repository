#include "Deque.hpp"
#include <stdexcept>
#include <algorithm>

template <typename T>
Deque<T>::Deque() : head(nullptr), tail(nullptr), current_size(0) {}

template <typename T>
Deque<T>::~Deque() {
    clear();
}

template <typename T>
Deque<T>::Deque(const Deque& other) : head(nullptr), tail(nullptr), current_size(0) {
    Node* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& other) {
    if (this != &other) {
        Deque temp(other);
        swap(*this, temp);
    }
    
    return *this;
}

template <typename T>
Deque<T>::Deque(Deque&& other) noexcept
    : head(other.head), tail(other.tail), current_size(other.current_size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.current_size = 0;
}

template <typename T>
Deque<T>& Deque<T>::operator=(Deque&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        current_size = other.current_size;
        other.head = nullptr;
        other.tail = nullptr;
        other.current_size = 0;
    }
    
    return *this;
}

template <typename T>
void swap(Deque<T>& a, Deque<T>& b) noexcept {
    std::swap(a.get_head(), b.get_head());
    std::swap(a.get_tail(), b.get_tail());
    std::swap(a.get_current_size(), b.get_current_size());
}

template <typename T>
void Deque<T>::push_front(const T& element) {
    Node* new_node = new Node(element);
    if (empty()) {
        head = tail = new_node;
    } 
    else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    
    ++current_size;
}

template <typename T>
void Deque<T>::push_front(T&& element) {
    Node* new_node = new Node(std::move(element));
    if (empty()) {
        head = tail = new_node;
    } 
    else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    
    ++current_size;
}

template <typename T>
void Deque<T>::pop_front() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    Node* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } 
    else {
        tail = nullptr;
    }
    
    delete temp;
    --current_size;
}

template <typename T>
T& Deque<T>::front() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return head->data;
}

template <typename T>
const T& Deque<T>::front() const {
    if (empty()) 
        throw std::out_of_range("Deque is empty");
        
    return head->data;
}

template <typename T>
void Deque<T>::push_back(const T& element) {
    Node* new_node = new Node(element);
    if (empty()) {
        head = tail = new_node;
    } 
    else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    
    ++current_size;
}

template <typename T>
void Deque<T>::push_back(T&& element) {
    Node* new_node = new Node(std::move(element));
    if (empty()) {
        head = tail = new_node;
    } 
    else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
 
    ++current_size;
}

template <typename T>
void Deque<T>::pop_back() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    Node* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } 
    else {
        head = nullptr;
    }
    
    delete temp;
    --current_size;
}

template <typename T>
T& Deque<T>::back() {
    if (empty()) 
        throw std::out_of_range("Deque is empty");

    return tail->data;
}

template <typename T>
const T& Deque<T>::back() const {
    if (empty()) 
        throw std::out_of_range("Deque is empty");
        
    return tail->data;
}

template <typename T>
bool Deque<T>::empty() const {
    return current_size == 0;
}

template <typename T>
std::size_t Deque<T>::size() const {
    return current_size;
}

template <typename T>
void Deque<T>::clear() {
    while (!empty()) pop_front();
}

template <typename T>
typename Deque<T>::Node*& Deque<T>::get_head() {
    return head;
}

template <typename T>
typename Deque<T>::Node*& Deque<T>::get_tail() {
    return tail;
}

template <typename T>
std::size_t& Deque<T>::get_current_size() {
    return current_size;
}
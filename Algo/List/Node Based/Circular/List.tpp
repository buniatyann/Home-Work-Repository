#ifndef LIST_TPP
#define LIST_TPP

#include "List.hpp"

template <typename T>
List<T>::Node::Node(const T& value, Node* next, Node* prev) 
    : data(value), next(next), prev(prev) {}

template <typename T>
List<T>::Node::Node(T&& value, Node* next, Node* prev) 
    : data(std::move(value)), next(next), prev(prev) {}

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), list_size(0) {}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), list_size(0) {
    if (other.list_size == 0) 
        return;

    Node* current = other.head;
    while (current != other.head || list_size == 0) {
        push_back(current->data);
        current = current->next;
        if (current == other.head) 
            break; 
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        if (other.list_size > 0) {
            Node* current = other.head;
            while (current != other.head || list_size == 0) {
                push_back(current->data);
                current = current->next;
                if (current == other.head) break; 
            }
        }
    }

    return *this;
}

template <typename T>
List<T>::List(List&& other) noexcept : head(other.head), tail(other.tail), list_size(other.list_size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.list_size = 0;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        list_size = other.list_size;
        other.head = nullptr;
        other.tail = nullptr;
        other.list_size = 0;
    }
    
    return *this;
}

template <typename T>
typename List<T>::Node* List<T>::get_node(std::size_t pos) const {
    if (pos >= list_size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    Node* current = head;
    for (std::size_t i = 0; i < pos; ++i) {
        current = current->next;
    }
    
    return current;
}

template <typename T>
void List<T>::insert(const T& value, std::size_t pos) {
    if (pos > list_size) {
        throw std::out_of_range("Index out of bounds");
    }

    if (list_size == 0) {
        Node* new_node = new Node(value, nullptr, nullptr);
        head = new_node;
        tail = new_node;
        head->next = head;
        head->prev = head;
    } 
    else if (pos == 0) {
        Node* new_node = new Node(value, head, tail);
        head->prev = new_node;
        tail->next = new_node;
        head = new_node;
    } 
    else {
        Node* current = get_node(pos);
        Node* new_node = new Node(value, current, current->prev);
        current->prev->next = new_node;
        current->prev = new_node;
        if (pos == list_size) {
            tail = new_node;
        }
    }
    
    ++list_size;
}

template <typename T>
void List<T>::insert(T&& value, std::size_t pos) {
    if (pos > list_size) {
        throw std::out_of_range("Index out of bounds");
    }

    if (list_size == 0) {
        Node* new_node = new Node(std::move(value), nullptr, nullptr);
        head = new_node;
        tail = new_node;
        head->next = head;
        head->prev = head;
    } 
    else if (pos == 0) {
        Node* new_node = new Node(std::move(value), head, tail);
        head->prev = new_node;
        tail->next = new_node;
        head = new_node;
    } 
    else {
        Node* current = get_node(pos);
        Node* new_node = new Node(std::move(value), current, current->prev);
        current->prev->next = new_node;
        current->prev = new_node;
        if (pos == list_size) {
            tail = new_node;
        }
    }
    
    ++list_size;
}

template <typename T>
void List<T>::push_back(const T& value) {
    assert(list_size < std::numeric_limits<std::size_t>::max() && "List size exceeds maximum");
    insert(value, list_size);
}

template <typename T>
void List<T>::push_back(T&& value) {
    assert(list_size < std::numeric_limits<std::size_t>::max() && "List size exceeds maximum");
    insert(std::move(value), list_size);
}

template <typename T>
void List<T>::push_front(const T& value) {
    assert(list_size < std::numeric_limits<std::size_t>::max() && "List size exceeds maximum");
    insert(value, 0);
}

template <typename T>
void List<T>::push_front(T&& value) {
    assert(list_size < std::numeric_limits<std::size_t>::max() && "List size exceeds maximum");
    insert(std::move(value), 0);
}

template <typename T>
void List<T>::pop_back() {
    assert(list_size > 0 && "Cannot pop_back from empty list");
    assert(head != nullptr && tail != nullptr && "Invalid list state");
    if (list_size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        list_size = 0;
    
        return;
    }

    Node* old_tail = tail;
    tail = tail->prev;
    tail->next = head;
    head->prev = tail;
    delete old_tail;
    --list_size;
}

template <typename T>
void List<T>::pop_front() {
    assert(list_size > 0 && "Cannot pop_front from empty list");
    assert(head != nullptr && tail != nullptr && "Invalid list state");
    if (list_size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        list_size = 0;
        return;
    }

    Node* old_head = head;
    head = head->next;
    head->prev = tail;
    tail->next = head;
    delete old_head;
    --list_size;
}

template <typename T>
void List<T>::clear() {
    if (list_size == 0) 
        return;

    Node* current = head;
    Node* next = current->next;
    while (current != head || list_size > 0) {
        delete current;
        current = next;
        next = current->next;
        --list_size;
        if (current == head) 
            break; 
    }

    head = nullptr;
    tail = nullptr;
}

template <typename T>
const T& List<T>::front() const {
    if (list_size == 0) {
        throw std::out_of_range("List is empty");
    }

    return head->data;
}

template <typename T>
T& List<T>::front() {
    if (list_size == 0) {
        throw std::out_of_range("List is empty");
    }

    return head->data;
}

template <typename T>
const T& List<T>::back() const {
    if (list_size == 0) {
        throw std::out_of_range("List is empty");
    }

    return tail->data;
}

template <typename T>
T& List<T>::back() {
    if (list_size == 0) {
        throw std::out_of_range("List is empty");
    }

    return tail->data;
}

template <typename T>
std::size_t List<T>::size() const noexcept {
    return list_size;
}

template <typename T>
bool List<T>::empty() const noexcept {
    return list_size == 0;
}

template <typename T>
std::size_t List<T>::find(const T& value) {
    if (list_size == 0) {
        return static_cast<std::size_t>(-1);
    }

    Node* current = head;
    std::size_t index = 0;
    while (current != head || index == 0) {
        if (current->data == value) {
            return index;
        }

        current = current->next;
        ++index;
        if (current == head) 
            break;
    }

    return static_cast<std::size_t>(-1);
}

template <typename T>
const T& List<T>::at(std::size_t ind) {
    if (ind >= list_size) {
        throw std::out_of_range("Index out of bounds");
    }

    return get_node(ind)->data;
}


#endif // LIST_TPP
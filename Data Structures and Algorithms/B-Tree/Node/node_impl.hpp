#ifndef NODE_IMPL_HPP
#define NODE_IMPL_HPP

#include "node.hpp"
#include <iostream>
#include <cstring>

template<typename T>
Node<T>::Node(int _t, bool _is_leaf) : t(_t), is_leaf(_is_leaf), disk_position(-1) {}

template<typename T>
Node<T>::~Node() {
    for (auto child : children)
    {
        delete child;
    }
}

template<typename T>
int Node<T>::find_key(const T& k) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < k) {
        ++idx;
    }
    
    return idx;
}

template<typename T>
void Node<T>::disk_read(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }

    if (disk_position == -1) {
        return; // New node, not on disk
    }

    file.seekg(disk_position);
    if (!file) {
        throw std::runtime_error("Invalid disk position");
    }

    // Read node metadata
    bool read_is_leaf;
    int read_key_count, read_child_count;
    file.read(reinterpret_cast<char*>(&read_is_leaf), sizeof(bool));
    file.read(reinterpret_cast<char*>(&read_key_count), sizeof(int));
    file.read(reinterpret_cast<char*>(&read_child_count), sizeof(int));

    if (!file) {
        throw std::runtime_error("Failed to read node metadata");
    }

    is_leaf = read_is_leaf;
    keys.resize(read_key_count);
    children.resize(read_child_count);

    // Read keys
    for (int i = 0; i < read_key_count; ++i) {
        file.read(reinterpret_cast<char*>(&keys[i]), sizeof(T));
        if (!file) {
            throw std::runtime_error("Failed to read key data");
        }
    }

    // Read children positions
    std::vector<std::streampos> child_positions(read_child_count);
    for (int i = 0; i < read_child_count; ++i) {
        file.read(reinterpret_cast<char*>(&child_positions[i]), sizeof(std::streampos));
        if (!file) {
            throw std::runtime_error("Failed to read child position");
        }
    }

    file.close();

    // Recursively read children
    for (int i = 0; i < read_child_count; ++i) {
        children[i] = new Node(t, false); // Will be updated by disk_read
        children[i]->disk_position = child_positions[i];
        children[i]->disk_read(filename);
    }
}

template<typename T>
void Node<T>::disk_write(const std::string& filename) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        file.open(filename, std::ios::binary | std::ios::out);
        if (!file) {
            throw std::runtime_error("Cannot open file for writing: " + filename);
        }
    }

    if (disk_position == -1) {
        file.seekp(0, std::ios::end);
        disk_position = file.tellp();
    } 
    else {
        file.seekp(disk_position);
    }

    // Write node metadata
    int key_count = keys.size();
    int child_count = children.size();
    file.write(reinterpret_cast<const char*>(&is_leaf), sizeof(bool));
    file.write(reinterpret_cast<const char*>(&key_count), sizeof(int));
    file.write(reinterpret_cast<const char*>(&child_count), sizeof(int));

    // Write keys
    for (const auto& key : keys) {
        file.write(reinterpret_cast<const char*>(&key), sizeof(T));
    }

    // Write children positions
    for (auto child : children) {
        std::streampos pos = child->disk_position;
        file.write(reinterpret_cast<const char*>(&pos), sizeof(std::streampos));
    }

    if (!file) {
        throw std::runtime_error("Failed to write node data");
    }

    file.close();

    // Recursively write children
    for (auto child : children) {
        child->disk_write(filename);
    }
}

template<typename T>
void Node<T>::remove(const T& k) {
    int idx = find_key(k);

    if (idx < keys.size() && keys[idx] == k) {
        is_leaf ? remove_from_leaf(idx) : remove_from_non_leaf(idx);
    } 
    else {
        if (is_leaf) return; // Key not found

        bool flag = (idx == keys.size());
        if (children[idx]->keys.size() < t) {
            fill(idx);
        }
        
        if (flag && idx > keys.size()) {
            children[idx - 1]->remove(k); 
        }
        else {
            children[idx]->remove(k);
        }
    }
}

template<typename T>
void Node<T>::remove_from_leaf(int idx) {
    keys.erase(keys.begin() + idx);
}

template<typename T>
void Node<T>::remove_from_non_leaf(int idx) {
    T k = keys[idx];
    if (children[idx]->keys.size() >= t) {
        T pred = get_predecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } 
    else if (children[idx + 1]->keys.size() >= t) {
        T succ = get_successor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } 
    else {
        merge(idx);
        children[idx]->remove(k);
    }
}

template<typename T>
T Node<T>::get_predecessor(int idx) {
    Node* cur = children[idx];
    while (!cur->is_leaf) {
        cur = cur->children.back();
    }

    return cur->keys.back();
}

template<typename T>
T Node<T>::get_successor(int idx) {
    Node* cur = children[idx + 1];
    while (!cur->is_leaf) {
        cur = cur->children.front();
    }
    
    return cur->keys.front();
}

template<typename T>
void Node<T>::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t) {
        borrow_from_prev(idx);
    }
    else if (idx != keys.size() && children[idx + 1]->keys.size() >= t) {
        borrow_from_next(idx);
    }
    else {
        merge(idx != keys.size() ? idx : idx - 1);
    }
}

template<typename T>
void Node<T>::borrow_from_prev(int idx) {
    Node* child = children[idx];
    Node* sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    if (!child->is_leaf) {
        child->children.insert(child->children.begin(), sibling->children.back());
    }
    
    keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    if (!sibling->is_leaf) {
        sibling->children.pop_back();
    }
}

template<typename T>
void Node<T>::borrow_from_next(int idx) {
    Node* child = children[idx];
    Node* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    if (!child->is_leaf) {
        child->children.push_back(sibling->children.front());
    }
    
    keys[idx] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());
    if (!sibling->is_leaf) {
        sibling->children.erase(sibling->children.begin());
    }
}

template<typename T>
void Node<T>::merge(int idx) {
    Node* child = children[idx];
    Node* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

    if (!child->is_leaf) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }
    
    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);
    delete sibling;
}

template<typename T>
void Node<T>::insert_non_full(const T& k) {
    int i = keys.size() - 1;
    if (is_leaf) {
        keys.insert(std::upper_bound(keys.begin(), keys.end(), k), k);
    } 
    else {
        while (i >= 0 && keys[i] > k) --i;
        ++i;
        children[i]->disk_read(filename);
        if (children[i]->keys.size() == 2 * t - 1) {
            split_child(i, children[i]);
            if (k > keys[i]) ++i;
        }

        children[i]->insert_non_full(k);
    }
}

template<typename T>
void Node<T>::split_child(int i, Node* y) {
    Node* z = new Node(y->t, y->is_leaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);

    if (!y->is_leaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

template<typename T>
Node<T>* Node<T>::search(const T& k) {
    int i = 0;
    while (i < keys.size() && k > keys[i]) ++i;
    if (i < keys.size() && keys[i] == k) return this;
    
    return is_leaf ? nullptr : children[i]->search(k);
}

template<typename T>
void Node<T>::traverse() {
    int i;
    for (i = 0; i < keys.size(); ++i) {
        if (!is_leaf) {
            children[i]->disk_read(filename);
            children[i]->traverse();
        }
    
        std::cout << keys[i] << " ";
    }
    
    if (!is_leaf) {
        children[i]->disk_read(filename);
        children[i]->traverse();
    }
}

#endif // NODE_IMPL_HPP
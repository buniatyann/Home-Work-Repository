#ifndef BTREE_IMPL_HPP
#define BTREE_IMPL_HPP

#include "btree.hpp"
#include <iostream>

template<typename T>
BTree<T>::BTree(int _t, const std::string& _filename) : t(_t), root(nullptr), filename(_filename) {
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file) {
        throw std::runtime_error("Cannot initialize file: " + filename);
    }
    
    file.close();
}

template<typename T>
BTree<T>::~BTree() {
    delete root;
}

template<typename T>
void BTree<T>::insert(const T& k) {
    if (!root) {
        root = new Node<T>(t, true);
        root->keys.push_back(k);
        root->disk_write(filename);
    } 
    else {
        root->disk_read(filename);
        if (root->keys.size() == 2 * t - 1) {
            Node<T>* s = new Node<T>(t, false);
            s->children.push_back(root);
            s->split_child(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->children[i]->insert_non_full(k);
            root = s;
            root->disk_write(filename);
        } 
        else {
            root->insert_non_full(k);
            root->disk_write(filename);
        }
    }
}

template<typename T>
void BTree<T>::remove(const T& k) {
    if (!root) {
        return;
    }

    root->disk_read(filename);
    root->remove(k);
    root->disk_write(filename);

    if (root->keys.empty()) {
        Node<T>* tmp = root;
        root = root->is_leaf ? nullptr : root->children[0];
        delete tmp;
        if (root) {
            root->disk_write(filename);
        }
    }
}

template<typename T>
Node<T>* BTree<T>::search(const T& k) {
    if (root) {
        root->disk_read(filename);
        return root->search(k);
    }
    
    return nullptr;
}

template<typename T>
void BTree<T>::traverse() const {
    if (root) {
        root->disk_read(filename);
        root->traverse();
    }
    
    std::cout << std::endl;
}

#endif // BTREE_IMPL_HPP
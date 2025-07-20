#ifndef BTREE_HPP
#define BTREE_HPP

#include "../Node/node.hpp"
#include <string>

/**
 * @brief Class representing a B-tree data structure with disk I/O support.
 * 
 * A B-tree allows efficient insertion, deletion, and search operations.
 * This implementation uses a separate Node class for individual node operations.
 * 
 * @tparam T Type of keys stored in the B-tree.
 */
template <typename T>
class BTree {
public:
    /**
     * @brief Construct a new BTree object.
     * 
     * @param _t Minimum degree of the B-tree.
     * @param filename File name used for persistent node storage.
     */
    BTree(int _t, const std::string& filename);

    /**
     * @brief Destroy the BTree and deallocate memory.
     */
    ~BTree();

    /**
     * @brief Traverse and print all keys in the B-tree in sorted order.
     */
    void traverse() const;

    /**
     * @brief Search for a key in the B-tree.
     * 
     * @param key Key to search for.
     * @return Pointer to the Node containing the key, or nullptr if not found.
     */
    Node<T>* search(const T& key);

    /**
     * @brief Insert a key into the B-tree.
     * 
     * @param k Key to insert.
     */
    void insert(const T& k);

    /**
     * @brief Remove a key from the B-tree.
     * 
     * @param k Key to remove.
     */
    void remove(const T& k);

private:
    Node<T>* root;          ///< Pointer to the root node.
    int t;                  ///< Minimum degree (defines range for number of keys).
    std::string filename;   ///< File used for persistent node storage.
};

#include "btree_impl.hpp"

#endif // BTREE_HPP

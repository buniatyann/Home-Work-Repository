#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdexcept>

/**
 * @brief B-tree Node class for internal management and disk storage.
 * 
 * @tparam T Type of keys stored in the node.
 */
template <typename T>
class Node {
public:
    /**
     * @brief Construct a new Node.
     * 
     * @param t Minimum degree.
     * @param is_leaf True if node is a leaf.
     */
    Node(int t, bool is_leaf);

    /**
     * @brief Destroy the Node and its children.
     */
    ~Node();

    /**
     * @brief Traverse the subtree rooted at this node.
     */
    void traverse();

    /**
     * @brief Search for a key in the subtree rooted at this node.
     * 
     * @param k Key to search.
     * @return Pointer to node containing the key, or nullptr if not found.
     */
    Node* search(const T& k);

    /**
     * @brief Insert key into this node if it's not full.
     * 
     * @param k Key to insert.
     */
    void insert_non_full(const T& k);

    /**
     * @brief Split the child node y at index i.
     * 
     * @param i Index of child.
     * @param y Pointer to child node to be split.
     */
    void split_child(int i, Node* y);

    /**
     * @brief Find the index of the first key greater than or equal to k.
     * 
     * @param k Key to find.
     * @return Index in keys.
     */
    int find_key(const T& k);

    /**
     * @brief Remove a key from the subtree rooted at this node.
     * 
     * @param k Key to remove.
     */
    void remove(const T& k);

    /**
     * @brief Remove key from a leaf node.
     * 
     * @param idx Index of key in the node.
     */
    void remove_from_leaf(int idx);

    /**
     * @brief Remove key from an internal (non-leaf) node.
     * 
     * @param idx Index of key.
     */
    void remove_from_non_leaf(int idx);

    /**
     * @brief Get predecessor of key at index idx.
     * 
     * @param idx Index of key.
     * @return Predecessor key.
     */
    T get_predecessor(int idx);

    /**
     * @brief Get successor of key at index idx.
     * 
     * @param idx Index of key.
     * @return Successor key.
     */
    T get_successor(int idx);

    /**
     * @brief Fill child node at index idx if it has less than t-1 keys.
     * 
     * @param idx Index of child.
     */
    void fill(int idx);

    /**
     * @brief Borrow a key from the previous sibling of the child at idx.
     * 
     * @param idx Index of child.
     */
    void borrow_from_prev(int idx);

    /**
     * @brief Borrow a key from the next sibling of the child at idx.
     * 
     * @param idx Index of child.
     */
    void borrow_from_next(int idx);

    /**
     * @brief Merge the child at idx with its sibling.
     * 
     * @param idx Index of child.
     */
    void merge(int idx);

    /**
     * @brief Read node data from disk file.
     * 
     * @param filename File containing serialized B-tree nodes.
     */
    void disk_read(const std::string& filename);

    /**
     * @brief Write node data to disk file.
     * 
     * @param filename File to write serialized B-tree nodes.
     */
    void disk_write(const std::string& filename);

    bool is_leaf;                   ///< True if the node is a leaf
    int t;                          ///< Minimum degree (defines the range for number of keys)
    std::vector<T> keys;            ///< Keys in the node
    std::vector<Node*> children;    ///< Child pointers
    std::streampos disk_position;   ///< Disk position where this node is saved

private:
    std::string filename;           ///< File name for I/O operations
};

#include "node_impl.hpp"

#endif // NODE_HPP

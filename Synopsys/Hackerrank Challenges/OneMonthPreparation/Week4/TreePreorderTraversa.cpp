#include <iostream>

// Define the structure of a node in a binary tree
class Node {
public:
    int data;      // Store the data of the node
    Node *left;    // Pointer to the left child node
    Node *right;   // Pointer to the right child node
    
    // Constructor to initialize the node with data and set left and right children to NULL
    Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

// Function to perform pre-order traversal of the binary tree
void preOrder(Node *root) {
    // Base case: if the current node is nullptr, return (empty tree or end of branch)
    if (root == nullptr) {
        return;
    }
    
    // Print the data of the current node (visit the node)
    std::cout << root->data << " ";
    
    // Recursively traverse the left subtree
    preOrder(root->left);
    
    // Recursively traverse the right subtree
    preOrder(root->right);
}

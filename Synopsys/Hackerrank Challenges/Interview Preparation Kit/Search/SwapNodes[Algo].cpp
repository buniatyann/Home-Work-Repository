#include <bits/stdc++.h>

/*
    veranayel 
    Time O(m * n)
    Space O(n+m⋅n) (mainly due to the storage of nodes and the results)
*/
// Node class representing each node in the binary tree
class Node {
public:
    int data;        // Data stored in the node
    Node *left;     // Pointer to the left child
    Node *right;    // Pointer to the right child

    // Constructor to initialize a new node
    Node(int d) {
        data = d;
        left = NULL;  // Initialize left child to null
        right = NULL; // Initialize right child to null
    }
};

// Pre-order traversal: visits root, then left, then right
void printnode_preOrder(Node *root, std::vector<int> &result) {
    // Base case: if the node's data is negative, return
    if (root->data < 0)
        return;

    std::cout << root->data << " "; // Print current node's data
    result.push_back(root->data); // Add data to the result vector

    // Recursively visit left and right children
    if (root->left != NULL)
        printnode_preOrder(root->left, result);
    
    if (root->right != NULL)
        printnode_preOrder(root->right, result);
}

// In-order traversal: visits left, then root, then right
void printnode_inOrder(Node *root, std::vector<int> &result) {
    // Base case: if the node's data is negative, return
    if (root->data < 0)
        return;

    // Recursively visit left child
    if (root->left != NULL)
        printnode_inOrder(root->left, result);
    
    result.push_back(root->data); // Add data to the result vector

    // Recursively visit right child
    if (root->right != NULL)
        printnode_inOrder(root->right, result);
}

// Swap left and right children at every k-th depth
void swap_k_depth(Node *node, int depth, int k) {
    // Base case: if the node is null, return
    if (node == NULL) {
        return;
    }
    
    // Check if the current depth is a multiple of k
    if (depth % k == 0) {
        // Swap left and right children
        Node *temp = node->left;
        node->left = node->right;
        node->right = temp;
    }

    // Recursively process left and right children
    swap_k_depth(node->left, depth + 1, k);
    swap_k_depth(node->right, depth + 1, k);
}

// Function to create the binary tree and perform operations based on queries
std::vector<std::vector<int>> swapNodes(std::vector<std::vector<int>> indexes, std::vector<int> queries) {
    std::vector<std::vector<int>> result; // Result to store outputs for each query
    Node root(1);               // Create the root node with data 1
    Node *node = &root;         // Pointer to the current node
    std::queue<Node *> q;            // Queue to facilitate level-order insertion
    q.push(node);               // Start with the root in the queue
    std::cout << "indexes" << std::endl; // Debug output for indexes
    
    for (auto i : indexes) {
        node = q.front();       // Get the current node
        for (auto j : i) {
            std::cout << j << " ";   // Print the value being added
            Node *nn = new Node(j); // Create a new node with the given value
            if (node->left == NULL) {
                node->left = nn; // Assign left child if it's empty
            } else {
                node->right = nn; // Assign right child otherwise
            }
            
            // Only enqueue valid nodes (non-negative)
            if (j != -1)
                q.push(nn);
        }
        std::cout << std::endl;
        q.pop(); // Remove the current node from the queue
    }

    std::cout << std::endl;
    std::cout << "queries" << std::endl; // Debug output for queries

    for (auto k : queries) {
        std::cout << k << "  " << std::endl; // Print the current query
        swap_k_depth(&root, 1, k); // Swap nodes at the k-th depth
        std::vector<int> current_result; // Vector to hold current in-order result
        printnode_inOrder(&root, current_result); // Get the in-order traversal
        result.push_back(current_result); // Store result for this query
    }

    std::cout << std::endl;

    return result; // Return all results
}

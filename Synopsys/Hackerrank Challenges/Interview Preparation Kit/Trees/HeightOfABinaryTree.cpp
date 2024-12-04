#include <bits/stdc++.h>

class Node{
public:
    int data;
    Node* right;
    Node* left;
};


// Time O(n) Space O(h): h -> the height of the tree
int height(Node* root) {
    // Base case: if the node is null, return -1
    // This indicates that the height of an empty tree is -1,
    // which can be useful for calculating height in terms of edges.
    if (root == nullptr) {
        return -1;  
    }
    
    // Recursively find the height of the left subtree
    int left_height = height(root->left);
    
    // Recursively find the height of the right subtree
    int right_height = height(root->right);
    
    // The height of the current node is 1 plus the maximum height of its children
    // Adding 1 accounts for the edge connecting the current node to its children.
    return 1 + std::max(left_height, right_height);
}
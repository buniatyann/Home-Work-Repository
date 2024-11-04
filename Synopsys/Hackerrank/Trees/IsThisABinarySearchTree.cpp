#include <bits/stdc++.h>


struct Node{
    int data;
    Node* right;
    Node* left;
};

bool checkBST(Node* root, int min_val, int max_val) {
    // An empty tree is a BST
    if (root == nullptr) {
        return true;
    }

    // Check if the current node's data is within the valid range
    if (root->data <= min_val || root->data >= max_val) {
        return false;
    }

    // Recursively check the left and right subtrees with updated ranges
    return checkBST(root->left, min_val, root->data) && checkBST(root->right, root->data, max_val);
}

// Wrapper function to maintain the original signature
bool checkBST(Node* root) {
    int min_val = INT_MIN;
    int max_val = INT_MAX;
    return checkBST(root, min_val, max_val);
}
#include <iostream>

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

/*
    Time O(h)
    Space O(h)
    where h is the height of the tree
*/
Node* lca(Node* root, int v1, int v2) {
    if (root == nullptr) return nullptr;  // Handle edge case when root is null

    // If root's data is between v1 and v2 (inclusive), root is the LCA
    if (root->data >= std::min(v1, v2) && root->data <= std::max(v1, v2)) {
        return root;
    }
    // If root's data is smaller than both v1 and v2, search in the right subtree
    else if (root->data < v1 && root->data < v2) {
        return lca(root->right, v1, v2);
    }
    // If root's data is larger than both v1 and v2, search in the left subtree
    else if (root->data > v1 && root->data > v2) {
        return lca(root->left, v1, v2);
    }
    
    return root;  // If no other condition matches, root is the LCA
}

/*
    Time O(n) or O(log(n))
    Space O(1)
*/
Node* lca(Node* root, int v1, int v2) {
    while (root != nullptr) {
        if (root->data > v1 && root->data > v2) {
            // Both v1 and v2 are smaller than root, move to the left
            root = root->left;
        }
        else if (root->data < v1 && root->data < v2) {
            // Both v1 and v2 are larger than root, move to the right
            root = root->right;
        } 
        else {
            // One of v1 or v2 is on the left and the other is on the right, or one is equal to root
            return root;
        }
    }

    return nullptr;  // This line is technically unreachable if v1 and v2 exist in the tree
}

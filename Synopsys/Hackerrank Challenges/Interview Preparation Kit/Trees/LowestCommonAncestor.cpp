#include <bits/stdc++.h>

class Node{
public:
    int data;
    Node* right;
    Node* left;
};

/*
    !Recursive approach
    Time O(h) (O(log n) for balanced BST, O(n) for unbalanced BST)
    Space O(1)
*/
Node* lca(Node* root, int v1, int v2) {
    Node* dummy = root;

    while (dummy != nullptr) {
        // If both values are greater than the current node, go right
        if (dummy->data < v1 && dummy->data < v2) {
            dummy = dummy->right;
        }
        // If both values are less than the current node, go left
        else if (dummy->data > v1 && dummy->data > v2) {
            dummy = dummy->left;
        }
        // If one value is on one side and the other is on the opposite side, return the current node
        else {
            return dummy;
        }
    }

    return nullptr; // If the root is nullptr, return nullptr
}


/*
    Recursive approach
    Time O(h) (O(log n) for balanced BST, O(n) for unbalanced BST)
    Space O(1) Why?
*/
Node* lca_recursive(Node* root, int v1, int v2) {
    // Base case: If the tree is empty, return nullptr
    if (root == nullptr) {
        return nullptr;
    }

    // If both v1 and v2 are greater than the root's data,
    // then the LCA lies in the right subtree.
    if (root->data < v1 && root->data < v2) {
        return lca_recursive(root->right, v1, v2);
    }
    
    // If both v1 and v2 are less than the root's data,
    // then the LCA lies in the left subtree.
    if (root->data > v1 && root->data > v2) {
        return lca_recursive(root->left, v1, v2);
    }
    
    // If neither of the above cases is true,
    // then the current node is the LCA of v1 and v2.
    return root;
}

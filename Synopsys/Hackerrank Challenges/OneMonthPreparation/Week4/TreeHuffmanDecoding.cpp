#include <iostream>
#include <string>

// Node structure for Huffman tree
struct node {
    char data;
    node* left;
    node* right;
    
    node(char c) : data(c), left(nullptr), right(nullptr) {}
};

/*
    Time O(n)
    Space O(1)
*/
void decode_huff(node* root, std::string s) {
    std::string ans = "";
    node* curr = root;
    
    // Traverse the encoded string character by character
    for(char c : s){
        // Move down the tree based on '0' or '1'
        if(c == '0'){
            curr = curr->left;  // Move to left child if '0'
        }
        else if(c == '1'){
            curr = curr->right;  // Move to right child if '1'
        }
        
        // If we've reached a leaf node, append the data to the answer
        if(curr->left == nullptr && curr->right == nullptr){
            ans += curr->data;  // Add the character at the leaf node
            curr = root;  // Reset to the root for the next character
        }
    }
    
    // Output the decoded string
    std::cout << ans << std::endl;
}

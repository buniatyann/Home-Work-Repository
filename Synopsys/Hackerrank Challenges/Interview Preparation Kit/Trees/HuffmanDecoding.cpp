#include <iostream>
#include <string>

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;


/*
    Time O(n * h) where n is the length of the input string and h is the height of the Huffman tree
    Space O(m) where m is the length of the decoded result
*/
void decode_huff(node * root, std::string s) {
    // Initialize the current node to the root of the Huffman tree
    node* curr = root;
    // Initialize an empty string to hold the decoded result
    std::string result = "";
    
    // Iterate through each character in the encoded string
    for(char c : s) {
        // Navigate the Huffman tree based on the current bit
        if(c == '0') {
            // Move to the left child for '0'
            curr = curr->left;
        }
        else {
            // Move to the right child for '1'
            curr = curr->right;
        }
        
        // Check if the current node is a leaf (contains actual data)
        if(curr->left == nullptr && curr->right == nullptr) {
            // Append the decoded character to the result
            result += curr->data;
            // Reset current node to the root for the next character
            curr = root;
        }
    }
    
    // Output the fully decoded string
    for(char c : result) {
        std::cout << c;
    }
}


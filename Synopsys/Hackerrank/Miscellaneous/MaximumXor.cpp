#include <iostream>
#include <vector>

/*
    Time O(n + m) n is the number of elements in the array and m is the number of queries.
    Space O(n)
    veranayel
*/
class TrieNode {
public:
    TrieNode* left;  // Represents bit 0
    TrieNode* right; // Represents bit 1
    TrieNode() {
        left = nullptr;
        right = nullptr;
    }
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(int num) {
        TrieNode* node = root;
        // Process each bit of the number, starting from the most significant bit (31st)
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;  // Extract the bit at position i
            
            // If the bit is 0, move to the left child, otherwise to the right child
            if (bit == 0) {
                if (!node->left) node->left = new TrieNode();  // Create left child if doesn't exist
                node = node->left;  // Move to the left child
            } 
            else {
                if (!node->right) node->right = new TrieNode();  // Create right child if doesn't exist
                node = node->right;  // Move to the right child
            }
        }
    }
    
    int find_max_xor(int num) {
        TrieNode* node = root;
        int max_xor = 0;
        
        // Iterate over each bit of the number, starting from the most significant bit
        for (int i = 31; i >= 0; --i) {
            int bit = (num >> i) & 1;  // Extract the bit at position i
            
            // Try to go in the opposite direction to maximize the XOR result
            if (bit == 0) {
                if (node->right) {
                    max_xor |= (1 << i);  // Set the current bit in maxXor
                    node = node->right;  // Move to the right child (opposite bit 1)
                } 
                else {
                    node = node->left;  // Move to the left child (same bit 0)
                }
            } 
            else {
                if (node->left) {
                    max_xor |= (1 << i);  // Set the current bit in maxXor
                    node = node->left;  // Move to the left child (opposite bit 0)
                } 
                else {
                    node = node->right;  // Move to the right child (same bit 1)
                }
            }
        }
        
        return max_xor;  // Return the maximum XOR value found
    }
};

std::vector<int> maxXor(std::vector<int> arr, std::vector<int> queries) {
    Trie trie;
    
    // Insert all elements of the array into the Trie
    for (int num : arr) {
        trie.insert(num);
    }
    
    // Result vector to store the answers for each query
    std::vector<int> ans;
    
    // For each query, find the maximum XOR value by querying the Trie
    for (int q : queries) {
        ans.push_back(trie.find_max_xor(q));  // Append the result for the query
    }
    
    return ans;  // Return the results for all queries
}

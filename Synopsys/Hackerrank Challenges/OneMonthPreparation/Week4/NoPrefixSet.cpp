#include <vector>
#include <string>
#include <iostream>

class Trie {
private:
    // Size of alphabet, assuming 'a' to 'j' (10 letters) based on 'j' - 'a' + 1
    static const int LETTER_SIZE = 'j' - 'a' + 1;

    // Node class to represent each node of the Trie
    class Node {
    public:
        Node* children[LETTER_SIZE]; // Array of pointers to child nodes (one for each letter)
        char key;                    // The character that this node represents
        int word_count;               // Number of words that pass through this node or end at this node
        int prefix_count;             // Number of words that pass through this node

        // Constructor to initialize the node with a given character
        Node(char key) : key(key), word_count(0), prefix_count(0) {
            // Initialize all child pointers to null
            for (int i = 0; i < LETTER_SIZE; ++i) {
                children[i] = nullptr;
            }
        }

        // Check if a child node exists for a given character
        bool has(char key) {
            return get(key) != nullptr;
        }

        // Get the child node corresponding to the given character
        Node* get(char key) {
            return children[getKey(key)];
        }

        // Put a node in the array of children based on the character
        void put(char key, Node* node) {
            children[getKey(key)] = node;
        }

        // Convert a character to an index (e.g., 'a' -> 0, 'b' -> 1, ...)
        int getKey(char ch) {
            return ch - 'a';
        }
    };

    Node* root; // Root of the Trie

public:
    // Constructor to initialize the root node of the Trie
    Trie() {
        root = new Node('*'); // Special key '*' for the root node
    }

    // Public method to insert a word into the Trie
    bool insert(const std::string& word) {
        return insert(word, root); // Call private helper insert method
    }

    // Private method to insert a word starting from a given parent node
    bool insert(const std::string& word, Node* parent) {
        parent->prefix_count++; // Increment the count of prefixes passing through the node
        // If the word is already present, return false (cannot insert prefix of an existing word)
        if (word.length() > 0 && parent->word_count > 0) {
            return false;
        }
        // If we reach the end of the word, mark it as a complete word in the Trie
        if (word.empty()) {
            if (parent->prefix_count > 1) {
                return false; // If the current node has multiple prefixes, it's a bad set
            }
            parent->word_count++; // Increment the count of complete words at this node
            return true;
        }

        // Get the character to insert
        char ch = word[0];
        Node* next = parent->get(ch); // Look for the child node for this character
        // If there is no child node for the character, create a new one
        if (next == nullptr) {
            next = new Node(ch);
            parent->put(ch, next); // Put the new node into the children array
        }
        // Recursively insert the rest of the word
        return insert(word.substr(1), next);
    }


};

/*
    Time O(N * L), where N is the number of words and L is the average length of the words.
    Space O(T), where T is the total number of characters across all words in the input.
    veranayel
*/
void noPrefix(const std::vector<std::string>& words) {
    bool good = true;
    Trie trie;

    // Loop through each word and try to insert it into the Trie
    for (const auto& word : words) {
        good = trie.insert(word); // Insert word into Trie
        if (!good) {
            // If insertion fails (i.e., it’s a bad set), output "BAD SET" and the word
            std::cout << "BAD SET" << std::endl;
            std::cout << word << std::endl;
            return;
        }
    }

    // If all words are inserted successfully, output "GOOD SET"
    if (good) {
        std::cout << "GOOD SET" << std::endl;
    }
}

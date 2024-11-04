#include <bits/stdc++.h>

struct Node {
        int data;
        struct Node* next;
};

/*
    Floyd's cycle finding algorithm
    Time O(n), Space O(1)
*/  
bool has_cycle(Node* head) {
    if (head == nullptr) {
        return false;
    }
    
    Node* slow = head; // Initialize slow pointer
    Node* fast = head; // Initialize fast pointer
    
    while (fast != nullptr && fast->next != nullptr) { // Check for end of list
        slow = slow->next;              // Move slow pointer by one
        fast = fast->next->next;       // Move fast pointer by two
        
        if (slow == fast) { // Cycle detected
            return true;
        }
    }
    
    return false; // No cycle detected
}

// Time O(n), Space O(n), because of std::unordered_set
bool has_cycle(Node* head) {
    if (head == nullptr) {
        return false;
    }

    Node* dummy = head;  // Start from the head
    std::unordered_set<Node*> visited;  // Set to track visited nodes

    while (dummy != nullptr) {
        if (visited.find(dummy) != visited.end()) {
            return true;  // Cycle detected
        }

        visited.insert(dummy);  // Add current node to the set
        dummy = dummy->next;    // Move to the next node
    }

    return false;  // No cycle detected
}



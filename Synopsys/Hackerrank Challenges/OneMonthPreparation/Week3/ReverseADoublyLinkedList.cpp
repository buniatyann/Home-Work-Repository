#include <iostream>

struct DoublyLinkedListNode {
    int data;
    DoublyLinkedListNode* next;
    DoublyLinkedListNode* prev;
};

using Node = DoublyLinkedListNode;

/*
    Time O(n)
    Space O(1)
*/
DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist) {
    // Initialize pointers for traversal and reversal
    Node* curr = llist;     // 'curr' points to the current node in the list
    Node* prev = nullptr;   // 'prev' will eventually point to the new head of the list (initially null)
    Node* next = nullptr;   // 'next' stores the next node (used to avoid losing the reference during reversal)
    
    // Traverse the list and reverse the links
    while (curr != nullptr) {
        // Store the next node (before breaking the 'next' pointer)
        next = curr->next;
        
        // Reverse the 'next' and 'prev' pointers of the current node
        curr->next = prev;  // Current node's next now points to the previous node (reversing the direction)
        curr->prev = next;  // Current node's prev now points to the next node (preparing for the next node to be reversed)
        
        // Move prev and curr one step forward
        prev = curr;    // Move 'prev' to the current node (for the next iteration)
        curr = next;    // Move 'curr' to the next node in the original list (saved in 'next')
    }
    
    // Return the new head of the list (prev is now pointing to the last node, which is the new head)
    return prev;
}

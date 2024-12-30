#include <iostream>

struct SinglyLinkedListNode {
    int data;
    SinglyLinkedListNode* next;
};

/*
    Time O(n)
    Space O(1)
*/
SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {
    // Initialize pointers
    SinglyLinkedListNode* curr = llist; // 'curr' will point to the current node during the traversal
    SinglyLinkedListNode* prev = nullptr; // 'prev' will point to the previous node, starts as nullptr
    SinglyLinkedListNode* next; // 'next' will temporarily store the next node in the list

    // Traverse the list and reverse the links
    while(curr != nullptr) {
        // Store the next node (so we don't lose the reference)
        next = curr->next;

        // Reverse the 'next' pointer of the current node
        curr->next = prev;

        // Move 'prev' forward to 'curr', now 'prev' will be the current node in the next iteration
        prev = curr;

        // Move 'curr' forward to the next node (which is stored in 'next')
        curr = next;
    }

    // At the end of the loop, 'prev' will be pointing to the new head of the reversed list
    return prev;
}

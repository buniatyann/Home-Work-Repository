#include <bits/stdc++.h>

class DoublyLinkedListNode {
    public:
        int data;
        DoublyLinkedListNode *next;
        DoublyLinkedListNode *prev;

        DoublyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

class DoublyLinkedList {
    public:
        DoublyLinkedListNode *head;
        DoublyLinkedListNode *tail;

        DoublyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            DoublyLinkedListNode* node = new DoublyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
                node->prev = this->tail;
            }

            this->tail = node;
        }
};

DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist) {
    // Initialize pointers for the previous and current nodes
    DoublyLinkedListNode* prev = nullptr; // This will eventually become the new head of the reversed list
    DoublyLinkedListNode* curr = llist; // Start with the head of the list
    
    // Iterate through the list until we reach the end (curr becomes nullptr)
    while (curr != nullptr) {
        // Reverse the pointers
        curr->prev = curr->next; // Set the previous pointer to the next node
        curr->next = prev;       // Set the next pointer to the previous node
        
        // Move prev and curr one step forward
        prev = curr;            // Move prev to the current node (this will be the new previous node)
        curr = curr->prev;      // Move curr to the next node in the original list (now stored in curr->prev)
    }
    
    // At the end of the loop, prev points to the new head of the reversed list
    return prev; // Return the new head of the reversed list
}

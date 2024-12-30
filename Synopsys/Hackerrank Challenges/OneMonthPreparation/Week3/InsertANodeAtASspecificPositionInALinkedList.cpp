#include <iostream>

struct SinglyLinkedListNode{
    int data;
    SinglyLinkedListNode* next;
    SinglyLinkedListNode(int data) : data(data), next(nullptr) {}
};

using Node = SinglyLinkedListNode;

/*
    Time O(k) where k is the position at which we want to insert the new node
    Space O(1)
*/
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    // Special case: inserting at the head of the list
    if (position == 0) {
        Node* new_node = new Node(data);
        new_node->next = llist;
        return new_node;  // The new node is now the head of the list
    }
    
    Node* curr = llist;
    
    // Traverse to the node just before the desired position
    for(int i = 0; i < position - 1; ++i){
        curr = curr->next;
    }
    
    // Insert the new node
    auto next = curr->next;
    curr->next = new Node(data);
    curr->next->next = next;
    
    return llist;
}

#include <iostream>

struct SinglyLinkedListNode{
    int data;
    SinglyLinkedListNode* next;
    SinglyLinkedListNode(int data): data(data), next(nullptr) {}
};

using Node = SinglyLinkedListNode;

/*
    Time O(n + m)
    Space O(n + m)
    where n and m are the lengths of the two input lists head1 and head2.
*/
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    // Create a dummy node to act as the start of the merged list
    Node* dummy = new Node(0);  // Dummy node with value 0
    Node* curr = dummy;  // `curr` will point to the last node in the merged list
    
    // Merge the two lists
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->data <= head2->data) {
            curr->next = new Node(head1->data);  // Add the node from list 1
            head1 = head1->next;
        } 
        else {
            curr->next = new Node(head2->data);  // Add the node from list 2
            head2 = head2->next;
        }

        curr = curr->next;  // Move `curr` to the last node in the merged list
    }
    
    // Add remaining nodes from list 1 (if any)
    while (head1 != nullptr) {
        curr->next = new Node(head1->data);
        head1 = head1->next;
        curr = curr->next;  // Move `curr` to the last node
    }
    
    // Add remaining nodes from list 2 (if any)
    while (head2 != nullptr) {
        curr->next = new Node(head2->data);
        head2 = head2->next;
        curr = curr->next;  // Move `curr` to the last node
    }
    
    // Return the merged list starting from the first node (after the dummy node)
    return dummy->next;
}


using Node = SinglyLinkedListNode;
/*
    Time O(n + m) where n and m are the lengths of the two input lists head1 and head2.
    Space O(1)
*/
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    // Dummy node to start the merged list
    Node* dummy = new Node(0);  
    Node* tail = dummy;  // Tail points to the last node of the merged list
    
    // Traverse both lists and merge them
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->data <= head2->data) {
            tail->next = head1;  // Link the current node from list 1
            head1 = head1->next;  // Move head1 to the next node
        } 
        else {
            tail->next = head2;  // Link the current node from list 2
            head2 = head2->next;  // Move head2 to the next node
        }

        tail = tail->next;  // Move the tail pointer to the last node of the merged list
    }

    // If there are remaining nodes in head1, append them
    if (head1 != nullptr) {
        tail->next = head1;
    }

    // If there are remaining nodes in head2, append them
    if (head2 != nullptr) {
        tail->next = head2;
    }
    
    // Return the merged list starting from the first node
    return dummy->next;
}


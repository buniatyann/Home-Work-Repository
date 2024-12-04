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

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
    if (!llist) {
    throw std::invalid_argument("Bad input");
    }

    DoublyLinkedListNode* dummy = llist;
    DoublyLinkedListNode* dt = new DoublyLinkedListNode(data);

    // Handle insertion at the beginning or in the middle of the list
    if (dummy->data >= data) {
        dt->next = dummy;
        dt->prev = nullptr;
        dummy->prev = dt;
        return dt; // New head of the list
    }

    while (dummy->next != nullptr && dummy->next->data < data) {
        dummy = dummy->next;
    }

    dt->prev = dummy;
    dt->next = dummy->next;

    if (dummy->next != nullptr) {
        dummy->next->prev = dt; // Update the next node's previous pointer
    }

    dummy->next = dt;

    return llist; // Return the head of the list
}
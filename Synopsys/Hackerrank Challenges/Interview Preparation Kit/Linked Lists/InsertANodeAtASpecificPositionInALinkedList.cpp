#include <bits/stdc++.h>

class SinglyLinkedListNode {
    public:
        int data;
        SinglyLinkedListNode *next;

        SinglyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
        }
};

class SinglyLinkedList {
    public:
        SinglyLinkedListNode *head;
        SinglyLinkedListNode *tail;

        SinglyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
            }

            this->tail = node;
        }
};


SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    if(!llist){
        throw std::invalid_argument("Invalid input");    
    }
    
    SinglyLinkedListNode* dt = new SinglyLinkedListNode(data);
    
    if(position == 0){
        dt->next = llist;
        return dt;
    }
    
    SinglyLinkedListNode* dummy = llist;
    
    for(int i = 0; i < position - 1; ++i){
        dummy = dummy->next;
        
        if(dummy == nullptr){
            throw std::invalid_argument("Invalid input");
        }
    }
    
    dt->next = dummy->next;
    dummy->next = dt;
    
    return llist;
}
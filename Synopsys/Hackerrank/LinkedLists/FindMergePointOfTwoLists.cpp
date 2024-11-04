#include <bits/stdc++.h>

class ListNode {
public:
    int data;
    ListNode* next;

    ListNode(int data) : data(data), next(nullptr) {}
};


// Time O(n) Space O(1)
int findMergeNode(ListNode* head1, ListNode* head2) {
    if (!head1 || !head2) {
        return -1; // Return -1 or handle as needed for no merge
    }

    ListNode* pointer1 = head1;
    ListNode* pointer2 = head2;

    // Traverse both lists
    while (pointer1 != pointer2) {
        // If we reach the end of one list, start at the beginning of the other
        pointer1 = pointer1 ? pointer1->next : head2;
        pointer2 = pointer2 ? pointer2->next : head1;
    }

    // Either they meet at the merge point or at nullptr (if no merge)
    return pointer1 ? pointer1->data : -1; // Return the data of the merge node
}


// Time O(n + m): n -> len(head1), m->len(head2) Space O(n): because of set
int findMergeNode(ListNode* head1, ListNode* head2) {
    // Create a set to store nodes from the first list
    std::unordered_set<ListNode*> visited_nodes;

    // Traverse the first list and store its nodes in the set
    ListNode* current = head1;
    while (current != nullptr) {
        visited_nodes.insert(current);
        current = current->next;
    }

    // Traverse the second list and check for a merge point
    current = head2;
    while (current != nullptr) {
        if (visited_nodes.find(current) != visited_nodes.end()) {
            return current->data;  // Return the data of the merge node
        }
        current = current->next;
    }

    return -1;  // Return -1 if no merge point is found
}

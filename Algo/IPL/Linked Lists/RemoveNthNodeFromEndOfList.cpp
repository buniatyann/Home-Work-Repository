// Leetcode 19

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* behind = dummy;
    ListNode* ahead = dummy;
    for (int i = 0; i <= n; ++i) {
        ahead = ahead->next;
    }

    while (ahead != nullptr) {
        ahead = ahead->next;
        behind = behind->next;
    }

    ListNode* temp = behind->next;
    behind->next = temp->next;;
    delete temp;
    
    return dummy->next;
}
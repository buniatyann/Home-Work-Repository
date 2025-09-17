// Leetcode 206

ListNode* reverseList(ListNode* head) {
    if (!head) {
        return head;
    }

    ListNode* curr = head;
    ListNode* prev = nullptr;
    while (curr != nullptr) {
        ListNode* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    return prev;
}
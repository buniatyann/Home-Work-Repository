// Leetcode 83

ListNode* removeDuplicates(ListNode* head) {
    if (head == nullptr) {
        return head;
    }

    ListNode* curr = head;
    while (curr != nullptr && curr->next != nullptr) {
        if (curr->val == curr->next->val) {
            ListNode* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
        else {
            curr = curr->next;
        }
    }

    return head;
}
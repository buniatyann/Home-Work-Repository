// Leetcode 867

bool hasCycle(ListNode *head) {
    if (head == nullptr) {
        return head;
    }   

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            return true;
        }
    }

    return false;
}
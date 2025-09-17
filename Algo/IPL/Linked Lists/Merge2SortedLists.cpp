// Leetcode 21
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            curr->next = list1;
            list1 = list1->next;
        } 
        else {
            curr->next = list2;
            list2 = list2->next;
        }
        
        curr = curr->next;
    }
    
    if (list1 != nullptr) {
        curr->next = list1;
    } 
    else if (list2 != nullptr) {
        curr->next = list2;
    }
    
    return dummy.next;
}
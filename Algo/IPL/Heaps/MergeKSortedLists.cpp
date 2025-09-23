#include <vector>
#include <queue>

struct ListNode {
    ListNode* next;
    int val;
    ListNode(int i) : val(i), next(nullptr) {}
};

// leetcode 23
ListNode* mergeKLists(const std::vector<ListNode*>& lists) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;

    for (ListNode* list : lists) {
        while (list != nullptr) {
            q.push(list->val);
            list = list->next;
        }
    }

    if (q.empty()) {
        return nullptr;
    }

    ListNode* dummy = new ListNode(-1);
    ListNode* curr = dummy;
    while (!q.empty()) {
        curr->next = new ListNode(q.top());
        curr = curr->next;
        q.pop();
    }

    ListNode* result = dummy->next;
    delete dummy; 
    return result;
}
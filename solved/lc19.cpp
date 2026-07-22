


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverse(ListNode* node) {
    ListNode* curr = nullptr;
    while (node != nullptr) {
        auto next = node->next;
        node->next = curr;
        curr = node;
        node = next;
    }
    return curr;
}

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* r = reverse(head);
        ListNode* curr = nullptr;
        while (r != nullptr) {
            auto next = r->next;
            if (n == 1) {
                r = next;
                n--;
            } else {
                n--;
                r->next = curr;
                curr = r;
                r = next;
            }
        }
        return curr;
    }
};


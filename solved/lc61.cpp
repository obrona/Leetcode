
// find the length of the linked list.
// split the list into (length - k, k).
// shift the right half to the front.

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || k == 0) return head;

        int len = 1;
        auto curr = head;
        while (curr->next) {
            len++;
            curr = curr->next;
        }

        k %= len;
        if (k == 0) return head;

        auto new_tail = head;
        for (int i = 0; i < len - k - 1; i++) new_tail = new_tail->next;

        auto new_head = new_tail->next;
        auto tail = new_head;
        while (tail->next) tail = tail->next;

        tail->next = head;
        new_tail->next = nullptr;
        return new_head;
    }
};
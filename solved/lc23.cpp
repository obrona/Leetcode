#include <vector>
#include <queue>
using namespace std;

// use a priority queue with state {head->val, head (whatever is left of the list)}.
// pick the smallest elem, then push {head->next->val, head->next} if the next elem is not nullptr.

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [] (const pair<int, ListNode*> p1, const pair<int, ListNode*> p2) {
            return p1.first > p2.first;
        };

        ListNode* curr = nullptr;
        priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, decltype(cmp)> pq(cmp);

        for (auto ptr : lists) {
            if (ptr == nullptr) continue;
            pq.emplace(ptr->val, ptr);
        }

        while (!pq.empty()) {
            auto [_a, ptr] = pq.top(); pq.pop();
            auto next = ptr->next;
            ptr->next = curr;
            curr = ptr;

            if (next) pq.emplace(next->val, next);
        }

        curr = reverse(curr);
        return curr;
    }
};
#include <bits/stdc++.h>
using namespace std;

// greedy does not work.
// eg n = 12, greedy is [1,2,3,4,0,1,0,1] len = 8, optimal is [1,2,3,0,1,2,3] len = 7.
// use dp.
// dp(target, prev)
// prev means we have taken scores 1,2,3,...prev - 1
// total sum is 0.5 * (prev**2 - prev)
// so time complexity is O(n^1.5).
// all instances can share the same dp, this is 1 optimisation.

bool has_init = false;
array<array<int, 450>, 100001> store;

void init() {
    for (auto& r : store) r.fill(-1);
    has_init = true;
}

int dp(int left, int prev) {
    int& ans = store[left][prev];
    if (ans != -1) return ans;

    if (left == 0) return ans = 0;

    if (prev == 0) return ans = 1 + dp(left - 1, 1);
    
    int take = (left < prev + 1) ? 999999 : 1 + dp(left - prev - 1, prev + 1);
    int notake = 1 + dp(left, 0);
    return ans = min(notake, take);
}




class Solution {
public:
    int minDays(int n) {
        if (!has_init) init();
        return dp(n, 0);
    }
};

int main() {
    Solution sol;

    int ans = sol.minDays(9);
    cout << ans << endl;
}
#include <bits/stdc++.h>
using namespace std;

// to get O(n) solution.
// for each elem, get mod k.
// a valid subarray must have all elems have the same modulo.
// suppose k = 4, we have length 5 of modulo 3.
// so the sum of the subarray we take from this block must be modulo 3
// then we just need to find i s.t 3 * i modulo k = 3
// we can just try i in [1, 2, 3 .. length of block]

// mathematically we want a formula for all i s.t a * i mod b = a.

int helper(int a, int k, int len) {
    int best = 1;
    for (int i = 2; i <= len; i++) {
        long long x = (long long) a * i;
        if (x % k == a) best = i;
    }
    return best;
}

class Solution {
public:
    int resilientSubarray(vector<int>& nums, int k) {
        int best = 1;
        int p = 0;
        while (p < nums.size()) {
            int s = p;
            int tgt = nums[s] % k;
            while (s < nums.size() && nums[s] % k == tgt) s++;

            int res = helper(tgt, k, s - p);
            best = max(best, res);

            p = s;
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,5,4,8};
    int k = 4;

    cout << sol.resilientSubarray(nums, k) << endl;
}

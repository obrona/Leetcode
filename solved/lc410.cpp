#include <bits/stdc++.h>
using namespace std;

// classic binary search problem.
// binary search min max sum.
// take from left to right until we hit the limit.

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int s = *max_element(nums.begin(), nums.end());
        int e = accumulate(nums.begin(), nums.end(), 0);

        while (s < e) {
            int m = (s + e) >> 1;

            int cnt = 0;
            int store = 0;
            int p = 0;
            while (p < nums.size()) {
                if (store + nums[p] > m) {
                    cnt++;
                    store = 0;
                } else {
                    store += nums[p++];
                }
            }
            cnt++;

            if (cnt <= k) {
                e = m;
            } else {
                s = m + 1;
            }
        }

        return s;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {7,2,5,10,8};
    int k = 2;

    int ans = sol.splitArray(nums, k);
    cout << ans << endl;
}


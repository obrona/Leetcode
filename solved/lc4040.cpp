#include <bits/stdc++.h>
using namespace std;

// 2*x means left shift by 1.
// floor(x/2) means right shift by 1.
// given a number x, we can left shift and right shift any number of times and in any order.
// notice that l -> r is useless, we can remove it.
// multiplication must all occur before division, means we cannot have rl somewhere.
// lllrr can be reduce to l.
// so only valid ops are l, ll, lll... and r, rr, rrr...

class Solution {
public:
    vector<int> nums;
    int invalid = int(1e7);
    int store[100][5001];

    void init(int len, int sum) {
        for (int l = 0; l < len; l++) {
            for (int s = 0; s <= sum; s++) {
                store[l][s] = -1;
            }
        }
    }

    int dp(int i, int s) {
        if (s == 0) return 0;
        if (i == nums.size()) return invalid;

        int& ans = store[i][s];
        if (ans != -1) return store[i][s];

        int notake= dp(i + 1, s);
        
        int take = invalid;
        
        // l ops only.
        int lops = 0;
        int t_curr = nums[i];
        while (t_curr <= s) {
            take = min(take, lops + dp(i + 1, s - t_curr));
            t_curr <<= 1;
            lops++;
        }

        int rops = 0;
        int t_curr_2 = nums[i];
        while (t_curr_2 > s) {
            t_curr_2 >>= 1;
            rops++;
        }
        while (t_curr_2 > 0) {
            take = min(take, rops + dp(i + 1, s - t_curr_2));
            t_curr_2 >>= 1;
            rops++;
        }
        
        return ans = min(take, notake);
    }

    int minOperations(vector<int>& nums, int sum) {
        this->nums = nums;
        init(nums.size(), sum);
        int ans = dp(0, sum);
        return (ans >= invalid) ? -1 : ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,6,10};
    int sum = 4;
    int ans = sol.minOperations(nums, sum);
    cout << ans << endl;
}
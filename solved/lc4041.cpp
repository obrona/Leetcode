#include <bits/stdc++.h>
using namespace std;

// 2*x means left shift by 1.
// floor(x/2) means right shift by 1.
// given a number x, we can left shift and right shift any number of times and in any order.
// notice that l -> r is useless, we can remove it.
// so in the optimal solution, there is no lr
// only rr...rrll...lll

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
        int curr = nums[i];
        int rops = 0;
        while (curr > 0) {
            int x = curr;
            int lops = 0;
            while (x <= s) {
                take = min(take, lops + rops + dp(i + 1, s - x));
                
                x <<= 1;
                lops++;
            }
            
            curr >>= 1;
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
    vector<int> nums = {6,3};
    int sum = 8;

    int ans = sol.minOperations(nums, sum);
    cout << ans << endl;
}
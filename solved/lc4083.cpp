#include <bits/stdc++.h>
using namespace std;

// just make sure adjacent elements are not equal.

class Solution {
public:
    int minDeletions(vector<int>& nums) {
        int cnt = 0;
        for (int i = 0; i < nums.size();) {
            int curr = nums[i];
            
            i++;
            while (i < nums.size() && nums[i] == curr) {
                cnt++;
                i++;
            }
        }
        return cnt;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,1,2,2,2,3};

    int ans = sol.minDeletions(nums);
    cout << ans << endl;
}
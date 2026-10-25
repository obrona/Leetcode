#include <bits/stdc++.h>
using namespace std;

// O(n**2) is possible.
// really just check and store the required state.

class Solution {
public:
    int countStaircase(vector<int>& nums) {
        int ans = 0;
        for (int s = 0; s < nums.size(); s++) {
            int p = 0;
            int completed = 0;
            unordered_map<int, int> freqs;
            unordered_map<int, int> pos;

            for (int e = s; e < nums.size(); e++) {
                int x = nums[e];
                auto it = freqs.find(x);
                if (it == freqs.end()) {
                    it = freqs.emplace(x, 0).first;
                    pos[x] = p++;
                }

                int my_pos = pos[x];
                it->second++;
                if (it->second > my_pos + 1) {
                    // completed before, but from now on cannot fulfill anymore.
                    break;
                } else if (it->second == my_pos + 1) {
                    if (++completed == p) ans++;
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,8,8,2,2,2};

    int ans = sol.countStaircase(nums);
    cout << ans << endl;
}
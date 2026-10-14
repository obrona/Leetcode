#include <bits/stdc++.h>
#include <ranges>
using namespace std;

// dp problem
// 1st we sort the array in increasing order.
// let dp[i][b] be the longest sequence we can get when we select arr[i] (sorted already)
// b is to store whether we will increment arr[i] or not.
// then the next value is arr[i] + 1 or arr[i] + 2.
// let say the next value to get is x
// can go to the earliest right index with x - 1 (because we can increment).
// if cannot the earliest right index with x
// it is optimal to chase the earliest right index.

class Solution {
public:
    int N;
    vector<int> nums;
    unordered_map<int, vector<int>> index_store;
    vector<vector<optional<int>>> dp_store;

    int dp(int i, int b) {
        if (i == N) return 0;

        auto& opt = dp_store[i][b];
        if (opt) return opt.value();

        int res = 1;
        int now = nums[i] + b;

        auto it = index_store.find(now);
        if (it != index_store.end()) {
            auto& arr = it->second;
            auto it_idx = upper_bound(arr.begin(), arr.end(), i);
            if (it_idx != arr.end()) {
                res = max(res, 1 + dp(*it_idx, 1));
                
                // can return early.
                opt = res;
                return res;
            }

           
        }

        it = index_store.find(now + 1);
        if (it != index_store.end()) {
            auto& arr = it->second;
            auto it_idx = upper_bound(arr.begin(), arr.end(), i);
            if (it_idx != arr.end()) {
                res = max(res, 1 + dp(*it_idx, 0));
            }
        }

        opt = res;
        return res;
    }

    int maxSelectedElements(vector<int>& nums) {
        N = nums.size();
        sort(nums.begin(), nums.end());
        this->nums = nums;
        dp_store = vector(nums.size(), vector<optional<int>>(2, nullopt));

        for (int i = 0; i < nums.size(); i++) {
            index_store[nums[i]].push_back(i);
        }

        int res = 1;
        for (int i : views::iota(0, N)) {
            res = max(res, dp(i, 0));
            res = max(res, dp(i, 1));
        }

        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,4,7,10};
    int ans = sol.maxSelectedElements(nums);
    cout << ans << endl;
}
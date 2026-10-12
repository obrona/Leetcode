#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxProductPair(vector<int>& nums, int target) {
        unordered_map<int,int> store;
        for (int i = 0; i < nums.size(); i++) {
            store[nums[i]] = i;
        }

        vector<int> res;
        int val = -999999999;

        for (auto [x, idx] : store) {
            if (x <= target - x) continue;

            auto it = store.find(target - x);
            if (it == store.end()) continue;
            if (x * (target - x) <= val) continue;

            res = {idx, it->second};
            val = x * (target - x);
        }

        if (!res.size()) return {-1, -1};
        return res;
    }
};
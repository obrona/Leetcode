#include <bits/stdc++.h>
using namespace std;
// count frequency of elems.
// then use nth_element

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> store;
        for (int x : nums) store[x]++;

        vector<pair<int,int>> arr(store.begin(), store.end());
        nth_element(arr.begin(), arr.begin() + arr.size() - k, arr.end(),
                    [] (const auto& p1, const auto& p2) { return p1.second < p2.second; });

        vector<int> out;
        for (auto it = arr.begin() + arr.size() - k; it != arr.end(); it++) {
            out.push_back(it->first);
        }

        return out;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,1,1,2,2,3};
    int k = 2;

    auto ans = sol.topKFrequent(nums, k);
    for (int x : ans) cout << x << " ";
    cout << endl;
}
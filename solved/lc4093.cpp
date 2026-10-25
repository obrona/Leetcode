#include <bits/stdc++.h>
using namespace std;

// for each element we have 2 choices x or the sorted in decreasing order digit sx.
// if x >= sx we choose x and use no operation.
// want to maximise sum so sort by (sx - x) in decreasing order.

int sort_digits(int x) {
    string s = to_string(x);
    sort(s.begin(), s.end(), greater<char>{});
    return stoi(s);
}

class Solution {
public:
    long long maximizeSum(vector<int>& nums, int k) {
        vector<tuple<int,int,int>> store;
        for (int x : nums) {
            int sx = sort_digits(x);
            store.emplace_back(x, sx, sx - x);
        }

        sort(store.begin(), store.end(), [] (const auto& t1, const auto& t2) { return get<2>(t1) > get<2>(t2); });
        long long sum = 0;
        
        for (auto [x, sx, diff] : store) {
            if (k == 0) {
                sum += x;
            } else {
                sum += sx;
                k -= (x != sx);
            }

        }

        return sum;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {102, 90, 14};
    int k = 2;

    auto ans = sol.maximizeSum(nums, k);
    cout << ans << endl;
}
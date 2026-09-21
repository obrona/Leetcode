#include <bits/stdc++.h>
using namespace std;

// for intervals with the same starting point, keep the one with the rightmost endpoint.
// then sort in increasing start point.
// traverse left to right, keep the max endpoint.
// at interval i, if endpoint i <= max endpoint, it is covered, since the max endpoint 
// is from a interval that started earlier.


class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int cnt = 0;
        unordered_map<int,int> store;

        for (auto& itv : intervals) {
            auto it = store.find(itv[0]);
            if (it != store.end()) {
                cnt++;
            }
            
            store[itv[0]] = max(store[itv[0]], itv[1]);
        }

        vector<pair<int,int>> arr(store.begin(), store.end());
        sort(arr.begin(), arr.end());

        int max_left = -1;
        for (auto [s, e] : arr) {
            if (max_left >= e) cnt++;
            max_left = max(max_left, e);
        }

        return intervals.size() - cnt;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1,4}, {3,6}, {2,8}};
    int ans = sol.removeCoveredIntervals(intervals);
    cout << ans << endl;
}
#include <bits/stdc++.h>
using namespace std;

// for each bar, we can extend as far left until we encounter a bar that is shorter.
// same for the right.
// we use monotonic stack for this.

vector<int> left_shorter(const vector<int>& heights) {
    vector<pair<int,int>> store;
    vector<int> out(heights.size());
    for (int i = 0; i < heights.size(); i++) {
        int h = heights[i];
        while (!store.empty() && store.back().second >= h) {
            store.pop_back();
        }
        
        if (store.empty()) {
            out[i] = -1;
        } else {
            out[i] = store.back().first;
        }
        
        store.emplace_back(i, h);
    }
    return out;
}

vector<int> right_shorter(const vector<int>& heights) {
    vector<pair<int,int>> store;
    vector<int> out(heights.size());
    for (int i = heights.size() - 1; i >= 0; i--) {
        int h = heights[i];
        while (!store.empty() && store.back().second >= h) {
            store.pop_back();
        }
        
        if (store.empty()) {
            out[i] = heights.size();
        } else {
            out[i] = store.back().first;
        }
        store.emplace_back(i, h);
    }
    return out;
}

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        auto left_res = left_shorter(heights);
        //for (int x : left_res) cout << x << " "; cout << endl;
        auto right_res = right_shorter(heights);
        //for (int x : right_res) cout << x << " "; cout << endl;
        int best = 0;
        for (int i = 0; i < heights.size(); i++) {
            int l = left_res[i], r = right_res[i];
            best = max(best, (r - l - 1) * heights[i]);
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> heights = {1, 1};
    int ans = sol.largestRectangleArea(heights);
    println("Ans: {}", ans);
}
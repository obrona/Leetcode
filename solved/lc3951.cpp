#include <bits/stdc++.h>
using namespace std;

// of bulbs is ceil(brightness / 3).
// just merge the intervels.

vector<pair<int,int>> merge_intervals(const vector<vector<int>>& intervals) {
    auto cpy = intervals;
    sort(cpy.begin(), cpy.end(), [](auto& i1, auto& i2) {
        return (i1[0] == i2[0]) ? i1[1] > i2[1] : i1[0] < i2[0];
    });

    vector<pair<int,int>> out;
    int s = cpy[0][0], e = cpy[0][1];
    for (auto& v : cpy) {
        int l = v[0], r = v[1];
        if (r <= e) continue;
        
        if (l <= e && r > e) {
            e = r;
        } else if (l > e) {
            out.emplace_back(s, e);
            s = l, e = r;
        }
    }

    out.emplace_back(s, e);
    return out;
}

class Solution {
public:
    long long minEnergy(int n, int brightness, vector<vector<int>>& intervals) {
        int numLightBulbs = (int) ceil(brightness / 3.0);
        vector<pair<int,int>> merged = merge_intervals(intervals);
        
        long long cnt = 0;
        for (auto& [s, e] : merged) cnt += e - s + 1;

        return cnt * numLightBulbs;
    }
};

int main() {
    Solution sol;
    int n = 5;
    int brightness = 5;
    vector<vector<int>> intervals = {{6,12}};

    long long ans = sol.minEnergy(n, brightness, intervals);
    println("{}", ans);
}
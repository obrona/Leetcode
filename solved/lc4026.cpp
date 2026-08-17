#include <bits/stdc++.h>
using namespace std;

// suppose the max gap occurs in j_i-1, j_i, then we must have stuff everything <= j_i-1 as left as possible
// and everything >= j_i as right as possible.
// get the prefix and suffix min, then get the best j_i-1, j_i.

class Solution {
public:
    int maximumGap(string skill, string station) {
        vector<int> prefix_min(skill.size()), suffix_min(skill.size());
        int p = 0;
        for (int i = 0; i < skill.size(); i++) {
            while (p < station.size() && station[p] != skill[i]) p++;
            prefix_min[i] = p;
            p++;
        }

        p = station.size() - 1;
        for (int i = skill.size() - 1; i >= 0; i--) {
            while (p >= 0 && station[p] != skill[i]) p--;
            suffix_min[i] = p;
            p--;
        }

        int best = 0;
        for (int i = 0; i < skill.size() - 1; i++) {
            best = max(best, suffix_min[i + 1] - prefix_min[i]);
        }

        return best;
    }

};

int main() {
    Solution sol;
    string skill = "xyz";
    string station = "xyzz";
    int ans = sol.maximumGap(skill, station);
    println("Ans: {}", ans);
}
#include <bits/stdc++.h>
using namespace std;

// 7^3 = 343 possible points only, so just brute force.

struct Hash {
    size_t operator()(const tuple<int,int,int>& p) const {
        auto [x, y, z] = p;
        return x + (y << 3) + (z << 6);
    }
};

class Solution {
public:
    int minGenerations(vector<vector<int>>& points, vector<int>& target) {
        unordered_set<tuple<int,int,int>, Hash> store;
        for (const auto& p : points) {
            store.emplace(p[0], p[1], p[2]);
        }

        tuple<int,int,int> t = {target[0], target[1], target[2]};
        if (store.contains(t)) return 0;

        for (int g = 0; store.size() < 343; g++) {
            unordered_set<tuple<int,int,int>, Hash> tmp;
            for (auto it1 = store.begin(); it1 != store.end(); it1++) {
                for (auto it2 = next(it1); it2 != store.end(); it2++) {
                    auto [x1, y1, z1] = *it1;
                    auto [x2, y2, z2] = *it2;

                    tuple<int,int,int> pt = {(x1 + x2) / 2, (y1 + y2) / 2, (z1 + z2) / 2};
                    if (pt == t) return g + 1;

                    if (!store.contains(pt)) tmp.insert(pt);
                }
            }

            if (tmp.size() == 0) break;
            store.insert(tmp.begin(), tmp.end());
        }

        return -1;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> points = {{0,0,0}};
    vector<int> target = {{1,1,1}};

    int ans = sol.minGenerations(points, target);
    println("{}", ans);
}
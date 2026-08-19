#include <bits/stdc++.h>
using namespace std;

// if no seats are reserved then can have 2 groups.
// if seats are reserved then eiher 2, 1 or 0 groups.
// can only have 2 groups if the free sections are [2,3,4,5] and [6,7,8,9].

int helper(const vector<int>& taken) { 
    array<bool, 3> store = {true, true, true};

    for (int x : taken) {
        if (x >= 2 && x <= 5) store[0] = false;
        if (x >= 4 && x <= 7) store[1] = false;
        if (x >= 6 && x <= 9) store[2] = false;
    }

    if (store[0] && store[2]) return 2;
    if (any_of(store.begin(), store.end(), identity{})) return 1;
    return 0;
}

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, vector<int>> taken;
        for (auto& v : reservedSeats) {
            taken[v[0]].push_back(v[1]);
        }
        for (auto& [k, v] : taken) {
            sort(v.begin(), v.end());
        }

        int ans = (n - taken.size()) * 2;
        for (const auto& [r, taken_seats] : taken) {
            ans += helper(taken_seats);
        }

        return ans;
    }
};
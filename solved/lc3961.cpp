#include <bits/stdc++.h>
using namespace std;

// for each device, the only 2 values that matter are the smallest and 2nd smallest values.
// very simple algorithm.
// for the smallest 1st value among all devices, let say it is at device i.
// we give it to device j.
// then the best way is for all other devices to give their smallest value to device j too.

// so just try all possible j.

// some edge cases when a device has only 1 value.
// but the only case we need to consider is when the device containing the smallest 1st value is length 1.
// then the computation is different.

class Solution {
public:
    long long maxRatings(vector<vector<int>>& units) {
        for (vector<int>& unit : units) {
            if (unit.size() > 1) {
                partial_sort(unit.begin(), unit.begin() + 2, unit.end());
            }
        }

        int s = 999999999;
        long long sum = 0;
        for (auto& u : units) {
            s = min(s, u[0]);

            if (u.size() == 1) {
                sum += u[0];
            } else {
                sum += u[1];
            }
        }

        bool check = any_of(units.begin(), units.end(), [s] (auto &u) { return u.size() == 0 && u[0] == s; });
        if (check) {
            return sum;
        }

        long long best = 0;
        for (auto& u : units) {
            long long ans = s + sum - (u.size() == 1 ? u[0] : u[1]);
            best = max(best, ans);
        } 

        return best;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> units = {{1,2,3}, {4,5,6}};
    cout << sol.maxRatings(units) << endl;
}
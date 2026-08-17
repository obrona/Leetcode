#include <bits/stdc++.h>
using namespace std;

// for each car, find traffic[i] s.t arrival time % period < traffic[i].

class Solution {
public:
    int minPenalty(int period, vector<int>& lights, vector<int>& arrivalTime) {
        set<int> store;
        for (int l : lights) store.insert(l);

        int ans = 0;
        for (int t : arrivalTime) {
            int x = t % period;
            auto it = store.upper_bound(x);
            if (it == store.end()) ans = max(ans, period - x);
        }

        return ans;
    }
};
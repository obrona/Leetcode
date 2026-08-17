#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// we want to try all permutations of solving requests, but O(N!) is too long.
// let dp[i][bm] be the earliest time we can finish all requests in bm and the last request is index i.
// in the optimal sequence r1, r2, r3 ... rn, dp[ri][bm] must be the smallest time, otherwise we can 
// make the final time smaller.
// suppose we are at dp[i][bm] and the next index is j, the time needed is max(t + dist(rj, ri), arrival j).

class Solution {
public:
    int len;
    vector<ll> store;

    int key(int i, int bm) {
        return i * (1 << len) + bm;
    }

    ll dp(int i, int bm, const vector<vector<int>>& requests) {
        ll idx = key(i, bm);
        if (store[idx] != -1) return store[idx];

        ll best = 1e15;
        for (int j = 0; j < requests.size(); j++) {
            if (j == i || ((bm >> j) & 1) == 0) continue;
            ll t = dp(j, bm - (1 << i), requests);
            best = min(
                best, 
                max(t + abs(requests[j][1] - requests[i][1]), (ll) requests[i][0])
            );
        }

        return store[idx] = best; 
    }

    long long elevatorRequests(int n, int start, vector<vector<int>>& requests) {
        len = requests.size();
        store = vector(len * (1 << len), -1LL);

        for (int i = 0; i < len; i++) {
            store[key(i, 1 << i)] = max(abs(start - requests[i][1]), requests[i][0]);
        }

        ll best = 1e15;
        for (int i = 0; i < len; i++) {
            best = min(best, dp(i, (1 << len) - 1, requests));
        }

        return best;
    }
};

int main() {
    Solution sol;
    int n = 7;
    int start = 3;
    vector<vector<int>> requests = {{0,5}, {0,1}, {6,3}};

    ll ans = sol.elevatorRequests(n, start, requests);
    cout << ans << endl;
}
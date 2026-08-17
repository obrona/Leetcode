#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// we split the elevators into 2 sets, floors <= start and floors > start.
// clearly we clear floors in decreasing order for the 1st set and increasing order for the 2nd set.
// suppose not we go to from floor 0 to floor 3 then back to floor 1, wel on the process to go to floor 3
// we fulfilled floor 1 request.
// we have 2 choices at each state.

struct TupleHash {
    size_t operator()(const std::tuple<bool,int,int>& t) const noexcept {
        auto [b, x, y] = t;
        return (static_cast<size_t>(b) * 1501 + x) * 1501 + y;
    }
};

pair<vector<int>, vector<int>> split(int start, const vector<int>& requests) {
    vector<int> left, right;
    for (int r : requests) {
        if (r <= start) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end(), [] (int x1, int x2) { return x1 > x2; });
    sort(right.begin(), right.end());
    return {left, right};
}

class Solution {
public:
    ll MAX = 1e14;
    unordered_map<tuple<bool,int,int>, ll, TupleHash> store;

    // we start at left[0] or right[0]. 
    // if start is neither left[0] or right[0], then we move.
    ll dp(bool side, int li, int ri, const vector<int>& left, const vector<int>& right) {
        tuple<bool, int, int> key = {side, li, ri};
        if (store.contains(key)) {
            return store[key];
        }
        if (li == left.size() && ri == right.size()) {
            return 0;
        }

        int curr_pos;
        if (!side) {
            curr_pos = (li == 0) ? left[0] : left[li - 1];
        } else {
            curr_pos = (ri == 0) ? right[0] : right[ri - 1];
        }

        ll best = MAX;
        int num_left = left.size() - li + right.size() - ri;

        // move left.
        if (li < left.size()) {
            ll res = abs(curr_pos - left[li]) * (ll) num_left + dp(0, li + 1, ri, left, right);
            best = min(best, res);
        }
        if (ri < right.size()) {
            ll res = abs(curr_pos - right[ri]) * (ll) num_left + dp(1, li, ri + 1, left, right);
            best = min(best, res);
        }

        return store[key] = best;
    }

    long long elevatorRequests(int n, int start, vector<int>& requests) {
        auto [left, right] = split(start, requests);

        ll best = MAX;
        if (left.size() > 0) {
            ll res = abs(start - left[0]) * requests.size() + dp(0, 0, 0, left, right);
            best = min(best, res);
        }
        if (right.size() > 0) {
            ll res = abs(start - right[0]) * requests.size() + dp(1, 0, 0, left, right);
            best = min(best, res);
        }

        return best;
    }
};

int main() {
    Solution sol;

    int n = 8;
    int start = 3;
    vector<int> requests = {3, 7, 1};

    ll ans = sol.elevatorRequests(n, start, requests);
    println("Ans: {}", ans);

}
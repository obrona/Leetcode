#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// brute force dp.
// dp(i) = min cost to change sourc[i:] to target[i:]
// if 1st char match, then dp(i + 1) is a possibility
// else try to use the (pattern, replacement) pairs.

// time complexity is O(5000 * 200 * 20) = 2e7 which is ok.



class Solution {
public:
    string src, tgt;
    vector<tuple<string, string, int>> tuples;
    vector<ll> store;

    bool can_match(const string& src, const string& tgt, int i, const string& pattern, const string& replace) {
        if (src.size() - i < pattern.size()) return false;
        
        for (int j = 0; j < pattern.size(); j++) {
            bool a = (src[i + j] == pattern[j] || pattern[j] == '*') && tgt[i + j] == replace[j];
            if (!a) return false;
        }
        return true;
    }

    ll dp(int i) {
        if (i == src.size()) return 0;
        auto& ans = store[i];
        if (ans != -2) return ans;

        ll notake = (src[i] == tgt[i]) ? dp(i + 1) : INT_MAX;
        ll take = INT_MAX;
        for (const auto& [p, r, c] : tuples) {
            if (can_match(src, tgt, i, p, r)) {
                take = min(take, c + dp(i + p.size()));
            }
        }
        ans = min(notake, take);
        return ans;
    }


    int minCost(string source, string target, vector<vector<string>>& rules, vector<int>& costs) {
        src = source;
        tgt = target;

        for (int i = 0; i < rules.size(); i++) {
            auto p = rules[i][0], r = rules[i][1];
            int cost = costs[i];
            for (char c : p) cost += c == '*';
            tuples.emplace_back(p, r, cost);
        }

        store = vector<ll>(source.size(), -2);

        ll ans = dp(0);
        return (ans >= INT_MAX) ? -1 : ans;
    }
};

int main() {
    Solution sol;
    string source = "hello";
    string target = "world";
    vector<vector<string>> rules = {{"he","wo"},{"llo","rld"}};
    vector<int> costs = {3,4};
    int ans = sol.minCost(source, target, rules, costs);
    cout << ans << endl;
}
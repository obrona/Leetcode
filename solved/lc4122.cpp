#include <bits/stdc++.h>
using namespace std;

// just use a priority queue.
// (v, d) means signal from some node reaches node v at time d.
// since there is at most 1 directed edge from any node u to any node v, 
// there is no need to store a set of nodes whose signal we received.
// just decrement the cnt.

vector<vector<pair<int,int>>> make_adj(int n, const vector<vector<int>>& edges) {
    vector<vector<pair<int,int>>> adj(n, vector<pair<int,int>>());

    for (auto& e : edges) {
        adj[e[0]].emplace_back(e[1], e[2]);
    }

    return adj;
}

class Solution {
public:
    vector<long long> earliestActivationTimes(int n, vector<vector<int>>& edges, vector<int>& requiredSignals) {
        auto adj = make_adj(n, edges);
        vector<long long> time(n, -1);
        auto cmp = [] (const pair<int,long long>& p1, const pair<int,long long>& p2) { return p1.second > p2.second; };
        priority_queue<pair<int,long long>, vector<pair<int,long long>>, decltype(cmp)> pq;
        
        requiredSignals[0] = 0;
        time[0] = 0;
        for (auto [v, d] : adj[0]) {
            pq.emplace(v, d);
        }

        while (!pq.empty()) {
            auto [v, d] = pq.top(); pq.pop();
            int& cnt = requiredSignals[v];
            if (--cnt == 0) {
                time[v] = d;
                for (auto [nv, nd] : adj[v]) {
                    if (requiredSignals[nv] == 0) continue;
                    pq.emplace(nv, d + nd);
                }
            }
        }

        return time;

    }
};

int main() {
    Solution sol;

    int n = 4;
    vector<vector<int>> edges = {{0, 1, 2}, {1, 0, 1}, {1, 2, 1}, {2, 3, 1}, {3, 2, 1}};
    vector<int> requiredSignals = {3, 1, 2, 1};

    auto ans = sol.earliestActivationTimes(n, edges, requiredSignals);
    for (auto x : ans) cout << x << " ";
    cout << endl;
}


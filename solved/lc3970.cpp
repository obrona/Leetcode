#include <bits/stdc++.h>
using namespace std;

// it is possible to have loops in the path to break up consecutive identical characters.
// the state is simply (node, count).
// no need to store the character as if we know the node, we know the character.
// this state already takes care of loops.

class Solution {
public:
    vector<vector<pair<int,int>>> make_adj(int n, const vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> out(n, vector<pair<int,int>>());
        for (auto& e : edges) {
            out[e[0]].emplace_back(e[1], e[2]);
        }
        return out;
    }

    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        auto adj = make_adj(n, edges);
        vector<vector<int>> store = vector(n, vector(k + 1, -1));
        
        auto cmp = [] (tuple<int,int,int> p1, tuple<int,int,int> p2) {
            return get<2>(p1) > get<2>(p2);
        };

        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, decltype(cmp)> pq(cmp);
        pq.emplace(0, 1, 0);

        while (!pq.empty()) {
            auto [v, cnt, d] = pq.top(); pq.pop();
            if (store[v][cnt] != -1) continue;
            
            store[v][cnt] = d;
            if (v == n - 1) return d;

            for (auto [u, w] : adj[v]) {
                int uc = labels[u];
                int new_cnt = (uc == labels[v]) ? cnt + 1 : 1;
                if (new_cnt > k || store[u][new_cnt] != -1) continue;

                pq.emplace(u, new_cnt, d + w);
            }
        }

        return -1;
    }
};


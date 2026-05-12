#include <bits/stdc++.h>
using namespace std;

// binary search threshold.
// the node is (v, k) where k is the # of heavy edges used.
// after setting a threshold, the weight of edges is either 0 if it is a light edge or 1 if it is a heavy edge.
// use dijkstra algo to find the shortest path from src to tgt, then check if it is <= k.

vector<vector<pair<int,int>>> get_adj(int n, const vector<vector<int>>& edges) {
    vector<vector<pair<int,int>>> out(n, vector<pair<int,int>>());
    for (const vector<int>& e : edges) {
        out[e[0]].emplace_back(e[1], e[2]);
        out[e[1]].emplace_back(e[0], e[2]);
    }
    return out;
}

bool search(int n, int src, int tgt, int k, const vector<vector<pair<int,int>>>& adj, int thres) {
    vector<int> ds(n, -1);
    auto cmp = [] (const pair<int,int>& p1, const pair<int,int>& p2) { 
        if (p1.second == p2.second) return p1.first < p2.first;
        return p1.second < p2.second;
    };
    set<pair<int,int>, decltype(cmp)> pq(cmp);

    pq.emplace(src, 0);

    while (!pq.empty()) {
        auto [v, d] = *pq.begin();
        pq.erase(pq.begin());

        if (ds[v] != -1) continue;

        ds[v] = d;
        for (auto [u, w] : adj[v]) {
            if (ds[u] != -1) continue;
            pq.emplace(u, d + (w > thres));
        }
    }

    return ds[tgt] != -1 && ds[tgt] <= k;

}

class Solution {
public:
    int minimumThreshold(int n, vector<vector<int>>& edges, int source, int target, int k) {
        auto adj = get_adj(n, edges);

        // do compression on the edges, we dont have to consider all values in [0, 1e9]
        // but have to consider the case when all edges can be heavy or no edges can be heavy
        vector<int> ws;
        int ma = 0;
        for (const auto& e : edges) {
            ws.push_back(e[2]);
            ma = max(ma, e[2]);
        }
        ws.insert(ws.end(), {0, ma});
        sort(ws.begin(), ws.end());

        int s = 0, e = ws.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            bool can = search(n, source, target, k, adj, ws[m]);
            if (can) {
                e = m;
            } else {
                s = m + 1;
            }
        }
        //println("{}", s);
        bool check = search(n, source, target, k, adj, ws[s]);
        return (check) ? ws[s] : -1;
    }
};

int main() {
    Solution sol;

    int n = 6;
    vector<vector<int>> edges = {{0,1,5},{1,2,3},{3,4,4},{4,5,1},{1,4,2}};
    int source = 0, target = 3;
    int k = 1;

    int ans = sol.minimumThreshold(n, edges, source, target, k);
    println("{}", ans);
}
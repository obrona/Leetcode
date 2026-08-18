#include <bits/stdc++.h>
using namespace std;

// use a bitmask to denote a subtree.
// for each subtree, find the max distance between 2 nodes.
// must reject disconnected subgraphs (i.e >= 2 trees)
struct pair_cmp {
    bool operator()(const pair<int,int>& p1, const pair<int,int>& p2) {
        return p2.second < p1.second;
    }
};

class Solution {
public:
    vector<vector<int>> adj;

    void make_adj(int n, const vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (auto& e : edges) {
            adj[e[0] - 1].push_back(e[1] - 1);
            adj[e[1] - 1].push_back(e[0] - 1);
        }
    }

    tuple<int,int,int> dfs(int v, int p, int bm) {
        int best_dist = 0;
        int best_depth = 0;
        int count = 1;
        multiset<int> top2;

        for (int c : adj[v]) {
            if (c == p || ((bm >> c) & 1) == 0) continue;
            auto [max_dist, max_depth, cnt] = dfs(c, v, bm);

            best_dist = max(best_dist, max_dist);
            best_depth = max(best_depth, 1 + max_depth);
            count += cnt;
            
            top2.emplace(1 + max_depth);
            if (top2.size() > 2) top2.erase(top2.begin());
        }

        if (top2.size() == 2) {
            auto d1 = *top2.begin();
            auto d2 = *next(top2.begin());
            best_dist = max(best_dist, d1 + d2);
        }
        
        best_dist = max(best_dist, best_depth);

        return {best_dist, best_depth, count};
    }

    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        auto out = vector(n - 1, 0);
        make_adj(n, edges);
        for (int bm = 1; bm < (1 << n); bm++) {
            int v = countr_zero((unsigned int) bm);
            auto [max_dist, max_depth, count] = dfs(v, v, bm);
            if (max_dist == 0 || count != popcount((unsigned int) bm)) continue;
            out[max_dist - 1]++;
        }
        return out;
    }
};

int main() {
    Solution sol;
    int n = 4;
    vector<vector<int>> edges = {{1,2},{2,3},{2,4}};
    auto out = sol.countSubgraphsForEachDiameter(n, edges);
    for (int x : out) {
        cout << x << " ";
    }
    cout << endl;
}
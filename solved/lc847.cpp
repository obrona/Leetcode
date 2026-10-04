#include <bits/stdc++.h>
using namespace std;

// bitmask dp.
// dp(bitset, node) = shortest path to touch all nodes in bitset and ending at node.
// need all pairs shortest path too.

vector<vector<int>> floyd_warshall(int n , const vector<vector<int>>& edges) {
    vector<vector<int>> curr(n, vector(n, 999));
    for (int i = 0; i < n; i++) {
        curr[i][i] = 0;
        for (int x : edges[i]) {
            curr[i][x] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                curr[j][k] = min(curr[j][k], curr[j][i] + curr[i][k]);
            }
        }
    }

    return curr;
}

class Solution {
public:
    vector<vector<int>> store;
    vector<vector<int>> apsp;

    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        auto apsp = floyd_warshall(n, graph);
        vector<vector<int>> store(1 << n, vector(n, 0));

        for (unsigned int bm = 1; bm < (1 << n); bm++) {
            for (auto m = bm; m; m &= m - 1) {
                int i = countr_zero(m);
                int best = 999999;
                int prev_bm = bm - (1 << i);

                if (popcount(bm) == 1) {
                    best = 0;
                    goto end;
                }

                for (auto p = prev_bm; p; p &= p - 1) {
                    int pi = countr_zero((unsigned int) p);
                    best = min(best, store[prev_bm][pi] + apsp[pi][i]);
                }

                end:
                store[bm][i] = best;
            }
        }

        return *min_element(store.back().begin(), store.back().end());
    }
};

int main() {
    Solution sol;

    vector<vector<int>> graph = {{1,2,3}, {0}, {0}, {0}};

    int ans = sol.shortestPathLength(graph);
    cout << ans << endl;
}
#include <bits/stdc++.h>
using namespace std;

// 1st find if graph has a cycle.
// if no cycle, graph is a dag, for each color, if correct color, node val is 1 else 0.
// becomes finding largest path sum, is just dp.

vector<vector<int>> get_adj_list(int n, const vector<vector<int>>& edges) {
    auto adj = vector<vector<int>>(n, vector<int>());
    for (auto e : edges) {
        adj[e[0]].push_back(e[1]);
    }
    return adj;
}

// return true if there is a cycle else false.
bool check_for_cycle(int n, const vector<vector<int>>& adj) {
    auto first = vector<bool>(n, false);
    auto second = vector<bool>(n, false);

    function<bool(int)> dfs = [&] (int u) -> bool {
        if (first[u] && !second[u]) return true;
        if (second[u]) return false;

        first[u] = true;
        for (int v : adj[u]) {
            if (second[v]) continue;
            if (dfs(v)) return true;
        }

        second[u] = true;
        return false;
    };
    
    for (int i = 0; i < n; i++) {
        if (second[i]) continue;
        if (dfs(i)) return true;
    }
    return false;
}

int largest_path_sum(int n, char c, string colors, const vector<vector<int>>& adj) {
    vector<int> sums(n, -1);

    function<int(int)> dfs = [&] (int u) -> int {
        if (sums[u] != -1) return sums[u];
        
        int best_child = 0;
        for (int v : adj[u]) {
            best_child = max(best_child, dfs(v));
        }

        return sums[u] = (colors[u] == c) + best_child;
    };

    int best = 0;
    for (int i = 0; i < n; i++) {
        best = max(best, dfs(i));
    }

    return best;
}

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        auto adj = get_adj_list(n, edges);
        
        if (check_for_cycle(n, adj)) return -1;

        unordered_set<char> my_colors(colors.begin(), colors.end());
        int best = 0;
        for (char c : my_colors) {
            best = max(best, largest_path_sum(n, c, colors, adj));
        }

        return best;
    }
};

int main() {
    Solution sol;

    string colors = "abaca";
    vector<vector<int>> edges = {{0,1}, {0,2}, {2,3}, {3,4}};

    int ans = sol.largestPathValue(colors, edges);
    cout << ans << endl;
}
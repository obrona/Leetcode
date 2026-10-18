#include <bits/stdc++.h>
#include <ranges>
using namespace std;

// double dfs style.
// just that the logic is so convoluted.
// notice the 3 allowed cycles 
// R B W R B W
// B W R B W R
// W R B W R B
// they are all part of the same cycle just starting at different points.

class Solution {
public:
    string colors;
    vector<vector<int>> adj;

    // dfs with 0 as the root.
    // dfs1_store[v] stores {num of invalid child, num of valid child} when v is the (sub)root.
    // i.e the color of the parent node does not matter.
    vector<array<int,2>> dfs1_store;

    vector<bool> dfs2_res;
    vector<array<int,2>> dfs2_store;
    

    char next_color(char c) {
        switch (c) {
            case 'R':
                return 'B';
            case 'B':
                return 'W';
            case 'W':
                return 'R';
            default:
                return 'A';
        }
    }

    int color_to_int(char c) {
        switch (c) {
            case 'R':
                return 0;
            case 'B':
                return 1;
            case 'W':
                return 2;
            default:
                return -1;
        }
    }

    vector<vector<int>> get_adj(const vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> out(n, vector<int>());

        for(const auto& e : edges) {
            out[e[0]].push_back(e[1]);
            out[e[1]].push_back(e[0]);
        }
        return out;
    }

    
    bool dfs1(int v, int p) {
        char my_color = colors[v];
        char expected_color = next_color(my_color);
        int num_children = adj[v].size() - (v != p);

        auto& my_store = dfs1_store[v];

        for (int c : adj[v]) {
            if (c == p) continue;

            bool r = dfs1(c, v);
            if (r && colors[c] == expected_color) {
                my_store[1]++;
            } else {
                my_store[0]++;
            }
        }

        return my_store[0] == 0 && num_children <= 2;
    }

    void dfs2(int v, int p) {
        if (v == p) {
            dfs2_store[v] = dfs1_store[v];
            dfs2_res[v] = dfs2_store[v][0] == 0 && adj[v].size() <= 2;

            for (int c : adj[v]) {
                dfs2(c, v);
            }
        } 
        
        else {
            // check whether I satisfy the requirements when I was a child of p.
            bool satisfy = colors[v] == next_color(colors[p]) 
                && (adj[v].size() - 1 <= 2)
                && (dfs1_store[v][0] == 0);
            
            // invariant: dfs2_store[p] stores the {num of invalid child, num of valid child}
            // when p is the root.
            auto pres = dfs2_store[p];
            pres[int(satisfy)]--;

            // now check whether p satisfy the requirements if it is a child of v.
            bool p_satisfy = colors[p] == next_color(colors[v])
                && (adj[p].size() - 1 <= 2)
                && (pres[0] == 0);

            dfs2_store[v] = dfs1_store[v];
            dfs2_store[v][p_satisfy]++;

            dfs2_res[v] = dfs2_store[v][0] == 0 && adj[v].size() <= 2;

            for (int c : adj[v]) {
                if (c == p) continue;
                dfs2(c, v);
            }
        }
    }

    


    int findColoredRoot(vector<vector<int>>& edges, string colors) {
        int n = edges.size() + 1;

        this->colors = colors;
        adj = get_adj(edges);

        dfs1_store = vector<array<int, 2>>(n, {0, 0});

        dfs2_res = vector(n, false);
        dfs2_store = dfs1_store;

        dfs1(0, 0);
        dfs2(0, 0);

        for (int i : views::iota(0, n)) {
            if (dfs2_res[i]) return i;
        }

        return -1;

    }
};

int main() {
    Solution sol;

    vector<vector<int>> edges = {{3,1}, {3,2}, {1,4}, {2,0}};
    string colors = "BRRWB";

    int ans = sol.findColoredRoot(edges, colors);
    cout << ans << endl;
}
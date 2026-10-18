#include <bits/stdc++.h>
using namespace std;

// just bookwork.

class Solution {
public:
    vector<int> lastVisitedCell(vector<vector<char>>& grid) {
        int R = grid.size();
        int C = grid[0].size();
        vector<vector<bool>> visited(R, vector(C, false));

        auto is_in_grid = [R, C] (int r, int c) {
            return r >= 0 && r < R && c >= 0 && c < C;
        };

        unordered_map<char, pair<int,int>> dirs = {
            {'L', {0, -1}},
            {'R', {0, 1}},
            {'U', {-1, 0}},
            {'D', {1, 0}}
        };

        visited[0][0] = true;
        int cr = 0;
        int cc = 0;

        while (1) {
            char dir = grid[cr][cc];
            auto [dr, dc] = dirs[dir];

            int nr = cr + dr;
            int nc = cc + dc;

            if (!is_in_grid(nr, nc) || visited[nr][nc]) {
                return {cr, cc};
            }

            visited[nr][nc] = 1;
            cr = nr;
            cc= nc;
        }

        return {-1, -1};
    }
};

int main() {
    Solution sol;

    vector<vector<char>> grid = {{'R', 'D'}, {'U', 'L'}};

    auto ans = sol.lastVisitedCell(grid);
    for (int x : ans) cout << x << " ";
    cout << endl;
}
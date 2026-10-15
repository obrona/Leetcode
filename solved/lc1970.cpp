#include <bits/stdc++.h>
using namespace std;

// binary search the day.
// let say day = d. 
// then cells with value <= d are blocked at this stage.

bool can_cross(int row, int col, const vector<vector<int>>& block, int day) {
    static vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    auto valid = [row, col] (int r, int c) {
        return r >= 0 && r < row && c >= 0 && c < col;
    };

    vector<vector<bool>> visited(row, vector(col, false));

    function<bool(int, int)> dfs = [&] (int r, int c) {
        visited[r][c] = true;
        if (r == row - 1) return true;

        for (auto [dx, dy] : dirs) {
            int nr = r + dx, nc = c + dy;
            if (!valid(nr, nc) || visited[nr][nc] || block[nr][nc] <= day) continue;
            bool ans = dfs(nr, nc);
            if (ans) return true;
        }

        return false;
    };

    
    for (int c = 0; c < col; c++) {
        if (visited[0][c] || block[0][c] <= day) continue;
        if (dfs(0, c)) return true;
    }
    return false;
}

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        vector<vector<int>> block(row, vector(col, 0));
        for (int i = 0; i < cells.size(); i++) {
            auto& c = cells[i];
            block[c[0] - 1][c[1] - 1] = i + 1;
        }

        int s = 0; int e = cells.size();
        while (s < e) {
            int m = (s + e + 1) >> 1;
            bool res = can_cross(row, col, block, m);
            if (res) {
                s = m;
            } else {
                e = m - 1;
            }
        }

        return s;
    }
};

int main() {
    Solution sol;
    int row = 2, col = 2;
    vector<vector<int>> cells = {{1,1},{1,2},{2,1},{2,2}};

    int ans = sol.latestDayToCross(row, col, cells);
    cout << ans << endl;
}
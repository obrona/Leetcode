#include <bits/stdc++.h>
using namespace std;

// state is (r, c, bitmask of keys obtained).
// then use bfs until we reach the state of getting all keys.

class Solution {
public:
    vector<pair<int,int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    
    int key_idx(char c) {
        return c - 'a';
    }

    int lock_idx(char c) {
        return c - 'A';
    }

    int how_many_keys(vector<string>& grid) {
        int cnt = 0;
        for (auto& s : grid) {
            for (char c : s) {
                if (islower(c)) cnt++;
            }
        }
        return cnt;
    }

    pair<int,int> get_start_pos(const vector<string>& grid) {
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[r].size(); c++) {
                if (grid[r][c] == '@') return {r, c};
            }
        }
        return {-1, -1};
    }

    int shortestPathAllKeys(vector<string>& grid) {
        int R = grid.size();
        int C = grid[0].size();
        int num_of_keys = how_many_keys(grid);
        int BM = 1 << num_of_keys;
        auto [start_r, start_c] = get_start_pos(grid);
        
        vector<int> store(R * C * BM, -1);
        
        auto state_to_pos = [&] (int r, int c, int bm) {
            return r * C * BM + c * BM + bm;
        };

        auto is_valid_pos = [&] (int r, int c) {
            return r >= 0 && r < R && c >= 0 && c < C;
        };

        auto is_wall = [&] (int r, int c) {
            return grid[r][c] == '#';
        };

        auto is_key = [&] (int r, int c) {
            return islower(grid[r][c]);
        };

        auto is_lock = [&] (int r, int c) {
            return isupper(grid[r][c]);
        };



        int wave = 0;
        deque<tuple<int,int,int>> q;
        q.emplace_back(start_r, start_c, 0);

        while (!q.empty()) {
            for (int len = q.size(); len > 0; len--) {
                auto [r, c, bm] = q.front(); q.pop_front();
                int pos = state_to_pos(r, c, bm);
                
                if (store[pos] != -1) continue;
                store[pos] = wave;

                if (bm == BM - 1) return wave;

                for (auto [dr, dc] : dirs) {
                    int nr = r + dr, nc = c + dc;
                    if (!is_valid_pos(nr, nc) || is_wall(nr, nc)) continue;

                    if (is_lock(nr, nc)) {
                        int lbm = (1 << lock_idx(grid[nr][nc]));
                        if ((bm & lbm) == 0) continue;
                    }
                    
                    int nbm = bm;
                    if (is_key(nr, nc)) {
                        nbm = nbm | (1 << key_idx(grid[nr][nc]));
                    }

                    q.emplace_back(nr, nc, nbm);
                }
            }
            wave++;
        }

        return -1;
    }
};

int main() {
    Solution sol;
    vector<string> grid = {"@..aA","..B#.","....b"};
    int ans = sol.shortestPathAllKeys(grid);
    println("Ans {}", ans);
}
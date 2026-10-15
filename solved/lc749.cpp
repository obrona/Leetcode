#include <bits/stdc++.h>
using namespace std;

// for each step.
// for each connected component, find the perimeter and the num of uninfected cells that are going to be infected.
// for the component threatening the most number of uninfected cells, add the perimeter to the count,
// and mark cells for this component as disinfected.

// -1: disinfected
// 0: uninfected
// 1: infected

vector<pair<int,int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool valid(int R, int C, int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

pair<int,int> dfs(int r, int c, int label, 
    vector<vector<int>>& infected, 
    vector<vector<bool>>& visited,
    vector<vector<int>>& grid
) 
{
    int R = infected.size(), C = infected[0].size();
    visited[r][c] = true;
    infected[r][c] = label;

    int perimeter = 0;
    int to_infect = 0;
    for (auto [dx, dy] : dirs) {
        int nx = r + dx, ny = c + dy;

        // not valid cell, don't need to add to perimeter or to_infect.
        if (!valid(R, C, nx, ny)) continue;

        if (infected[nx][ny] == 0) {
            perimeter++;
            if (grid[nx][ny] != label) {
                to_infect++;
                grid[nx][ny] = label;
            }
        }

        if (!visited[nx][ny] && infected[nx][ny] >= 1) {
            auto [pp, ii] = dfs(nx, ny, label, infected, visited, grid);
            perimeter += pp;
            to_infect += ii;
        }
    }

    return {perimeter, to_infect};
}

// return the {num of conncted component > 1, perimeter of the connected component covered}.
// infected cells are cells whose value are >= 1.
pair<bool, int> step(vector<vector<int>>& infected) {
    int R = infected.size();
    int C = infected[0].size();

    int init = 2;
    int label = 2;
    vector<pair<int,int>> res;
    vector<vector<bool>> visited(R, vector(C, false));
    vector<vector<int>> grid(R, vector(C, 0));


    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (infected[r][c] <= 0 || visited[r][c]) continue;
            
            auto p = dfs(r, c, label, infected, visited, grid);
            res.push_back(p);
        
            label++;
        }
    }

    // edge case: we cannot find any infected connected components at all.
    if (res.size() == 0) return {false, 0};

    int arg_max = max_element(res.begin(), res.end(), [] (const auto& p1, const auto& p2) { return p1.second < p2.second; }) - res.begin();
    int label_chosen = arg_max + init;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (infected[r][c] == label_chosen) {
                infected[r][c] = -1;
            }
        }
    }

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            // remeber the newly infectec cells have value 1.
            // do not continue to spread.
            if (infected[r][c] <= 1) continue;

            for (auto [dx, dy] : dirs) {
                int nx = r + dx, ny = c + dy;
                if (nx >= 0 && nx < R && ny >= 0 && ny < C && infected[nx][ny] == 0) {
                    infected[nx][ny] = 1;
                }
            }
        }
    }


    return {res.size() > 1, res[arg_max].first};
}

class Solution {
public:
    int containVirus(vector<vector<int>>& isInfected) {
        int cnt = 0;
        while (1) {
            auto [to_continue, pp] = step(isInfected);
            cnt += pp;
            if (!to_continue) break;
        }
        return cnt;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> isInfected = {{0,1,0,0,0,0,0,1}, {0,1,0,0,0,0,0,1}, {0,0,0,0,0,0,0,1}, {0,0,0,0,0,0,0,0}};

    int ans = sol.containVirus(isInfected);
    cout << ans << endl;
}
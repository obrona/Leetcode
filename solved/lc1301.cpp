#include <vector>
#include <print>
#include <array>
#include <optional>
using namespace std;

// classic dp on DAG.
// dp(r, c) = [max score, num of ways with max score, can reach].
// suppose at r, c you cannot reach e, then the result should be [0, 0].

class Solution {
public:
    int R, C;
    vector<string> board;
    vector<vector<optional<array<int,3>>>> store;
    vector<array<int,2>> dirs = {{-1, 0}, {-1, -1}, {0, -1}};

    bool is_valid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    int score(int r, int c) {
        return isdigit(board[r][c]) ? board[r][c] - '0' : 0;
    }

    array<int,3> dp(int r, int c) {
        auto& ans = store[r][c];
        if (ans) return ans.value();

        if (r == 0 && c == 0) {
            ans = {0, 1, 1};
            return ans.value();
        }

        int best = 0;
        bool can_reach = false;
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (!is_valid(nr, nc) || board[nr][nc] == 'X') continue;

            auto [s, w, b] = dp(nr, nc);
            if (b) {
                can_reach = true;
                best = max(best, score(r, c) + s);
            }
            
        }

        int ways = 0;
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (!is_valid(nr, nc) || board[nr][nc] == 'X') continue;

            auto [s, w, b] = dp(nr, nc);
            if (s + score(r, c) == best) {
                ways += w;
                ways %= int(1e9 + 7);
            }
        }

        ans = {best, ways, can_reach};
        return ans.value();
    }

    vector<int> pathsWithMaxScore(vector<string>& board) {
        R = board.size();
        C = board[0].size();
        this->board = std::move(board);
        store = vector(R, vector<optional<array<int,3>>>(C, nullopt));
        
        auto [s, w, b] = dp(R - 1, C - 1);
        return {s, w};
    }
};

int main() {
    Solution sol;
    vector<string> board = {"E23","2X2","12S"};
    
    auto ans = sol.pathsWithMaxScore(board);
    println("{} {}", ans[0], ans[1]);
}
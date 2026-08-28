#include <bits/stdc++.h>
using namespace std;

// (r, c) maps to (c, N - 1 - r).
// we process layer by layer, like peeling an onion.
// for odd * odd, eg 5 * 5, we do layer 0 = 5 * 5, layer 1 = 3 * 3, layer 2 = 1 * 1
// for even * even, eg 4 * 4 we do layer 0 = 4 * 4, layer 1 = 2 * 2.
// for each layer we do the cycle mapping so (r, c) -> (r1, c1) -> (r2, c2).
// length of each cycle is 4, so on the 5th iteration we stop.
// for each layer we do this for len - 1 times.
// do it manually yourself to see the pattern.

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int N = matrix.size();

        auto map = [N] (int r, int c) {
            return array<int,2>{c, N - 1 - r};
        };

        for (int l = 0; l < N / 2; l++) {
            for (int i = 0; i < N - 2 * l - 1; i++) {
                int r = l, c = l + i;
                int temp = matrix[r][c];
                for (int cycle = 0; cycle < 4; cycle++) {
                    auto [rn, cn] = map(r, c);
                    swap(matrix[rn][cn], temp);
                    r = rn;
                    c = cn;
                }
            }
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    sol.rotate(matrix);
    for (auto v : matrix) {
        for (auto x : v) cout << x << " ";
        cout << endl;
    }
}
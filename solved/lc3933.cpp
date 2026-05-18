#include <bits/stdc++.h>
using namespace std;

// have to use 2d segtree
// sort the numbers, group equal numbers together
// process from largest to smallest.
// when processing val of x at pos (r, c) check in the rectangle for how many numbers
// then subtract the 4 corner, if > 0 then is not the maximum

// no need to build
// range sum point add
// x coor is the row, y coor is the col
// (0, 0) is the top left
struct SegTree {
    int R, C;
    vector<vector<int>> tree;

    SegTree(int R, int C): R(R), C(C), tree(4 * R, vector<int>(4 * C, 0)) {}

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    int range_query_y(int px, int py, int ly, int ry, int sy, int ey) {
        if (sy == ly && ry == ey) return tree[px][py];
        
        int my = mid(sy, ey);
        if (ry <= my) {
            return range_query_y(px, left(py), ly, ry, sy, my);
        } else if (ly > my) {
            return range_query_y(px, right(py), ly, ry, my + 1, ey);
        } else {
            int lres = range_query_y(px, left(py), ly, my, sy, my);
            int rres = range_query_y(px, right(py), my + 1, ry, my + 1, ey);
            return lres + rres;
        }
    }

    int range_query_x(int px, int lx, int rx, int ly, int ry, int sx, int ex) {
        if (lx == sx && rx == ex) return range_query_y(px, 0, ly, ry, 0, C - 1);
        
        int mx = mid(sx, ex);
        if (rx <= mx) {
            return range_query_x(left(px), lx, rx, ly, ry, sx, mx);
        } else if (lx > mx) {
            return range_query_x(right(px), lx, rx, ly, ry, mx + 1, ex);
        } else {
            int lres = range_query_x(left(px), lx, mx, ly, ry, sx, mx);
            int rres = range_query_x(right(px), mx + 1, rx, ly, ry, mx + 1, ex);
            return lres + rres;
        }
    }

    int query(int lx, int rx, int ly, int ry) {
        return range_query_x(0, lx, rx, ly, ry, 0, R - 1);
    }

    void update_y(int px, int py, int i, int v, int sy, int ey) {
        if (sy == ey) {
            tree[px][py] += v;
            return;
        }

        int my = mid(sy, ey);
        if (i <= my) {
            update_y(px, left(py), i, v, sy, my);
        } else {
            update_y(px, right(py), i, v, my + 1, ey);
        }
        tree[px][py] = tree[px][left(py)] + tree[px][right(py)];
    }

    void merge_update(int px, int py, int c, int sy, int ey) {
        tree[px][py] = tree[left(px)][py] + tree[right(px)][py];
        if (sy == ey) return;
        
        int my = mid(sy, ey);
        if (c <= my) merge_update(px, left(py), c, sy, my);
        else merge_update(px, right(py), c, my + 1, ey);
    }

    void update_x(int px, int r, int c, int v, int sx, int ex) {
        if (sx == ex) {
            update_y(px, 0, c, v, 0, C - 1);
            return;
        }
        int mx = mid(sx, ex);
        if (r <= mx) {
            update_x(left(px), r, c, v, sx, mx);
        } else {
            update_x(right(px), r, c, v, mx + 1, ex);
        }
        merge_update(px, 0, c, 0, C - 1);
    }

    void update(int r, int c, int v) {
        update_x(0, r, c, v, 0, R - 1);
    }
    
};

class Solution {
public:
    int countLocalMaximums(vector<vector<int>>& matrix) {
        int R = matrix.size(), C = matrix[0].size();
        
        vector<tuple<int,int,int>> store;
        for (auto [r, c] : views::cartesian_product(views::iota(0, R), views::iota(0, C))) {
            store.emplace_back(matrix[r][c], r, c);
        }
        sort(store.begin(), store.end(), [] (auto t1, auto t2) { return get<0>(t1) > get<0>(t2); });

        SegTree st(R, C);

        auto valid = [R, C] (int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; };

        vector<pair<int,int>> dirs = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

        int ans = 0;

        vector<pair<int,int>> wave;
        int val = -1;
        for (auto [v, r, c] : store) {
            if (v != val) {
                val = v;
                for (auto [x, y] : wave) st.update(x, y, 1);
                wave.clear();
            }

            if (v != 0) {
                int tx = max(0, r - v), ty = max(0, c - v);
                int bx = min(R - 1, r + v), by = min(C - 1, c + v);
                int cnt = st.query(tx, bx, ty, by);

                // then minus 4 corners
                for (auto [dx, dy] : dirs) {
                    int x = r + dx * v, y = c + dy * v;
                    if (!valid(x, y)) continue;
                    if (matrix[x][y] > v) cnt--;
                }

                if (cnt == 0) ans++;
            }
            

            wave.emplace_back(r, c);
        }

        return ans;
    }
};

void test_2d_segtree() {
    SegTree st(4, 5);

    // grid:
    // 0 0 0 0 0
    // 0 0 0 0 0
    // 0 0 0 0 0
    // 0 0 0 0 0

    st.update(0, 0, 5);
    st.update(1, 2, 3);
    st.update(3, 4, 7);
    st.update(2, 1, 6);

    // grid:
    // 5 0 0 0 0
    // 0 0 3 0 0
    // 0 6 0 0 0
    // 0 0 0 0 7

    assert(st.query(0, 0, 0, 0) == 5);

    // whole grid
    assert(st.query(0, 3, 0, 4) == 21);

    // rectangle containing (1,2) and (2,1)
    assert(st.query(1, 2, 1, 2) == 9);

    // bottom-right corner
    assert(st.query(3, 3, 4, 4) == 7);

    // single empty cell
    assert(st.query(0, 0, 1, 1) == 0);

    // partial row
    assert(st.query(0, 1, 0, 2) == 8);

    // update existing cell
    st.update(1, 2, 4);

    // (1,2) becomes 7
    assert(st.query(1, 1, 2, 2) == 7);

    // total becomes 25
    assert(st.query(0, 3, 0, 4) == 25);

    // negative update
    st.update(0, 0, -2);

    // (0,0) becomes 3
    assert(st.query(0, 0, 0, 0) == 3);

    // total becomes 23
    assert(st.query(0, 3, 0, 4) == 23);

    cout << "All 2D segtree tests passed!\n";
}

int main() {
    //test_2d_segtree();
    
    Solution sol;
    vector<vector<int>> matrix = {{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,2,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
    int ans = sol.countLocalMaximums(matrix);
    println("{}", ans);
}
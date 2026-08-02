#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// use a segment tree to get the bonus at index i.
// work backwards to find the minimum energy.
// suppose minimum energy need to kill monsters[i+1:] is e
// if e = 0 this is the only special case, e = max(0, monsters[i] - bonus[i])
// else e += m, no matter the bonus as we subtract monsters[i] from e.

struct segtree {
    int len;
    vector<ll> tree;

    segtree(int len): len(len), tree(4 * len, 0) {}

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    void range_update(int l, int r, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == l && e == r) {
            tree[p] += v;
            return;
        }
        int m = mid(s, e);
        if (r <= m) {
            range_update(l, r, v, left(p), s, m);
        } else if (l > m) {
            range_update(l, r, v, right(p), m + 1, e);
        } else {
            range_update(l, m, v, left(p), s, m);
            range_update(m + 1, r, v, right(p), m + 1, e);
        }
    }

    ll point_query(int i, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) return tree[p];
        int m = mid(s, e);
        return tree[p] + (i <= m ? point_query(i, left(p), s, m) : point_query(i, right(p), m + 1, e));   
    }
};

class Solution {
public:
    long long minInitialStrength(vector<int>& monsters, vector<vector<int>>& boosts) {
        segtree st(monsters.size());
        for (auto& b : boosts) {
            st.range_update(b[0], b[1], b[2]);
        }

        ll energy = 0;
        for (int i = monsters.size() - 1; i > -1; i--) {
            ll m =  monsters[i];
            ll bonus = st.point_query(i);

            if (energy == 0) {
                energy = max(0LL, m - bonus);
            } else {
                energy += m;
            }
        }
        return energy;
    }
};

int main() {
    Solution sol;
    vector<int> monsters = {5, 10, 15};
    vector<vector<int>> boosts = {{1,2,10},{1,2,15}};

    ll ans = sol.minInitialStrength(monsters, boosts);
    cout << ans << endl;
}
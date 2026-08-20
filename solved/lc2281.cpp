#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

// need segment tree that supports adding an arithmetic series.
// i.e for [l, r] add a, a + b, a + 2b ... a * (r - l)b.
// we start from the smallest element at index i.
// we get the left and right endpoint.
// these are the leftmost and rightmost index that can occur.
// let a = i - l + 1, b = r - i + 1
// index i mult factor is xab, index i + 1 is xa(b-1), index i + 2 is xa(b + 2) ...
// index i - 1 is x(a-1)b, index i - 2 is x(a - 2)b ...
// the trick here is to store, at each tree node {start, step}
// then len is implicit from [start, end]
// we push down when we touch that node to its left and right children, see the methods for the details.

int norm(long long x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return static_cast<int>(x);
}

int add(int a, int b) {
    return norm(static_cast<long long>(a) + b);
}

int mult(int a, int b) {
    return norm(static_cast<long long>(a) * b);
}

int left(int p) {
    return (p << 1) + 1;
}

int right(int p) {
    return (p << 1) + 2;
}

int mid(int l, int r) {
    return (l + r) >> 1;
}

struct store {
    int start = 0;
    int step = 0;

    static void merge_to(store& receiver, store other) {
        receiver.start = add(receiver.start, other.start);
        receiver.step = add(receiver.step, other.step);
    }

    static void push_down(store& parent, store& left, store& right, int s, int e) {
        if (s == e) return;
        if (parent.start == 0 && parent.step == 0) return;

        merge_to(left, {.start = parent.start, .step = parent.step});
        
        int m = mid(s, e);
        int right_start = add(parent.start, mult(parent.step, m - s + 1));
        merge_to(right, {.start = right_start, .step = parent.step});

        parent = {0, 0};
    }
};

struct segtree {
    int len;
    vector<store> tree;

    segtree(int len): len(len), tree(4 * len, store{}) {}

    void range_update(int l, int r, int start, int step, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        store::push_down(tree[p], tree[left(p)], tree[right(p)], s, e);

        if (s == l && e == r) {
            store::merge_to(tree[p], {start, step});
            return;
        }

        int m = mid(s, e);
        if (r <= m) {
            range_update(l, r, start, step, left(p), s, m);
        } else if (l > m) {
            range_update(l, r, start, step, right(p), m + 1, e);
        } else {
            range_update(l, m, start, step, left(p), s, m);

            int right_start = add(start, mult(step, m - l + 1));
            range_update(m + 1, r, right_start, step, right(p), m + 1, e);
        }
    }

    int point_query(int i, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        store::push_down(tree[p], tree[left(p)], tree[right(p)], s, e);

        if (s == e) {
            return tree[p].start;
        }
        
        int m = mid(s, e);
        if (i <= m) {
            return point_query(i, left(p), s, m);
        } else {
            return point_query(i, right(p), m + 1, e);
        }
    }
};

class Solution {
public:
    int totalStrength(vector<int>& strength) {
        int len = strength.size();
        vector<pair<int,int>> arr;
        for (int i = 0; i < strength.size(); i++) arr.emplace_back(i, strength[i]);
        sort(arr.begin(), arr.end(), [] (const auto& p1, const auto& p2) {
            if (p1.second != p2.second) return p1.second < p2.second;
            if (p1.first != p2.first) return p1.first < p2.first;
            return false;
        });

        segtree st(len);
        set<int> used_indexes;

        auto get_left_limit = [&used_indexes] (int i) {
            auto it = used_indexes.lower_bound(i);
            if (it == used_indexes.begin()) return -1;
            else return *(prev(it));
        };

        auto get_right_limit = [&used_indexes, len] (int i) -> int {
            auto it = used_indexes.upper_bound(i);
            if (it == used_indexes.end()) return len;
            else return *it;
        };

        for (auto [i, v] : arr) {
            int left_lim = get_left_limit(i);
            int right_lim = get_right_limit(i);

            int a = i - left_lim;
            int b = right_lim - i;
            
            // Positions to the left of i:
            // count = (j - left_lim) * b
            if (left_lim + 1 < i) {
                int start_left = mult(v, b);
                int step_left = mult(v, b);

                st.range_update(
                    left_lim + 1,
                    i - 1,
                    start_left,
                    step_left
                );
            }

            // Position i: a * b subarrays
            st.range_update(i, i, mult(v, mult(a, b)), 0);

            // Positions to the right of i:
            // count = a * (right_lim - j)
            if (i + 1 < right_lim) {
                int start_right = mult(v, mult(a, b - 1));
                int step_right = norm(-1LL * mult(v, a));

                st.range_update(
                    i + 1,
                    right_lim - 1,
                    start_right,
                    step_right
                );
            }

            used_indexes.insert(i);
        }

        int sum = 0;
        for (int i = 0; i < len; i++) {
            int res = st.point_query(i);
            sum = add(sum, mult(strength[i], res));
        }

        return sum;
    
    }
};

int main() {
    Solution sol;
    vector<int> strength = {1,3,1,2};
    int ans = sol.totalStrength(strength);
    cout << ans << endl;
}
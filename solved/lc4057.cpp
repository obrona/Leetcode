#include <bits/stdc++.h>
using namespace std;

// sort in increasing start_idx.
// for interval [start, end], every interval in the segment tree has start_y >= start. 
// just need 1 query sum(start, end)
// then add 1 for index start for this interval.

function<int(int)> compress(const vector<vector<int>>& intervals) {
    vector<int> store;
    store.reserve(2 * intervals.size());

    for (const auto& i : intervals) {
        store.push_back(i[0]);
        store.push_back(i[1]);
    }

    sort(store.begin(), store.end());

    auto res = make_shared<unordered_map<int,int>>();
    int p = -1;
    int prev = -1;
    for (int x : store) {
        if (x == prev) {
            (*res)[x] = p;
        } else {
            (*res)[x] = ++p;
            prev = x;
        }
    }

    return [res] (int x) {
        auto it = res->find(x);
        if (it == res->end()) return -1;
        return it->second;
    };
}

struct segtree {
    int len;
    vector<int> tree;

    segtree(int len): len(len), tree(4 * len, 0) {}

    int mid(int s, int e) {
        return s + ((e - s) >> 1);
    }

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    void update(int idx, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == e) {
            tree[p]++;
            return;
        }

        int m = mid(s, e);
        tree[p]++;
        if (idx <= m) {
            update(idx, left(p), s, m);
        } else {
            update(idx, right(p), m + 1, e);
        }
    }

    int query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == l && e == r) {
            return tree[p];
        }

        int m = mid(s, e);
        if (r <= m) {
            return query(l, r, left(p), s, m);
        } else if (l > m) {
            return query(l, r, right(p), m + 1, e);
        } else {
            return query(l, m, left(p), s, m) + query(m + 1, r, right(p), m + 1, e);
        }
    }
};

class Solution {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        auto compress_func = compress(intervals);
        segtree st(2 * intervals.size());
        
        sort(intervals.begin(), intervals.end(), [] (auto& i1, auto& i2) { return i1[0] < i2[0]; });

        long long cnt = 0;
        for (int i = intervals.size() - 1; i >= 0; i--) {
            auto& it = intervals[i];
            int l = compress_func(it[0]), r = compress_func(it[1]);
            cnt += st.query(l, r);
            st.update(l);
        }

        return cnt;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> intervals = {{1,2}, {2,3}, {3,4}};

    long long ans = sol.countIntersectingIntervals(intervals);
    cout << ans << endl;
}
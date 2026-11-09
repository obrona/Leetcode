#include <bits/stdc++.h>
using namespace std;

// we can use segment tree to query which servers are available.
// for the loop back we split into 2 queries [k:n] and [0:k].
// note that we use python inclusive start exclusive end indexing.

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(int len): len(len), tree(4 * len, 0) {}

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    int update(int i, int val, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == e) return tree[p] = val;
        
        int m = mid(s, e);
        if (i <= m) {
            return tree[p] = min(update(i, val, left(p), s, m), tree[right(p)]);
        } else {
            return tree[p] = min(tree[left(p)], update(i, val, right(p), m + 1, e));
        }
    }

    // returns the smallest index in [l, r] s.t arr[i] <= val
    int query(int l, int r, int val, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (tree[p] > val) return len;

        if (s == e) return s;

        int m = mid(s, e);
        if (r <= m) {
            return query(l, r, val, left(p), s, m);
        } else if (l > m) {
            return query(l, r, val, right(p), m + 1, e);
        } else {
            int lres = query(l, m, val, left(p), s, m);
            if (lres < len) return lres;
            return query(m + 1, r, val, right(p), m + 1, e);
        }
    }
};

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> requests_served(k, 0);
        SegTree st(k);

        for (int i = 0; i < arrival.size(); i++) {
            int server = i % k;
            int s = st.query(server, k - 1, arrival[i]);
            if (s == k && server > 0) s = st.query(0, server - 1, arrival[i]);

            if (s == k) continue;
            requests_served[s] += 1;
            st.update(s, arrival[i] + load[i]);
        }

        int ma = *max_element(requests_served.begin(), requests_served.end());
        vector<int> out;
        for (int i = 0; i < k; i++) {
            if (requests_served[i] == ma) {
                out.push_back(i);
            }
        }

        return out;
    }
};

int main() {
    Solution sol;
    int k = 3;
    vector<int> arrival = {1,2,3,4,5};
    vector<int> load = {5,2,3,3,3};

    auto ans = sol.busiestServers(k, arrival, load);
    for (int x : ans) cout << x << " ";
    cout << endl;
}
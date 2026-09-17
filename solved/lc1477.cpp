#include <bits/stdc++.h>
using namespace std;

// use 2 pointer to get for each index i, len of the shortest (well only) subarray
// starting at i whose sum is target.
// this is only possible because every elem in the array is >= 0.
// after that at index i, get the min length from result[i + len: len(arr)]
// using a segment tree.

vector<int> get_len(const vector<int>& arr, int target) {
    int sum = 0;
    int p = 0;
    vector<int> out(arr.size(), arr.size());

    for (int i = 0; i < arr.size(); i++) {
        if (p < i) {
            p = i;
            sum = 0;
        }

        while (p < arr.size() && sum + arr[p] <= target) {
           sum += arr[p++];
        }

        if (sum == target) {
            out[i] = p - i;
        }

        if (p > i) {
            sum -= arr[i];
        }
    }

    return out;
}

struct segtree {
    int len;
    vector<int> tree;

    segtree(int len): len(len), tree(4 * len, int(1e5) + 1) {}

    segtree(const vector<int> arr): len(arr.size()), tree(4 * len, 0) {
        build(arr);
    }

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    int mid(int s, int e) {
        return s + ((e - s) >> 1);
    }

    void build(const vector<int>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == -1) {
            e = len - 1;
        }

        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = mid(s, e);
        build(arr, left(p), s, m);
        build(arr, right(p), m + 1, e);
        tree[p] = min(tree[left(p)], tree[right(p)]);
    }

    void update(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) {
            e = len - 1;
        }

        if (s == e) {
            tree[p] = v;
            return;
        }

        int m = mid(s, e);
        if (i <= m) {
            update(i, v, left(p), s, m);
        } else {
            update(i, v, right(p), m + 1, e);
        }

        tree[p] = min(tree[left(p)], tree[right(p)]);
    }

    int query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) {
            e = len - 1;
        }

        if (s == l && e == r) {
            return tree[p];
        }

        int m = mid(s, e);
        if (r <= m) {
            return query(l, r, left(p), s, m);
        } else if (l > m) {
            return query(l, r, right(p), m + 1, e);
        } else {
            return min(
                query(l, m, left(p), s, m),
                query(m + 1, r, right(p), m + 1, e)
            );
        }
    }
};

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        auto lens = get_len(arr, target);
        for (int x : lens) cout << x << " ";
        cout << endl;
        segtree st(lens);

        int best = 999999;
        for (int i = 0; i < arr.size(); i++) {
            if (lens[i] == arr.size()) continue;

            int start = i + lens[i];
            if (start >= arr.size()) continue;

            int next_len = st.query(start, arr.size() - 1);
            if (next_len == arr.size()) continue;

            best = min(best, lens[i] + next_len);
        }

        return (best == 999999) ? -1 : best;
    }
};

int main() {
    Solution sol;

    vector<int> arr = {4,3,2,6,2,3,4};
    int target = 6;

    int ans = sol.minSumOfLengths(arr, target);
    cout << ans << endl;

}
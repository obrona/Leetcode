#include <bits/stdc++.h>
using namespace std;

// 2 problems
// 1st problem is to get sliding window AND of size k.
// we can store a frequency map of each bit position.
// or just use a segment tree to get range N.
// both algo time complexity is nlogn

// we get a set S which contains the bitmask of window AND.
// problem is find the minimum size hitting set, i.e x s.t x & y != 0 for all y in S.
// a set x is invalid if it is the subset of ~y for any y in S.
// or x is a subset of another invalid set.
// so get ~y for every y and do sum over supersets.

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(int bitsize, const vector<int>& arr): len(arr.size()), tree(4 * len, (1 << bitsize) - 1) {
        build(0, 0, len - 1, arr);
    }

    int left(int p) { return (p << 1) + 1; }

    int right(int p) { return (p << 1) + 2; }

    int mid(int s, int e) { return s + ((e - s) >> 1); }
    
    int build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) return tree[p] = arr[s];
        int m = mid(s, e);
        return tree[p] = build(left(p), s, m, arr) & build(right(p), m + 1, e, arr);
    }

    int query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == l && e == r) return tree[p];
        int m = mid(s, e);
        if (r <= m) return query(l, r, left(p), s, m);
        if (l > m) return query(l, r, right(p), m + 1, e);
        return query(l, m, left(p), s, m) & query(m + 1, r, right(p), m + 1, e);
    }
};

// here we want the superset so the accumulate condition is different
// i.e accumulate when bit i is 0
int solve(int bitsize, unordered_set<int>& bm_set) {
    vector<int> store(1 << bitsize, 0);
    for (int bm : bm_set) store[(~bm) & ((1 << bitsize) - 1)] = 1;

    for (int i = 0; i < bitsize; i++) {
        for (int bm = 0; bm < (1 << bitsize); bm++) {
            if (!(bm & (1 << i))) {
                store[bm] += store[bm ^ (1 << i)];
            }
        }
    }

    int best = INT_MAX;
    for (size_t bm = 1; bm < (1 << bitsize); bm++) {
        if (store[bm] > 0) continue;
        best = min(best, popcount(bm));
    }
    return best == INT_MAX ? -1 : best;
}


class Solution {
public:
    int minSetBits(vector<int>& nums, int k) {
        int bitsize = 0;
        for (int x : nums) bitsize = max(bitsize, bit_width((size_t) x));

        SegTree st(bitsize, nums);

        unordered_set<int> window_elems;
        for (int i = 0; i < nums.size() - k + 1; i++) window_elems.insert(st.query(i, i + k - 1));

        int ans = solve(bitsize, window_elems);
        return ans;
    }
};

int main() {
    Solution sol;

   vector<int> nums = {1, 1, 1};
    int k = 1;

    int ans = sol.minSetBits(nums, k);
    println("Ans: {}", ans);
}
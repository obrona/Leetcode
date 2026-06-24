#include <bits/stdc++.h>
using namespace std;

// can jump from i to j iff |i - j| <= d and arr[i] is > max(arr[i +/- 1]..arr[j]) 
// depending on left or right dir.

// we find the 1st element to the left/right that is >= arr[i], as that index is the limit.
// we cannot jump beyond that index. 
// use monotonic stack for that.

// we can use segment tree to get range max. We process elements from smallest to largest

// total O(nlogn) but best solution is O(n)

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(int len): len(len), tree(4 * len, 0) {}

    int left(int p) { return (p << 1) + 1; }

    int right(int p) { return (p << 1) + 2; }

    int mid(int s, int e) { return (s + e) >> 1; }

    void point_update(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        
        if (s == e) {
            tree[p] = v;
            return;
        }

        int m = mid(s, e);
        if (i <= m) {
            point_update(i, v, left(p), s, m);
        } else {
            point_update(i, v, right(p), m + 1, e);
        }
        tree[p] = max(tree[left(p)], tree[right(p)]);
    }

    int range_query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == l && e == r) {
            return tree[p];
        }

        int m = mid(s, e);
        if (r <= m) {
            return range_query(l, r, left(p), s, m);
        } else if (l > m) {
            return range_query(l, r, right(p), m + 1, e);
        } else {
            return max(
                range_query(l, m, left(p), s, m),
                range_query(m + 1, r, right(p), m + 1, e)
            );
        }
    }
};

vector<int> find_left_first_geq(const vector<int>& arr) {
    vector<int> out(arr.size(), -1);
    vector<pair<int,int>> stack;
    for (int i = 0; i < arr.size(); i++) {
        int x = arr[i];
        while (!stack.empty() && stack.back().second < x) stack.pop_back();
        out[i] = stack.empty() ? -1 : stack.back().first;
        stack.emplace_back(i, x);
    }
    return out;
}

vector<int> find_right_first_geq(const vector<int>& arr) {
    vector<int> out(arr.size(), -1);
    vector<pair<int,int>> stack;
    for (int i = arr.size() - 1; i > -1; i--) {
        int x = arr[i];
        while (!stack.empty() && stack.back().second < x) stack.pop_back();
        out[i] = stack.empty() ? arr.size() : stack.back().first;
        stack.emplace_back(i, x);
    }
    return out;
}

class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        SegTree st(arr.size());
        auto left_geq = find_left_first_geq(arr);
        auto right_geq = find_right_first_geq(arr);

        vector<pair<int,int>> sorted(arr.size());
        for (int i = 0; i < arr.size(); i++) {
            sorted[i] = {i, arr[i]};
        }
        sort(sorted.begin(), sorted.end(), 
            [] (const pair<int,int>& p1, const pair<int,int>& p2) {
                return p1.second < p2.second;
            }
        );

        for (auto [i, v] : sorted) {
            
            int l = max(i - d, left_geq[i] + 1);
            int r = min(i + d, right_geq[i] - 1);
            println("{} {} {} {}", i, v, l, r);
            int left_best = l == i ? 0 : st.range_query(l, i - 1);
            int right_best = r == i ? 0 : st.range_query(i + 1, r);
            int res = 1 + max(left_best, right_best);
            st.point_update(i, res);
        }

        return st.range_query(0, arr.size() - 1);
    }
};

int main() {
    Solution sol;
    vector<int> arr = {3,3,3,3,3};
    int d = 3;
    int ans = sol.maxJumps(arr, d);
    println("Ans: {}", ans);
}
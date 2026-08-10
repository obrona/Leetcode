#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// maintain a set of indices which are peaks.
// changing arr[i] only affects arr[i - 1], arr[i], arr[i + 1].
// for each subarray, only consider the leftmost peak to avoid double counting.
// suppose in [l, r] the peaks are p1, p2 ... pk.
// the num of subarrays is (p1 - l)(r - p1) + sum((pi - pi-1)(r - pi))
// do some algebra and the final expression is
// -sum(pi^2) - lr + rp_n + lp_1 + sum(p_i * p_i-1)

struct segtree {
    int len;
    vector<ll> tree;

    segtree(int len): len(len), tree(4 * len, 0) {}

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    void point_update(int i, ll v, int p = 0, int s = 0, int e = -1) {
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
        tree[p] = tree[left(p)] + tree[right(p)];
    }

    ll range_query(int l, int r, int p = 0, int s = 0, int e = -1) {
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
            return range_query(l, m, left(p), s, m) + range_query(m + 1, r, right(p), m + 1, e);
        }
    } 
};

struct solver {
    vector<int> arr;
    set<int> peak_indices;
    segtree squares, consecutives;

    bool is_peak(int i) {
        return i > 0 && i < arr.size() - 1 && arr[i] > arr[i - 1] && arr[i] > arr[i + 1];
    }

    solver(const vector<int>& nums): arr(nums), squares(nums.size()), consecutives(nums.size()) {
        for (int i = 1; i < nums.size() - 1; i++) {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
                peak_indices.insert(i);
                squares.point_update(i, (ll) i * i);
            }
        }

        for (auto it = peak_indices.begin(); it != peak_indices.end(); it++) {
            if (it == peak_indices.begin()) continue;
            consecutives.point_update(*it, (ll) (*it) * (*prev(it)));
        }
    }

    // only call this if arr[i] is actually a peak.
    // arr[i] already has the new value.
    void add_peak(int i) {
        auto prev_it = peak_indices.lower_bound(i);
        if (prev_it != peak_indices.begin()) {
            prev_it--;
            int prev_peak_idx = *prev_it;
            consecutives.point_update(i, (ll) i * prev_peak_idx);
        }

        auto next_it = peak_indices.upper_bound(i);
        if (next_it != peak_indices.end()) {
            consecutives.point_update(*next_it, (ll) (*next_it) * i);
        }

        peak_indices.insert(i);
        squares.point_update(i, (ll) i * i);
    }

    void remove_peak(int i) {
        if (!peak_indices.contains(i)) return;

        peak_indices.erase(i);
        squares.point_update(i, 0);
        consecutives.point_update(i, 0);

        auto next_it = peak_indices.upper_bound(i);
        if (next_it == peak_indices.end()) return; // no need to do anything as there is no peak indices to the right.
        if (next_it == peak_indices.begin()) {
            consecutives.point_update(*next_it, 0);
            return;
        }

        auto prev_it = peak_indices.lower_bound(i);
        if (prev_it != peak_indices.begin()) {
            prev_it--;
            consecutives.point_update(*next_it, 1LL * (*next_it) * (*prev_it));
        }
    }

    ll query(int l, int r) {
        auto left_it = peak_indices.upper_bound(l);
        if (left_it == peak_indices.end()) return 0;

        auto right_it = peak_indices.lower_bound(r);
        if (right_it == peak_indices.begin()) return 0;
        if (left_it == right_it) return 0;
        right_it--;
        
        int left_peak = *left_it;
        int right_peak = *right_it;

        ll square_sum = squares.range_query(left_peak, right_peak);
        ll consecutive_sum = (left_peak == right_peak) ? 0 : consecutives.range_query(left_peak + 1, right_peak);
        ll rest = 1LL * -l * r 
                + 1LL * r * right_peak 
                + 1LL * l * left_peak;

        return consecutive_sum + rest - square_sum;
    }

    void update(int i, int v) {
        for (int j : {i - 1, i, i + 1}) remove_peak(j);
        
        arr[i] = v;
        for (int j : {i - 1, i, i + 1}) {
            if (is_peak(j)) add_peak(j);
        }
    }


};

class Solution {
public:
    vector<long long> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        solver sol(nums);
        vector<ll> out;

        for (auto& q : queries) {
            if (q[0] == 1) {
                out.push_back(sol.query(q[1], q[2]));
            } else {
                sol.update(q[1], q[2]);
            }
        }

        return out;
    }
};
#include <bits/stdc++.h>
using namespace std;

// Solution description
// --------------------
// Idea: count every consistent subarray exactly once, at the index of its
// leftmost minimum.
//
// Fix index i with x = nums[i], and count subarrays [l..r] (l <= i <= r) where
//   (1) nums[i] is the leftmost minimum of [l..r], and
//   (2) AND(nums[l..r]) == x.
//
// Condition (1) -- monotonic stacks:
//   - left_lteq[i]: 1st index to the left with value <= x (or -1).
//     Using <= on the left means no element equal to x lies left of i, so i
//     is the *leftmost* minimum and ties are not double counted.
//   - right_lt[i]: 1st index to the right with value < x (or n).
//     Equal values are allowed on the right.
//
// Condition (2) -- segment tree of ANDs:
//   The AND of any range containing i is a submask of x, so AND == x iff
//   every element of the range contains all bits of x. That makes the left
//   and right sides independent: AND(l..r) == x iff AND(l..i) == x and
//   AND(i..r) == x. Both of these can only shrink as the range grows, so
//   each side has a boundary:
//   - query_left(i, x): walk left from i, find the 1st index where the
//     running AND drops below x. If it never drops, the boundary is -1.
//   - query_right(i, x): walk right from i, find the 1st index where the
//     running AND drops below x. If it never drops, the boundary is n.
//   Each query goes down the segment tree, keeps a running AND (accu), and
//   skips any fully covered node that keeps accu >= x. That is O(log n).
//
// Combine:
//   L = max(left_lteq[i], AND boundary on the left)    (exclusive)
//   R = min(right_lt[i],  AND boundary on the right)   (exclusive)
//   l has (i - L) choices and r has (R - i) choices, independently, so
//   ans += (i - L) * (R - i).
//
// Complexity: O(n log n) time, O(n) space.
// (The indices are handled in sorted order, but each one is computed
// independently, so the order does not change the result.)


vector<int> get_left_lteq(const vector<int>& arr) {
    vector<int> out(arr.size());
    vector<pair<int,int>> stack;
    stack.reserve(arr.size());

    for (int i = arr.size() - 1; i > -1; i--) {
        while (!stack.empty() && stack.back().first >= arr[i]) {
            auto [v, idx] = stack.back();
            stack.pop_back();
            out[idx] = i;
        }
        stack.emplace_back(arr[i], i);
    }

    for (auto [v, idx] : stack) {
        out[idx] = -1;
    }

    return out;
}

vector<int> get_right_lt(const vector<int>& arr) {
    vector<int> out(arr.size());
    vector<pair<int,int>> stack;
    stack.reserve(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        while (!stack.empty() && stack.back().first > arr[i]) {
            auto [v, idx] = stack.back();
            stack.pop_back();
            out[idx] = i;
        }
        stack.emplace_back(arr[i], i);
    }

    for (auto [v, idx] : stack) {
        out[idx] = arr.size();
    }

    return out;
}

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(const vector<int>& arr): len(arr.size()), tree(4 * len) {
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

    int build(const vector<int>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == e) {
            return tree[p] = arr[s];
        }

        int m = mid(s, e);
        return tree[p] = build(arr, left(p), s, m) & build(arr, right(p), m + 1, e);
    }

    // returns {idx, AND val}
    // idx is the 1st index to the left where AND(nums[i], nums[i - 1] ... nums[idx]) < lim.
    // or 0 if there isn't any.
    // accu is always >= lim.
    pair<int,int> query_left(int i, int lim, int p = 0, int s = 0, int e = -1, int accu = INT_MAX) {
        if (e == -1) e = len - 1;

        if (s == e) {
            return {s, accu & tree[p]};
        }

        if (i >= e && (tree[p] & accu) >= lim) {
            return {s, tree[p] & accu};
        }

        int m = mid(s, e);
        if (i <= m) {
            return query_left(i, lim, left(p), s, m, accu);
        } else {
            auto res = query_left(i, lim, right(p), m + 1, e, accu);
            if (res.second < lim) return res;
            return query_left(i, lim, left(p), s, m, res.second);
        }
    }

    // returns {idx, AND val}
    // idx is the 1st index to the right where AND(nums[i], nums[i + 1] ... nums[idx]) < lim.
    // or n - 1 if there isn't any.
    // accu is always >= lim.
    pair<int,int> query_right(int i, int lim, int p = 0, int s = 0, int e = -1, int accu = INT_MAX) {
        if (e == -1) e = len - 1;
        
        if (s == e) {
            return {s, accu & tree[p]};
        }

        if (i <= s && (accu & tree[p]) >= lim) {
            return {e, tree[p] & accu};
        }

        int m = mid(s, e);
        if (i > m) {
            return query_right(i, lim, right(p), m + 1, e, accu);
        } else {
            auto res = query_right(i, lim, left(p), s, m, accu);
            if (res.second < lim) return res;
            return query_right(i, lim, right(p), m + 1, e, res.second);
        }
    }
};

class Solution {
public:
    long long countConsistent(vector<int>& nums) {
        auto left_lteq = get_left_lteq(nums);
        auto right_lt = get_right_lt(nums);
        SegTree st(nums);
        long long ans = 0;

        vector<pair<int,int>> sorted;
        sorted.reserve(nums.size());
        for (int i = 0; i < nums.size(); i++) sorted.emplace_back(i, nums[i]);
        sort(sorted.begin(), sorted.end(), [] (const auto& p1, const auto& p2) { 
            if (p1.second == p2.second) {
                return p1.first < p2.first;
            } else {
                return p1.second < p2.second;
            }
        });

        for (auto [idx, val] : sorted) {
            int l1 = left_lteq[idx];
            auto [l2, accu] = st.query_left(idx, val);
            if (accu == val) l2--;
            int left_limit = max(l1, l2);

            int r1 = right_lt[idx];
            auto [r2, right_accu] = st.query_right(idx, val);
            if (right_accu == val) r2++;

            int right_limit = min(r1, r2);
            ans += 1LL * (idx - left_limit) * (right_limit - idx);
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5, 3, 1, 2};

    auto ans = sol.countConsistent(nums);
    cout << ans << endl;
}
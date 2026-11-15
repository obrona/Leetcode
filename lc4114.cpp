#include <bits/stdc++.h>
using namespace std;

// process from smallest element to largest element.
// if there are multiple smallest element process from left to right.
// suppose smallest element x is at pos i.
// want to find all subarray that contain index i and where the minimum element is x
// and also the AND of all elems in that subarray is x.
// find the 1st element to the left where y & x < x, at pos a
// this is the same as finding 1st idx to the left where nums[yi] & nums[yi + 1] ... & nums[x] < x
// find 1st element to the right where z & x < x, eg at pos b
// this is the same as finding 1st idx to the right where nums[x] & nums[x + 1] ...  nums[zi] < x
// the ans is (i - a) * (b - i).

// for subsequent elems, we need to find
// to the left, the 1st elem <= x
// to the right the 1st elem < x.
// use monotonic stack for this


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
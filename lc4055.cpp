#include <bits/stdc++.h>
using namespace std;

// want to find how many pairs (i, j)
// where i < j
// and nums[i] < nums[j]
// and for all k in [i + 1, j - 1] (inclusive of both ends), nums[k] <= nums[i] or nums[k] >= nums[j]

// suppose we are processing index i.
// let j be the earliest right element s.t arr[j] > arr[i].
// this is 1 valid shadow pair.
// the next valid shadow pair is at k, the earliest right element from j s.t arr[k] <= arr[j].
// any element between j ank k is > arr[j], and any element between i and j is <= arr[i].
// this continues until arr[k'] is <= arr[i].

// the graph form is a DAG.
// each node has 1 outgoing edge.
// let dp(j) = how many nodes reachable from index j including j.
// we want dp(j) - dp(k').

// to find index k', need a data structure that can find earliest right index from index j onwards
// that is <= arr[i].
// j here is the earliest right element s.t arr[j] > arr[i].
// not the same as earliest right index that is <= arr[i] from index i onwards.
// as that is likely to be the left of j.
// we need a special segment tree.
// tree[p] stores the min of range(s, e).
// when traversing, see the logic in the segment tree to understand the rules.
// most importantly is to see even though sometimes we traverse on both sides,
// the time complexity is still O(logn).
 
vector<int> earliest_right_g_idx(const vector<int>& arr) {
    vector<int> out(arr.size(), arr.size());
    vector<pair<int,int>> store;

    for (int i = 0; i < arr.size(); i++) {
        int curr = arr[i];
        while (store.size() > 0 && store.back().second < curr) {
            auto [idx, v] = store.back();
            store.pop_back();
            out[idx] = i;
        }
        store.emplace_back(i, curr);
    }

    return out;
}

vector<int> earliest_right_leq_idx(const vector<int>& arr) {
    vector<int> out(arr.size(), arr.size());
    vector<pair<int,int>> store;

    for (int i = 0; i < arr.size(); i++) {
        int curr = arr[i];
        while (store.size() > 0 && store.back().second >= curr) {
            auto [idx, v] = store.back();
            store.pop_back();
            out[idx] = i;
        }
        store.emplace_back(i, curr);
    }

    return out;
}

struct segtree {
    const int DEFAULT = int(1e9) + 1;

    int len;
    vector<int> tree;

    segtree(int len): len(len), tree(4 * len, DEFAULT) {}

    segtree(const vector<int>& arr): len(arr.size()), tree(4 * len, DEFAULT) {
        build(arr);
    }

    inline int mid(int s, int e) {
        return s + ((e - s) >> 1);
    }

    inline int left(int p) {
        return (p << 1) + 1;
    }

    inline int right(int p) {
        return (p << 1) + 2;
    }

    int build(const vector<int>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == - 1) e = len - 1;

        if (s == e) {
            return tree[p] = arr[s];
        }

        int m = mid(s, e);
        return tree[p] = min(
            build(arr, left(p), s, m), 
            build(arr, right(p), m + 1, e)
        );

    }

    int update(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        
        if (s == e) {
            return tree[p] = v;
        }

        int m = mid(s, e);
        if (i <= m) {
            return tree[p] = min(update(i, v, left(p), s, m), tree[right(p)]);
        } else {
            return tree[p] = min(tree[left(p)], update(i, v, right(p), m + 1, e));
        }
    }

    pair<int,int> query(int l, int r, int key, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == l && e == r && tree[p] > key) {
            return {r + 1, DEFAULT};
        }

        if (s == e) {
            if (tree[p] <= key) {
                return {s, tree[p]};
            } else {
                return {r + 1, DEFAULT};
            }
        }

        int m = mid(s, e);
        if (r <= m) {
            return query(l, r, key, left(p), s, m);
        } else if (l > m) {
            return query(l, r, key, right(p), m + 1, e);
        } else {
            auto res = query(l, m, key, left(p), s, m);
            if (res.second < DEFAULT) {
                return res;
            } else {
                return query(m + 1, r, key, right(p), m + 1, e);
            }
        }
    }
};

// given a functional acyclic graph i.e each vertex has <= 1 outgoing edge,
// find the number of vertices reachable from vertex i.
vector<int> solve_dp(const vector<int> arr) {
    vector<int> out(arr.size(), -1);

    function<int(int)> dp = [&] (int i) {
        if (i < 0 || i >= arr.size()) {
            return 0;
        }
        
        int& ans = out[i];
        return (ans != -1) ? ans : ans = 1 + dp(arr[i]);
    };

    for (int i = 0; i < arr.size(); i++) {
        out[i] = dp(i);
    }

    return out;
}

class Solution {
public:
    int shadowPairs(vector<int>& nums) {
        int cnt = 0;

        auto earliest_leq = earliest_right_leq_idx(nums);
        auto earliest_g = earliest_right_g_idx(nums);

        segtree st(nums);

        auto dp_res = solve_dp(earliest_leq);

        for (int i = 0; i < nums.size(); i++) {
            int j = earliest_g[i];
            if (j == nums.size()) continue;

            auto [k, val] = st.query(j, nums.size() - 1, nums[i]);

            int ans = dp_res[j] - (k >= nums.size() ? 0 : dp_res[k]);
            cnt += ans;
        }
        
        return cnt;
    }
};

int main() {
    Solution sol;
    
    vector<int> nums = {11,18,11,18};

    int ans = sol.shadowPairs(nums);
    cout << ans << endl;
}


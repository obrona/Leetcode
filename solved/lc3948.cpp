#include <bits/stdc++.h>
using namespace std;

// lemma. MEX can only increase as we add more values. 
// This means if S is a subset of T then MEX(S) <= MEX(T).

// for the current suffix, the greatest MEX value is the MEX of the entire suffix.
// let say it is x. Then we find the smallest index that contains 0, 1, 2, ... x - 1.
// use a range min point update segment tree and take the max of the 1st pos where 0, 1, 2 ... x - 1 occurs.
// when we remove an element, in the segment tree update st[element] with the next index value.

// special case when MEX value f the enture suffix is 0.
// then we just pop the 1st element of the current suffix, as the MEX vale of the 1st element
// of the current suffix is definitely 0.

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(int len): len(len), tree(4 * len, 999999) {}

    static int left(int p) {
        return (p << 1) + 1;
    }

    static int right(int p) {
        return (p << 1) + 2;
    }

    static int mid(int s, int e) {
        return (s + e) >> 1;
    }

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
            int lres = range_query(l, m, left(p), s, m);
            int rres = range_query(m + 1, r, right(p), m + 1, e);
            return max(lres, rres);
        }
    }
};


class Solution {
public:

    // MEX of n = len(nums) is 0
    vector<int> find_suffix_mex(const vector<int>& nums) {
        int p = 0;
        vector<bool> store(100001, false);
        vector<int> out(nums.size() + 1, 0);
        for (int i = nums.size() - 1; i > -1; i--) {
            store[nums[i]] = true;
            while (p <= 100000 && store[p]) p++;
            out[i] = p;
        }
        return out;
    }

    unordered_map<int, vector<int>> collect_pos(const vector<int>& nums) {
        unordered_map<int, vector<int>> out;
        for (auto [i, v] : views::enumerate(nums)) {
            out[v].push_back(i);
        }

        for (auto& [k, v] : out) {
            reverse(v.begin(), v.end());
        }

        return out;
    }

    vector<int> maximumMEX(vector<int>& nums) {
        vector<int> res;
        auto suffix_mexs = find_suffix_mex(nums);
        auto positions = collect_pos(nums);
        SegTree st(100001);

        for (auto& [k, v] : positions) {
            st.point_update(k, v.back());
        }

        auto pop = [&positions, &st, &nums] (int idx) {
            auto& elem_pos = positions[nums[idx]];
            elem_pos.pop_back();
            st.point_update(nums[idx], (elem_pos.empty()) ? 999999 : elem_pos.back());
        };

        for (int i = 0; i < nums.size();) {
            int suffix_mex = suffix_mexs[i];
            res.push_back(suffix_mex);
            
            if (suffix_mex == 0) {
                pop(i);
                i++;
            } else {
                int min_idx = st.range_query(0, suffix_mex - 1);
                for (int j = i; j <= min_idx; j++) {
                    pop(j);
                }
                i = min_idx + 1;
            }
        }

        return res;

    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,0,2};
    vector<int> ans = sol.maximumMEX(nums);
    for (int x : ans) cout << x << ' ';
    cout << endl;
}
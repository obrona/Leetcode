#include <bits/stdc++.h>
using namespace std;

// let diff = i - nums[i].
// we sort the pairs (diff, nums[i]) in increasing order w.r.t to diff and then increasing w.r.t to nums[i].
// we want to go from i to j, but we must be careful that between i and j there are enough elems to cut.

// lemma 1:
// suppose for 2 indices i, j, diff[i] == diff[j] and nums[i] < nums[j].
// since i = diff[i] + nums[i], i < j
// same diff means no need to cut, hence among pairs with the same diff, if the sequence is increasing
// it can be made.

// lemma 2:
// we cannot have a non decreasing sequence, must be increasing, as the final sequence
// is strictly increasing.

// lemma 3:
// suppose diff[i] < diff[j] and nums[i] < nums[j]
// num of elems we can cut between i and j, i <= j is j - i - 1
// diff[j] - diff[i] < nums[j] + diff[j] - (nums[i] + diff[i]) = j - i
// then between increasing diff[j], we can safely go to a higher nums[j]

// lemma 4:
// lowest diff[i] must appear to the left in final array. 
// this is because as diff increases, we must have deleted more elems and we only delete elems from left to right.
// combine with lemma 2.

// hence the problem becomes LIS on nums[i]

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(int len): len(len), tree(4 * len, 0) {}

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    void reset() {
        fill(tree.begin(), tree.end(), 0);
    }

    void point_update(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) {
            tree[p] = max(tree[p], v);
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

SegTree st(100001);

class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        st.reset();

        vector<pair<int,int>> store;
        for (int i = 0; i < nums.size(); i++) {
            if (i - nums[i] < 0) continue;
            store.emplace_back(i - nums[i], nums[i]);
        }

        sort(store.begin(), store.end(), [] (pair<int,int> p1, pair<int,int> p2) {
            return p1.first < p2.first || p1.first == p2.first && p1.second < p2.second;
        });

        int best = 0;
        for (auto p: store) {
            auto [diff, val] = p;
            int res = 1 + ((val > 0) ? st.range_query(0, val - 1) : 0);
            best = max(best, res);
            st.point_update(val, res);
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {3,1,2};
    int ans = sol.maxFixedPoints(nums);
    println("{}", ans);
}
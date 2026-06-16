#pragma GCC optimize("O3")           // aggressive optimization
#pragma GCC optimize("Ofast")        // O3 + unsafe math (-ffast-math)
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")  // SIMD/bit instructions

#include <bits/stdc++.h>
using namespace std;

// we want to try all [l, r] subarrays.
// replace the bottom k values in arr[l, r] with the top k values from the rest of the array.
// we fix l and extend r by 1.
// we may not need to use all the swaps, we want t s.t the top t + 1 value outside is <= the bottom t + 1 value 
// from the inside. (0-based indexing here).
// when we extend r by 1, we add 1 element into the inside set and remove 1 element from the outside set.
// instead of binary searching t, we can just check bottomK[t] and topK[t] after the modification
// and move left or right accordingly.

// I can't prove it, but the # of times we need to shift should be O(1).
// either it is t or t - 1 or t + 1.
// intuitively when add a new element, the bottom k shift right, so the new intersect index shift right by 1 or 0.
// when remove a new element, the top k shift left, so the ne intersect index shift left by 1 or 0.
// so the max delta possible is +1/-1.

// unfortunately time limit is so tight, need to switch to fenwick tree.

struct Compressor {
    vector<int> idx_to_val;   // rank -> value, in cmp order
    bool ascending = true;

    Compressor() {}

    Compressor(const vector<int>& nums, bool asc) : ascending(asc) {
        idx_to_val = nums;
        sort(idx_to_val.begin(), idx_to_val.end());
        idx_to_val.erase(unique(idx_to_val.begin(), idx_to_val.end()), idx_to_val.end());
        if (!ascending) reverse(idx_to_val.begin(), idx_to_val.end());
    }

    int get_val_from_idx(int i) const { return idx_to_val[i]; }

    int get_idx_from_val(int v) const {
        auto b = idx_to_val.begin(), e = idx_to_val.end();
        return ascending
            ? int(lower_bound(b, e, v) - b)
            : int(lower_bound(b, e, v, greater<int>()) - b);
    }

    int size() const { return (int)idx_to_val.size(); }
};

struct SegTree {
    int len;
    vector<pair<int,int>> tree;
    const Compressor& compressor;

    SegTree(int len, const Compressor& compressor): 
        len(len),
        compressor(compressor),
        tree(4 * len, pair<int,int>{0, 0})
    {}

    inline int mid(int s, int e) {
        return (s + e) >> 1;
    }

    inline int left(int p) {
        return (p << 1) + 1;
    }

    inline int right(int p) {
        return (p << 1) + 2;
    }

    void merge(pair<int,int>& p, const pair<int,int>& l, const pair<int,int>& r) {
        p.first = l.first + r.first;
        p.second = l.second + r.second;
    }

    void _update(int i, int cnt, int val, int p, int s, int e) {
        if (s == e) {
            tree[p].first += cnt;
            tree[p].second += cnt * val;
            return;
        }

        int m = mid(s, e);
        if (i <= m) {
            _update(i, cnt, val, left(p), s, m);
        } else {
            _update(i, cnt, val, right(p), m + 1, e);
        }
        merge(tree[p], tree[left(p)], tree[right(p)]);
    }

    void update(int cnt, int val) {
        int i = compressor.get_idx_from_val(val);
        _update(i, cnt, val, 0, 0, len - 1);
    }

    int _get_by_rank(int r, int p, int s, int e) {
        if (s == e) {
            return compressor.get_val_from_idx(s);
        }

        int lcnt = tree[left(p)].first;
        int m = mid(s, e);
        if (r < lcnt) {
            return _get_by_rank(r, left(p),  s, m);
        } else {
            return _get_by_rank(r - lcnt, right(p), m + 1, e);
        }
    }

    int get_by_rank(int r) {
        return _get_by_rank(r, 0, 0, len - 1);
    }

    int get_total_weight() {
        return tree[0].first;
    }

    int _sum(int l, int r, int p, int s, int e) {
        if (s == e) {
            return (long long) (r - l + 1) * tree[p].second / tree[p].first;
        }

        if (l == 0 && r == tree[p].first - 1) {
            return tree[p].second;
        }

        int m = mid(s, e);
        int l_cnt = tree[left(p)].first;
        if (r < l_cnt) {
            return _sum(l, r, left(p), s, m);
        } else if (l >= l_cnt) {
            return _sum(l - l_cnt, r - l_cnt, right(p), m + 1, e);
        } else {
            return _sum(l, l_cnt - 1, left(p), s, m) + _sum(0, r - l_cnt, right(p), m + 1, e);
        }
    }

    int sum(int l, int r) {
        return _sum(l, r, 0, 0, len - 1);
    }

    void clear() {
        fill(tree.begin(), tree.end(), pair<int,int>{0, 0});
    }
};

class Solution {
public:
    long long maxSum(const vector<int>& nums, int K) {
        Compressor increasing(nums, true);
        Compressor decreasing(nums, false);
        SegTree inside(nums.size(), increasing);
        
        SegTree Outside(nums.size(), decreasing);
        for (int x : nums) Outside.update(1, x);

        SegTree outside(nums.size(), decreasing);

        int best = -1e9;

        for (int i = 0; i < nums.size(); i++) {
            inside.clear();

            // optimisation, we just copy the Outside tree
            // from O(nlogn) -> O(n)
            outside.tree = Outside.tree;
            

            /*for (int x : nums) {
                outside.update(1, x);
            }*/

            int p = 0; // p is the first invalid index.
            int inside_sum = 0;
            for (int j = i; j < nums.size(); j++) {
                inside_sum += nums[j];

                inside.update(1, nums[j]);
                outside.update(-1, nums[j]);
                
                // here both inside and outside are not empty
                int max_size = min(j - i + 1, (int) nums.size() - (j - i + 1));
                int limit = min(K, max_size);
                p = min(p, limit); // clamp p, no point going outside.

                // if we can't move left or right that means we are done.
                while (p <= limit) {
                    if (p > 0 && inside.get_by_rank(p - 1) > outside.get_by_rank(p - 1)) {
                        p--;
                    } else if (p < outside.get_total_weight() && inside.get_by_rank(p) <= outside.get_by_rank(p)) {
                        p++;
                    } else {
                        break;
                    }
                }

                if (p > limit) p = limit;

                int to_minus = (p == 0) ? 0 : inside.sum(0, p - 1);
                int to_add = (p == 0) ? 0 : outside.sum(0, p - 1);
                int ans = inside_sum - to_minus + to_add;
                best = max(best, ans);
            }
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-1,-2,-3,-4,6,-6,-7,7,-9,-10,7};
    int k = 1;
    int ans = sol.maxSum(nums, k);
    cout << ans << endl;
}
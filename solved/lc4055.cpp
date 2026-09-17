#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <limits>
#include <memory>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;




/*
Problem summary
---------------
Count pairs i < j for which nums[i] < nums[j], but no value at an index strictly
between i and j is also strictly between nums[i] and nums[j].

Key invariant
-------------
Process the right endpoint j from left to right. For every already processed i,
define

    ceiling[i] = min(nums[k]) over i < k < j and nums[k] > nums[i],

or INF if there is no such k. In words, ceiling[i] is the smallest value seen
after i that could block a future pair starting at i.

Assume nums[i] < nums[j]. There are two possibilities:

1. ceiling[i] < nums[j].
   Some intermediate nums[k] is greater than nums[i] and smaller than nums[j],
   so k blocks (i, j).

2. ceiling[i] >= nums[j].
   Every intermediate value greater than nums[i] is at least nums[j]. Therefore
   no intermediate value lies strictly between the endpoints, so (i, j) is a
   shadow pair.

Consequently,

    (i, j) is a shadow pair iff nums[i] < nums[j] <= ceiling[i].

After processing j, nums[j] becomes an intermediate value for future endpoints.
For every i with nums[i] < nums[j], the invariant is restored by

    ceiling[i] = min(ceiling[i], nums[j]).

Notice that ceiling[i] == nums[j] still produces a valid pair: equality is not
strictly between the endpoint values. Thus the update must count ceilings >=
nums[j], even though chmin does not numerically change ceilings equal to nums[j].

Ordering by value
-----------------
Give every index its own position after sorting the keys (nums[i], i). Keeping i
in the key is important because equal array values still represent distinct
indices with distinct ceilings. All positions whose value is strictly smaller
than nums[j] form one prefix. Positions for future indices have not been activated
yet, so they contribute nothing.

For that prefix, one operation must:

    * count all stored ceilings >= nums[j], and
    * replace every ceiling with min(ceiling, nums[j]).

This is exactly a range-chmin operation augmented with a count, which is handled
by segment tree beats. Finally, j is activated with ceiling[j] = INF.
*/






pair<function<int(int)>, function<int(int, int)>> compress(const vector<int>& arr) {
    using Key = pair<int, int>;

    using OrderedSet = tree<
        Key,
        null_type,
        less<Key>,
        rb_tree_tag,
        tree_order_statistics_node_update
    >;

    auto store = make_shared<OrderedSet>();

    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        // The index makes duplicate values occupy separate leaves.
        store->insert({arr[i], i});
    }

    function<int(int)> orderByValue = [store] (int value) {
        // Number of keys whose array value is strictly smaller than value.
        return static_cast<int>(
            store->order_of_key({value, numeric_limits<int>::min()})
        );
    };

    function<int(int, int)> orderByKey = [store] (int value, int index) {
        return static_cast<int>(store->order_of_key({value, index}));
    };

    return {orderByValue, orderByKey};
}


struct segtree {
    
    struct node {
        // Largest ceiling, second-largest distinct ceiling, and the number of
        // active leaves attaining the largest ceiling in this segment.
        int max_val = 0;
        int second_max_val = 0;
        int max_cnt = 0;
    };

    int len;
    vector<node> tree;

    segtree(int len): len(len), tree(4 * len) {}

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    int mid(int s, int e) {
        return s + ((e - s) >> 1);
    }

    void apply_chmin(int p, int val) {
        if (tree[p].max_val > val) {
            tree[p].max_val = val;
        }
    }

    void push_down(int p) {
        // A chmin applied at p only lowers its old maximum. Propagate that cap
        // to children whose maximum is still larger than the parent's maximum.
        apply_chmin(left(p), tree[p].max_val);
        apply_chmin(right(p), tree[p].max_val);
    }

    void pull_up(int p) {
        int l = left(p), r = right(p);

        if (tree[l].max_val == tree[r].max_val) {
            tree[p].max_val = tree[l].max_val;
            tree[p].max_cnt = tree[l].max_cnt + tree[r].max_cnt;
            tree[p].second_max_val = max(tree[l].second_max_val, tree[r].second_max_val);
        } else if (tree[l].max_val > tree[r].max_val) {
            tree[p].max_val = tree[l].max_val;
            tree[p].max_cnt = tree[l].max_cnt;
            tree[p].second_max_val = max(tree[l].second_max_val, tree[r].max_val);
        } else {
            tree[p].max_val = tree[r].max_val;
            tree[p].max_cnt = tree[r].max_cnt;
            tree[p].second_max_val = max(tree[l].max_val, tree[r].second_max_val);
        }
    }

    // On [l, r], count ceilings >= val (including equality), then apply chmin(val).
    //
    // If max_val < val, this segment contributes nothing. If second_max_val <
    // val <= max_val, only the maximum-valued leaves qualify, so max_cnt is the
    // answer and only max_val needs to be capped. Otherwise, more than one
    // distinct ceiling may qualify, so recurse into the children.
    int update_and_count(int val, int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        
        if (s == l && e == r) {
            if (tree[p].max_val < val){
                return 0;
            } else if (tree[p].second_max_val < val) {
                tree[p].max_val = val;
                return tree[p].max_cnt;
            }
        }

        push_down(p);

        int m = mid(s, e);
        int ans;
        if (r <= m) {
            ans = update_and_count(val, l, r, left(p), s, m);
        } else if (l > m) {
            ans = update_and_count(val, l, r, right(p), m + 1, e);
        } else {
            ans = update_and_count(val, l, m, left(p), s, m)
                + update_and_count(val, m + 1, r, right(p), m + 1, e);
        }

        pull_up(p);

        return ans;
    }

    void set(int i, int val, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == e) {
            tree[p].max_val = val;
            tree[p].second_max_val = 0;
            tree[p].max_cnt = 1;
            return;
        }

        push_down(p);

        int m = mid(s, e);
        if (i <= m) {
            set(i, val, left(p), s, m);
        } else {
            set(i, val, right(p), m + 1, e);
        }

        pull_up(p);
    }
};

class Solution {
public:
    int shadowPairs(vector<int>& nums) {
        segtree st(nums.size());
        auto [compressed_by_val, compressed_by_value_and_index] = compress(nums);
        
        int cnt = 0;
        for (int i = 0; i < static_cast<int>(nums.size()); i++) {
            // All earlier indices with nums[index] < nums[i] lie in this prefix.
            int limit = compressed_by_val(nums[i]);
            if (limit != 0) {
                int res = st.update_and_count(nums[i], 0, limit - 1);
                cnt += res;
            }

            // This index can now serve as the left endpoint of future pairs.
            int pos = compressed_by_value_and_index(nums[i], i);
            st.set(pos, int(1e9) + 1);
        }

        return cnt;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {3,1,4,2,5};

    int ans = sol.shadowPairs(nums);
    cout << ans << endl;
}

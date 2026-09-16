#include <functional>
#include <utility>
#include <vector>
#include <unordered_map>
#include <limits>
#include <memory>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;




// a difficult problem that requires a new technique called segment tree beats.
// 1st, we compress the values, however, equal values do not get collapse into the same value.
// i.e we are sorting (idx, val) then sort increasing val then increasing index.
// the compress function takes in (idx, val) -> compressed index.

// each compressed index stores the ceiling val.
// for later elems at index j, j can form a shadow pair with i if nums[j] <= seg array[compressed(i, arr[i])]
// so we need to count how many elements with value >= nums[j].
// to update we need to do a chmin update
// i,e seg arr[i] = min(seg arr[i], x)
// thankfully we are counting the number of elements that are going to be affected by the chmin update.
// makes the update (and query, contained in the update) to be logn






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
        store->insert({arr[i], i});
    }

    function<int(int)> orderByValue = [store] (int value) {
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
        int max_val = 0;
        int second_max_val = 0;
        int max_cnt = 0;
        int propogate_val = -1;

        int cnt = 0;
    };

    int len;
    vector<node> tree;

    segtree(int len): len(len), tree(4 * len) {}

    int left(int p) {
        return p << 1;
    }

    int right(int p) {
        return (p << 1) | 1;
    }

    int mid(int s, int e) {
        return s + ((e - s) >> 1);
    }

    void push_down(int p) {
        if (tree[p].propogate_val == -1) return;
        
        tree[left(p)].max_val = tree[right(p)].max_val = tree[p].max_val;
        tree[p].propogate_val = -1;
    }

    void pull_up(int p) {
        int l = left(p), r = right(p);

        if (tree[l].max_val == tree[r].max_val) {
            tree[p].max_val = tree[l].max_val;
            tree[p].max_cnt = tree[l].max_cnt + tree[r].max_cnt;
        } else if (tree[l].max_val > tree[r].max_val) {
            tree[p].max_val = tree[l].max_val;
            tree[p].max_cnt = tree[r].max_cnt;
        } else {
            tree[p].max_val = tree[r].max_cnt;
            tree[p].max_cnt = tree[r].max_cnt;
        }

        tree[p].second_max_val = max(tree[l].second_max_val, tree[r].second_max_val);

        tree[p].cnt = tree[l].cnt + tree[r].cnt;
    }

    // does chmin and also returns the number of elems whose values changed
    // if x = arr[i] for min(arr[i], x) we also consider that element changed.
    int update_and_count(int val, int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        
        if (r < s || l > e) {
            return 0;
        }

        if (l <= s && e <= r) {
            if (tree[p].max_val < val) {
                return 0;
            } else if (tree[p].second_max_val < val) {
                tree[p].propogate_val = (tree[p].propogate_val == -1) ? val : min(tree[p].propogate_val, val);
                tree[p].max_val = val;
                return tree[p].max_cnt;
            }
        }
        
        push_down(p);

        int m = mid(s, e);
        int lres = update_and_count(val, l, m, left(p), s, m);
        int rres = update_and_count(val, m + 1, r, right(p), m + 1, e);

        pull_up(p);

        return lres + rres;
    }

    void set(int i, int val, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == e) {
            tree[p].max_val = val;
            tree[p].second_max_val = 0;
            tree[p].max_cnt = tree[p].cnt = 1;
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
        for (int i = 0; i < nums.size(); i++) {
            int limit = compressed_by_val(nums[i]);
            if (limit != 0) {
                int res = st.update_and_count(nums[i], 0, limit - 1);
                cnt += res;
            }

            int pos = compressed_by_value_and_index(nums[i], i);
            st.set(pos, int(1e9) + 1);
        }

        return cnt;
    }
};
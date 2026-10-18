#include <bits/stdc++.h>
using namespace std;

// greedy.
// sort the target intervals in increasing startpoint.
// [s0, e0] [s1, e1] ...
// it does not matter if the intervals overlap, or even completely cover. 
// starting from [s0, e0]
// take the interval if the rightmost endpoint.
// i.e max j for all [i, j], i <= s0.

// we can use a treap for largest val for all key <= k, but actually is not needed.

struct TreapNode {
    inline static mt19937 rng{};

    uint32_t priority;

    int key;
    set<int> vals;
    int agg;

    TreapNode *l = nullptr;
    TreapNode *r = nullptr;

    TreapNode(int key, int val): 
        priority(rng()), 
        key(key), 
        vals{val},
        agg(val)
    {}
};

int get_agg(TreapNode *n) {
    return (!n) ? 0 : n->agg;
}

int get_val(TreapNode *n) {
    return (!n) ? 0 : n->agg;
}

void cut(TreapNode *n) {
    n->agg = *n->vals.rbegin();
    n->l = nullptr;
    n->r = nullptr;
}

void combine(TreapNode *n, TreapNode *l, TreapNode *r) {
    n->agg = max({*n->vals.rbegin(), get_agg(l), get_agg(r)});
    n->l = l;
    n->r = r;
}

void clear(TreapNode* n) {
    if (!n) return;
    clear(n->l);
    clear(n->r);
    delete n;
}

// split into {<, =, >}.
array<TreapNode*, 3> split(TreapNode *n, int key) {
    if (!n) return {nullptr, nullptr, nullptr};

    if (n->key == key) {
        auto l = n->l;
        auto r = n->r;
        cut(n);
        return {l, n, r};
    } else if (n->key < key) {
        auto [l, e, r] = split(n->r, key);
        combine(n, n->l, l);
        return {n, e, r};
    } else {
        auto [l, e, r] = split(n->l, key);
        combine(n, r, n->r);
        return {l, e, n};
    }  
}

TreapNode* merge(TreapNode *l, TreapNode *r) {
    if (!l) return r;
    if (!r) return l;

    if (l->priority >= r->priority) {
        combine(l, l->l, merge(l->r, r));
        return l;
    } else {
        combine(r, merge(l, r->l), r->r);
        return r;
    }
}

void insert(TreapNode*& root, int key, int val) {
    if (!root) {
        root = new TreapNode(key, val);
        return;
    }

    auto [l, e, r] = split(root, key);

    if (e) {
        e->vals.insert(val);
        e->agg = *e->vals.rbegin();
    } else {
        e = new TreapNode(key, val);
    }

    root = merge(l, merge(e, r));
}

void remove(TreapNode*& root, int key, int val) {
    if (!root) return;

    auto [l, e, r] = split(root, key);

    if (e) {
        auto it = e->vals.find(val);
        if (it != e->vals.end()) {
            e->vals.erase(e->vals.find(val));
        }
        
        if (e->vals.size() == 0) {
            delete e;
            e = nullptr;
        } else {
            e->agg = *e->vals.rbegin();
        }
        
    }

    root = merge(l, merge(e, r));
}

// return max val for all k <= key
int query(TreapNode *n, int key) {
    if (!n) return 0;

    if (n->key == key) {
        return max(get_agg(n->l), *n->vals.rbegin());
    } else if (n->key < key) {
        return max({get_agg(n->l), *n->vals.rbegin(), query(n->r, key)});
    } else {
        return query(n->l, key);
    }
}


class Solution {
public:
    int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals) {
        sort(targetIntervals.begin(), targetIntervals.end(), [] (const auto& i1, const auto& i2) {
            return i1[0] < i2[0];
        });

        TreapNode *root = nullptr;
        for (const auto& i : availableIntervals) insert(root, i[0], i[1]);

        int cnt = 0;
        int end = 0;
        for (const auto& i : targetIntervals) {
            int s = i[0];
            int e = i[1];

            if (end >= e) continue;

            // a target interval can take several intervals to cover.
            while (end < e) {
                int begin = max(s, end);
                int r = query(root, begin);

                if (r == 0 || r <= end) return -1;

                end = r;
                cnt++;
            }
                   
        }

        clear(root);

        return cnt;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> availableIntervals = {{1,4}, {1,7}, {3,9}, {5,10}, {10,15}};
    vector<vector<int>> targetIntervals = {{1,3}, {2,5}, {7,8}, {10,13}, {11,15}, {12,13}};

    int ans = sol.minSelection(availableIntervals, targetIntervals);
    cout << ans << endl;
}

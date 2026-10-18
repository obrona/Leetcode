#include <bits/stdc++.h>
using namespace std;

// greedy.
// sort the target intervals in increasing startpoint.
// [s0, e0] [s1, e1] ...
// it does not matter if the intervals overlap, or even completely cover. 
// starting from [s0, e0]
// take the interval if the rightmost endpoint.
// i.e max j for all [i, j], i <= s0.
// need a custom data structure, i.e treap.

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
        vals{val} 
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
    n->agg = max({*--n->vals.end(), get_agg(l), get_agg(r)});
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
        e->vals.erase(e->vals.find(val));
        if (e->vals.size() == 0) {
            delete e;
            e = nullptr;
        }
    }

    root = merge(l, merge(e, r));
}


class Solution {
public:
    int minSelection(vector<vector<int>>& availableIntervals, vector<vector<int>>& targetIntervals) {
        
    }
};

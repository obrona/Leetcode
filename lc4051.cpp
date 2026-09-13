#include <bits/stdc++.h>
using namespace std;

// we can use a treap.
// when processing index i, we have the subarray sums for [0:i-1], [1:i-1] ... [i-1:i-1].
// we do range add of entire tree arr[i].
// then we add arr[i].
// the treap is a multiset.
// since a treap is also a sorted bst, it is easy to find how many elems <= k or >= k.

struct node {
    inline static mt19937 rng{};

    int priority = 0;
    long long key = 0;
    long long to_propogate = 0;
    int count = 1;
    int weight = 1;

    node *left = nullptr;
    node *right = nullptr;

    node(long long key): priority(rng()), key(key) {}
};

int get_weight(node *n) {
    return (n == nullptr) ? 0 : n->weight;
}

void push_down(node *n) {
    if (!n) return;
    
    auto f = [p = n->to_propogate] (node *child) {
        child->to_propogate += p;
        child->key += p;
    };

    if (n->left) f(n->left);
    if (n->right) f(n->right);
}

void recombine(node *n, node *left, node *right) {
    n->weight = n->count + get_weight(left) + get_weight(right);
    n->left = left;
    n->right = right;
}

void cleanup(node *n) {
    if (!n) return;
    cleanup(n->left);
    cleanup(n->right);
    delete n;
}

void global_add(node *n, long long val) {
    if (!n) return;
    n->to_propogate += val;
    n->key += val;
}

// < key, = key, > key
array<node*, 3> split(node *n, long long key) {
    if (!n) return {nullptr, nullptr, nullptr};

    push_down(n);

    if (n->key == key) {
        recombine(n, nullptr, nullptr);
        return {n->left, n, n->right};
    } else if (n->key < key) {
        auto [l, e, r] = split(n->right, key);
        recombine(n, n->left, l);
        return {n, e, r};
    } else {
        auto [l, e, r] = split(n->left, key);
        recombine(n, r, n->right);
        return {l, e, n};
    }
}

node* merge(node *left, node *right) {
    if (!left) return right;
    if (!right) return left;

    push_down(left);
    push_down(right);

    if (left->priority >= right->priority) {
        recombine(left, left->left, merge(left->right, right));
        return left;
    } else {
        recombine(right, merge(left, right->left), right->right);
        return right;
    }
}

void insert(node *&root, long long key) {
    auto [l, e, r] = split(root, key);
    if (e) {
        e->count++;
    } else {
        e = new node(key);
    }
    root = merge(merge(l, e), r);
}

int count_geq(node *root, long long key) {
    if (!root) return 0;

    if (root->key == key) {
        return root->count + get_weight(root->right);
    } else if (root->key > key) {
        return count_geq(root->left, key) + root->count + get_weight(root->right);
    } else {
        return count_geq(root->right, key);
    }
}

int count_leq(node *root, long long key) {
    if (!root) return 0;

    if (root->key == key) {
        return get_weight(root->left) + root->count;
    } else if (root->key < key) {
        return get_weight(root->left) + root->count + count_leq(root->right, key);
    } else {
        return count_leq(root->left, key);
    }
}
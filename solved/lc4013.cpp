#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// convert odd elems to -a, even elems to b.
// a valid subarray then has subarray sum <= 0.
// starting from left to right, whenever we process arr[i],
// add arr[i] to all elems in treap, then add arr[i].
// then count how many elems >= 0

struct tnode {
    inline static mt19937 rng{};

    ll val;
    int prior;
    int cnt;
    int subtree_cnt;
    ll lazy;
    tnode *left = nullptr, *right = nullptr;

    tnode() {}
    
    tnode(ll val): val(val), prior(rng()), cnt(1), subtree_cnt(1), lazy(0) {}
};

int get_cnt(tnode* node) {
    return node ? node->subtree_cnt : 0;
}

void push_down(tnode *root) {
    if (!root) return;
    
    if (root->left) {
        root->left->val += root->lazy;
        root->left->lazy += root->lazy;
    }
    if (root->right) {
        root->right->val += root->lazy;
        root->right->lazy += root->lazy;
    }

    root->lazy = 0;
}

void process(tnode* node, tnode* left, tnode* right) {
    node->left = left;
    node->right = right;
    node->subtree_cnt = node->cnt + (left ? left->subtree_cnt : 0) + (right ? right->subtree_cnt : 0);
}

// split into {less than, equal, more than}.
// invariant: the returned nodes have no more lazy values that need to be propogated.
array<tnode*, 3> split(tnode *node, ll key) {
    if (!node) return {nullptr, nullptr, nullptr};
    
    push_down(node);
    
    if (node->val == key) {
        auto l = node->left, r = node->right;
        process(node, nullptr, nullptr);
        return {l, node, r};
    }
    
    else if (node->val < key) {
        auto [l, e, r] = split(node->right, key);
        process(node, node->left, l);
        return {node, e, r};
    } 

    else {
        auto [l, e, r] = split(node->left, key);
        process(node, r, node->right);
        return {l, e, node};
    }
}

tnode* merge(tnode *t1, tnode *t2) {
    // vital to push down FIRST !!!.
    // otherwise we push incorrect values to wrong trees.
    push_down(t1);
    push_down(t2);
    if (!t1) return t2;
    if (!t2) return t1;

    if (t1->prior >= t2->prior) {
        process(t1, t1->left, merge(t1->right, t2));
        return t1;
    } else {
        process(t2, merge(t1, t2->left), t2->right);
        return t2;
    }
}

void insert(tnode*& root, ll key) {
    auto [l, e, r] = split(root, key);
    if (e) {
        e->cnt++;
        e->subtree_cnt++;
        root = merge(l, merge(e, r));
    } else {
        tnode *e = new tnode(key);
        root = merge(l, merge(e, r));
    }
}

// we just need to paint all range
void add_all(tnode*&root, ll val) {
    if (!root) return;
    root->val += val;
    root->lazy += val;
}

int count_lesser(tnode*&root, ll key) {
    if (!root) return 0;
    
    push_down(root);
    if (root->val == key) {
        return get_cnt(root->left);
    } else if (root->val < key) {
        return root->cnt + get_cnt(root->left) + count_lesser(root->right, key);
    } else {
        return count_lesser(root->left, key);
    }
}

void clean(tnode*& root) {
    if (!root) return;
    if (root->left) clean(root->left);
    if (root->right) clean(root->right);
    delete root;
    root = nullptr;
}

class Solution {
public:
    long long countRatioSubarrays(vector<int>& nums, int a, int b) {
        ll cnt = 0;
        tnode* root = nullptr;

        for (int x : nums) {
            int t = x % 2 == 0 ? b : -a;
            add_all(root, t);
            insert(root, t);
            cnt += count_lesser(root, 1);
        }

        clean(root);
        
        return cnt; 
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2,2,1};
    int a = 2, b = 1;
    ll ans = sol.countRatioSubarrays(nums, a, b);
    cout << ans << endl;
}
#include <bits/stdc++.h>
using namespace std;

// sort the array in increasing xi.
// at index i, we store index i, index i + 1 ... index j where |xi - xj| <= k in a implicit treap.
// when we move to index i + 1, we remove node 0 (containing index i)
// then add the new nodes satisfying the requirement.
// we have to do a range update too.
// we use a range add to get the max yi + yj + |xi - xj|

// implementation of implicit treaps and its functions.
struct tnode {
    inline static mt19937 rng{};

    tnode *left = nullptr, *right = nullptr;
    
    int prior;
    int sz = 1;
    
    int val = 0;
    int range_max_val = 0;
    
    int lazy = 0;

    tnode() {}

    tnode(int val): prior(rng()), val(val), range_max_val(val) {}
};

int get_sz(tnode* node) {
    return (!node) ? 0 : node->sz;
}

int get_range_max_val(tnode* node) {
    return (!node) ? -(int)1e9 : node->range_max_val;
}

void push_down_helper(tnode* node, int val) {
    if (!node) return;
    node->val += val;
    node->range_max_val += val;
    node->lazy += val;

}

void push_down(tnode* node) {
    if (node->left) push_down_helper(node->left, node->lazy);
    if (node->right) push_down_helper(node->right, node->lazy);
    node->lazy = 0;
}

void merge_new_children(tnode* parent, tnode* left, tnode* right) {
    if (!parent) return;
    parent->left = left;
    parent->right = right;
    parent->sz = 1 + get_sz(left) + get_sz(right);
    parent->range_max_val = max({parent->val, get_range_max_val(left), get_range_max_val(right)});
}

// split into < idx, >= idx.
array<tnode*, 2> split(tnode* node, int i) {
    if (!node) return {nullptr, nullptr};
    
    push_down(node);
    int my_idx = get_sz(node->left);
    if (my_idx == i) {
        auto l = node->left;
        merge_new_children(node, nullptr, node->right);
        return {l, node};
    } else if (my_idx < i) {
        auto [l, r] = split(node->right, i - my_idx - 1);
        merge_new_children(node, node->left, l);
        return {node, r};
    } else {
        auto [l, r] = split(node->left, i);
        merge_new_children(node, r, node->right);
        return {l, node};
    }
}

tnode* merge(tnode* left, tnode* right) {
    if (!left) return right;
    if (!right) return left;

    push_down(left);
    push_down(right);
    if (left->prior >= right->prior) {
        auto r = merge(left->right, right);
        merge_new_children(left, left->left, r);
        return left;
    } else {
        auto l = merge(left, right->left);
        merge_new_children(right, l, right->right);
        return right;
    }
}

void range_update_entire_tree(tnode* node, int val) {
    if (!node) return;
    node->lazy += val;
    node->val += val;
    node->range_max_val += val;
}

void pop_front(tnode*& root) {
    auto [l, r] = split(root, 1);
    delete l;
    root = r;
}

void push_back(tnode *& root, int new_val) {
    tnode* new_node = new tnode(new_val);
    root = merge(root, new_node);
}

void cleanup(tnode*& root) {
    if (!root) return;
    cleanup(root->left);
    cleanup(root->right);
    delete root;
    root = nullptr;
}

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        sort(points.begin(), points.end(), [] (auto& p1, auto& p2) {
            return p1[0] < p2[0];
        });

        int best = -1e9;
        int p = 1;
        tnode* root = nullptr;
        for (int i = 0; i < points.size(); i++) {
            auto& curr = points[i];
            
            p = max(p, i + 1);
            while (p < points.size()) {
                auto& next = points[p];
                int diff = next[0] - curr[0];
                if (diff > k) break;
                push_back(root, diff + curr[1] + next[1]);
                p++;
            }

            int res = get_range_max_val(root);
            best = max(best, res);

            if (i < points.size() - 1) {
                pop_front(root);
                int diff = points[i + 1][1] - points[i][1] - (points[i + 1][0] - points[i][0]);
                range_update_entire_tree(root, diff);
            }

        }
        
        cleanup(root);
        return best;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> points = {{1,3}, {2,0}, {5,10}, {6,-10}};
    int k = 1;

    int ans = sol.findMaxValueOfEquation(points, k);
    cout << ans << endl;
}




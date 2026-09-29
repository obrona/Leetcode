#include <bits/stdc++.h>
using namespace std;

// basically we need a forward and reverse iterator.
// since it is a bst, the input is "sorted"
// if i pairs with j, then i' must pair with j' where i < i' and j' < j.
// so the forward iterator only needs to go forward and the backward iterator only needs to go backward.
// in the bst all values are distinct.

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ForwardIterator {
    vector<TreeNode*> stack;

    ForwardIterator(TreeNode* root) {
        while (root) {
            stack.push_back(root);
            root = root->left;
        }
    }

    TreeNode* next() {
        if (stack.empty()) return nullptr;
        auto out = stack.back();
        stack.pop_back();
        
        auto next = out->right;
        while (next) {
            stack.push_back(next);
            next = next->left;
        } 

        return out;
    }
};

struct BackwardIterator {
    vector<TreeNode*> stack;

    BackwardIterator(TreeNode* root) {
        while (root) {
            stack.push_back(root);
            root = root->right;
        }
    }

    TreeNode* next() {
        if (stack.empty()) return nullptr;
        auto out = stack.back();
        stack.pop_back();

        auto next = out->left;
        while (next) {
            stack.push_back(next);
            next = next->right;
        }

        return out;
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        auto it = ForwardIterator(root);
        auto rit = BackwardIterator(root);

        auto l = it.next();
        auto r = rit.next();

        while (l) {
            while (r && l->val + r->val > k) {
                r = rit.next();
            }

            if (!r || l == r) return false;
            if (l->val + r->val == k) return true;
            l = it.next();
        }

        return false;
    }
};

int main() {
    Solution sol;

    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);

    auto it = ForwardIterator(root);
    while (auto p = it.next()) {
        cout << p->val << " ";
    }
    cout << endl;

    auto rit = BackwardIterator(root);
    while (auto p = rit.next()) {
        cout << p->val << " ";
    }
    cout << endl;


}
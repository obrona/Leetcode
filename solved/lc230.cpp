#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// k here is 0 indexed.
// return {element found, remaining count}.
pair<int,int> dfs(TreeNode *root, int k) {
    if (!root) {
        return {-1, k};
    }

    auto p = dfs(root->left, k);
    if (p.second == -1) {
        return p;
    }

    if (p.second == 0) {
        return {root->val, -1};
    }

    return dfs(root->right, p.second - 1);


}

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        auto [ans, _cnt] = dfs(root, k - 1);
        return ans;
    }
};
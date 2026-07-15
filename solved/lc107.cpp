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

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root) return {};

        vector<vector<int>> out;
        list<TreeNode*> q;
        q.push_back(root);

        while (!q.empty()) {
            vector<int> lvl;
            for (int len = q.size(); len > 0; len--) {
                TreeNode* t = q.front();
                q.pop_front();
                lvl.push_back(t->val);

                if (t->left) q.push_back(t->left);
                if (t->right) q.push_back(t->right);
            }
            out.push_back(std::move(lvl));
        }

        reverse(out.begin(), out.end());
        return out;
    }
};
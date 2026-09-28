#include <iostream>
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
            return root;
        }
        if (root->val < key) {
            root->right = deleteNode(root->right, key);
            return root;
            
        }

        if (!root->left) {
            auto ans = root->right;
            delete root;
            return ans;
        }
        if (!root->right) {
            auto ans = root->left;
            delete root;
            return ans;
        }

        auto par = root;
        auto curr = root->right;

        while (curr->left) {
            par = curr;
            curr = curr->left;
        }
        
        if (par == root) {
            curr->left = root->left;
            return curr;
        } else {
            par->left = curr->right;
            curr->left = root->left;
            curr->right = root->right;
        }

        delete root;

        return curr;
    }
};
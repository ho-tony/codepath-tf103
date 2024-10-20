#include <iostream>
using namespace std;

/**
 *
 * Definition for a binary tree node.
 */
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
    int minDepth(TreeNode* root) { 
        if (root == NULL) {
            return 0;
        }
        return dfs(root);
    }
    int dfs(TreeNode *n) {
        if (n->left == NULL && n->right == NULL) {
            return 1;
        }
        int left = INT_MAX;
        if (n->left != NULL) {
            left = 1 + dfs(n->left);
        }
        int right = INT_MAX;
        if (n->right != NULL) {
            right = 1 + dfs(n->right);
        }
        return min(left, right);


        


    }
};
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution2 {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (!dfs(root)) {
            return NULL;
        } else {
            return root;
        }
        
        
    }
    bool dfs(TreeNode* n) {
        if (n == NULL) {
            return false;
        }
        bool containsOne = n->val == 1;
        bool leftHasOne = dfs(n->left);
        bool rightHasOne = dfs(n->right);
        if (!leftHasOne) {
            n->left = NULL;
        }
        if (!rightHasOne) {
            n->right = NULL;
        }
        return containsOne || leftHasOne || rightHasOne;

    }
};


//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
// Definition for a binary tree node.
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) {
            return res;
        }

        queue<TreeNode*> lastQ;
        int lastSize = 1, curSize;
        lastQ.push(root);
        TreeNode* node;
        
        while (!lastQ.empty()) {
            vector<int> lastLevelNums;
            curSize = 0;

            // level traverse
            while (lastSize--) {
                node = lastQ.front();
                lastLevelNums.push_back(node->val);

                if (node->left) {
                    lastQ.push(node->left);
                    ++curSize;
                }
                if (node->right) {
                    lastQ.push(node->right);
                    ++curSize;
                }

                lastQ.pop();
            }

            res.push_back(lastLevelNums);
            lastSize = curSize;
        }

        return res;
    }
};

int main(void) {
    Solution solution;

    TreeNode* tree1 = new TreeNode(3);
    tree1->left = new TreeNode(9);
    tree1->right = new TreeNode(20);
    tree1->right->left = new TreeNode(15);
    tree1->right->right = new TreeNode(7);
    vector<vector<int>> res1 = solution.levelOrder(tree1);

    TreeNode* tree2 = new TreeNode(1);
    vector<vector<int>> res2 = solution.levelOrder(tree2);

    vector<vector<int>> res3 = solution.levelOrder(nullptr);

    return 0;
}

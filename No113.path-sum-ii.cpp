#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No113. 路径总和 II (dfs)
 * 给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
返回:

[
   [5,4,11,2],
   [5,8,4,5]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/path-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class Solution {
public:
    vector<vector<int>> m_ans;
    vector<int> tmp;
    int m_target;
    void dfs(TreeNode* node) {
        if (node) {
            m_target -= node->val;
            tmp.push_back(node->val);

            // 叶子节点，且累加和相等
            if (!node->left && !node->right && 0 == m_target) {
                m_ans.push_back(tmp);
            }

            dfs(node->left);
            dfs(node->right);

            m_target += node->val;
            tmp.pop_back();
        }
    }

    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        m_target = sum;
        dfs(root);
        return m_ans;
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->right->left = new TreeNode(5);
    root->right->right->right = new TreeNode(1);
    int sum = 22;
    vector<vector<int>> result = solution.pathSum(root, sum);
    MyTools::printVec2D(result);
    return 0;
}
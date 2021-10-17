/** 题目描述：
 * 112. 路径总和
 * 给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190317
 * */
#include <iostream>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//假设：所有结点的值均大于0
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        //特殊值
        if (root == NULL) {
            return false;
        }
        //判断是否是叶子结点，且值与sum相等
        if (root->left == NULL && root->right == NULL) {
            return root->val == sum;
        }
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};



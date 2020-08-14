/** 题目描述：
 * 111. 二叉树的最小深度
 * 给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明: 叶子节点是指没有子节点的节点。

示例:

给定二叉树 [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回它的最小深度  2.

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

class Solution {
public:
    int minDepth(TreeNode* root) {
        //特殊值
        if (root == NULL) {
            return 0;
        }
        //左右子结点均为空
        if (root->left == NULL && root->right == NULL) {
            return 1;
        }
        //若左子结点为空，则右子结点非空
        if (root->left == NULL) {
            return minDepth(root->right)+1;
        }
        //若右子结点为空，则左子结点非空
        if (root->right == NULL) {
            return minDepth(root->left)+1;
        }
        //左右子结点均非空
        int leftMinDepth = minDepth(root->left);
        int rightMinDepth = minDepth(root->right);
        return leftMinDepth < rightMinDepth ? ++leftMinDepth : ++rightMinDepth;
    }
};



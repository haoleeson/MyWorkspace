/** 题目描述：    【审题。。。】
 * 110. 平衡二叉树
 * 给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。

示例 1:

给定二叉树 [3,9,20,null,null,15,7]

    3
   / \
  9  20
    /  \
   15   7
返回 true 。

示例 2:

给定二叉树 [1,2,2,3,3,null,null,4,4]

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
返回 false 。
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
    bool isBalanced(TreeNode* root) {
        //特殊值
        if (root == NULL) {
            return true;
        }//判断根结点是否平衡
        if (!isBalanceNode(root)) {
            return false;
        }
        return isBalanced(root->left)&&isBalanced(root->right);
    }

    //判断一个结点是否是平衡结点
    bool isBalanceNode (TreeNode* node) {
        //空结点，返回true
        if (node == NULL) {
            return true;
        }
        //无子结点，返回true
        if (node->left == NULL && node->right == NULL) {
            return true;
        }
        //左子结点为空，右子结点非空;
            //只有右子结点无左右孩子才返回true，其他情况返回false
        if (node->left == NULL) {
            return node->right->left==NULL && node->right->right==NULL;
        }
        //右子结点为空，左子结点非空;
            //只有左子结点无左右孩子才返回true，其他情况返回false
        if (node->right == NULL) {
            return node->left->left==NULL && node->left->right==NULL;
        }
        //左右子结点均非空，计算左右子树高度
        int leftRootHeight = getNodeHeight(node->left);
        int rightRootHeight = getNodeHeight(node->right);
        return leftRootHeight > rightRootHeight ? (leftRootHeight < rightRootHeight+2) : (rightRootHeight < leftRootHeight+2);
    }

    //获取结点高度
    int getNodeHeight (TreeNode* node) {
        if (node == NULL) {
            return 0;
        }
        //若左右子结点均非空，返回左右子树较高的高度值
        if (node->left != NULL && node->right != NULL) {
            int leftHeight = getNodeHeight(node->left);
            int rightHeight = getNodeHeight(node->right);
            return leftHeight > rightHeight ? ++leftHeight : ++rightHeight;
        }
        //若右子结点为空，左子结点非空
        if (node->left != NULL) {
            return getNodeHeight(node->left) + 1;
        }
        //若左子结点为空，右子结点非空
        if (node->right != NULL) {
            return getNodeHeight(node->right) + 1;
        }
        //左右子结点全空
        else {
            return 1;
        }
    }
};



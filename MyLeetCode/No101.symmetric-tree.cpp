/** 题目描述：
 * 101. 对称二叉树
 * 给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

    1
   / \
  2   2
 / \ / \
3  4 4  3
但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

    1
   / \
  2   2
   \   \
   3    3
说明:

如果你可以运用递归和迭代两种方法解决这个问题，会很加分。

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190303
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
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) {
            return true;
        }
        return isMirror(root, root);
    }
    bool isMirror(TreeNode *p, TreeNode *q) {
        //左右全为空，返回true， 左右一个空一个非空返回false
        if (p == NULL){
            return q == NULL;
        }
        if (q == NULL) {
            return p == NULL;
        }
        //左右非空
        if (p->val == q->val) {
            return isMirror(p->left, q->right) && isMirror(p->right, q->left);
        } else {
            return false;
        }
    }
};

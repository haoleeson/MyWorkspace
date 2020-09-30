#include <iostream>
#include "myTools.h"
using namespace std;

/**
 * No701. 二叉搜索树中的插入操作 (dfs 、 迭代)
 * 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据保证，新值和原始二叉搜索树中的任意节点值都不同。
 * 注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以返回任意有效的结果。

例如,
给定二叉搜索树:

        4
       / \
      2   7
     / \
    1   3
和 插入的值: 5
你可以返回这个二叉搜索树:
         4
       /   \
      2     7
     / \   /
    1   3 5
或者这个树也是有效的:
         5
       /   \
      2     7
     / \   
    1   3
         \
          4

提示：

给定的树上的节点数介于 0 和 10^4 之间
每个节点都有一个唯一整数值，取值范围从 0 到 10^8
-10^8 <= val <= 10^8
新值和原始二叉搜索树中的任意节点值都不同

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-into-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) {
            return new TreeNode(val);
        }
        TreeNode* ptr = root;
        while (true) {
            if (ptr->val < val) {
                if (!ptr->right) {
                    ptr->right = new TreeNode(val);
                    break;
                }
                ptr = ptr->right;
            } else {
                if (!ptr->left) {
                    ptr->left = new TreeNode(val);
                    break;
                }
                ptr = ptr->left;
            }
        }
        return root;
    }
};

/**
 * 解题思路1：迭代（遍历搜索二叉树、遇空插入）
 */
class Solution1 {
public:
    int m_val;
    TreeNode* dfs(TreeNode* root) {
        if (!root) {
            return new TreeNode(m_val);
        }
        if (root->val < m_val) {
            root->right = dfs(root->right);
        } else {
            root->left = dfs(root->left);
        }
        return root;
    }
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        m_val = val;
        return dfs(root);
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    int val = 5;
    TreeNode* result = solution.insertIntoBST(root, val);
    MyTools::printTree(root);
    return 0;
}
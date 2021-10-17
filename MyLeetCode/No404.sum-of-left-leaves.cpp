#include <iostream>
#include "myTools.h"
using namespace std;

/**
 * No404. 左叶子之和 (递归)
 * 计算给定二叉树的所有左叶子之和。

示例：
    3
   / \
  9  20
    /  \
   15   7

在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-left-leaves
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    int m_sum = 0;
    void dfs(TreeNode* node, bool isLeftNode) {
        if (node != nullptr) {
            // 判断左叶子
            if (isLeftNode && node->left == nullptr && node->right == nullptr) {
                m_sum += node->val;
            }
            dfs(node->left, true);
            dfs(node->right, false);
        }
    }
    int sumOfLeftLeaves(TreeNode* root) {
        dfs(root, false);
        return m_sum;
    }
};

/**
 * 力扣路人一行代码
 */
class Solution2 {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        return root ? sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right)
                      + (root->left && !root->left->left && !root->left->right? root->left->val : 0) : 0;
    }
};

int main() {
    Solution2 solution;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    cout << solution.sumOfLeftLeaves(root) << endl;
    return 0;
}
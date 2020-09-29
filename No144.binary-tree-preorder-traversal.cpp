#include <iostream>
#include <vector>
#include <stack>
#include "myTools.h"
using namespace std;

/**
 * No144. 二叉树的前序遍历 (迭代)
 * 给定一个二叉树，返回它的前序遍历。

示例:
输入: [1,null,2,3]  
   1
    \
     2
    /
   3 

输出: [1,2,3]
进阶:递归算法很简单，你可以通过迭代算法完成吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-preorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 解法：迭代
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        stack<TreeNode* > s;
        // 前序：根 左 右
        while (root != nullptr || !s.empty()) {
            if (root != nullptr) {
                // 输出 根
                ans.push_back(root->val);
                // 栈存 右
                if (root->right) {
                    s.push(root->right);
                }
                // 遍历 左
                root = root->left;
            } else {
                root = s.top();
                s.pop();
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    vector<int> result = solution.preorderTraversal(root);
    MyTools::printVec(result);
    return 0;
}
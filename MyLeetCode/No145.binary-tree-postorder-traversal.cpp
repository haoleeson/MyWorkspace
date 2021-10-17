#include <iostream>
#include <vector>
#include <stack>
#include "myTools.h"
using namespace std;

/**
 * No145. 二叉树的后序遍历 (递归 、 迭代)
 * 给定一个二叉树，返回它的 后序 遍历。

示例:

输入: [1,null,2,3]  
   1
    \
     2
    /
   3 

输出: [3,2,1]
进阶: 递归算法很简单，你可以通过迭代算法完成吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-postorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 解法2：迭代 (变异前序（根 右 左） 的逆序输出（左 右 根）)
 */
class Solution {
public:
    // 变异前序遍历：根 右 左
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        stack<TreeNode*> s;

        while (root != nullptr || !s.empty()) {
            if (root != nullptr) {
                // 头插 根
                ans.insert(ans.begin(), root->val);
                // 栈存 左
                if (root->left) {
                    s.push(root->left);
                }
                // 遍历 右
                root = root->right;
            } else {
                root = s.top();
                s.pop();
            }
        }
        return ans;
    }
};

/**
 * 解法1：递归
 */
class Solution1 {
public:
    vector<int> m_ans;
    // 后序遍历：左 右 根
    void postOrder(TreeNode* root) {
        if (root) {
            postOrder(root->left);
            postOrder(root->right);
            m_ans.push_back(root->val);
        }
    }
    vector<int> postorderTraversal(TreeNode* root) {
        postOrder(root);
        return m_ans;
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    vector<int> result = solution.postorderTraversal(root);
    MyTools::printVec(result);
    return 0;
}
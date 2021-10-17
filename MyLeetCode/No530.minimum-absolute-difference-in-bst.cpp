/**
 * No530. 二叉搜索树的最小绝对差 （中序遍历）
 * 给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。

示例：
输入：
   1
    \
     3
    /
   2
输出：
1
解释：
最小绝对差为 1，其中 2 和 1 的差的绝对值为 1（或者 2 和 3）。

提示：
树中至少有 2 个节点。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <stack>
#include "myTools.h"
using namespace std;

class Solution {
public:
    // 中序遍历
    int getMinimumDifference(TreeNode* root) {
        int tmpDiff, minDiff = INT32_MAX, lastVal = root->val  - INT32_MAX;
        // 中序遍历（左 根 右）
        stack<TreeNode*> s;
        while (root || !s.empty()) {
            // 先遍历左节点，根节点入栈
            while (root) {
                // 栈存 根
                s.push(root);
                // 遍历 左
                root = root->left;
            }
            root = s.top();
            s.pop();
            // 输出 根
            tmpDiff = root->val - lastVal;
            lastVal = root->val;
            if (tmpDiff < minDiff) {
                minDiff = tmpDiff;
            }
            // 遍历 右
            root = root->right;
        }
        return  minDiff;
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(2);
    cout << solution.getMinimumDifference(root) << endl;
    return 0;
}

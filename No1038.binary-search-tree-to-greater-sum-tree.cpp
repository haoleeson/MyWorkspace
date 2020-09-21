#include <iostream>
#include <stack>
#include "myTools.h"
using namespace std;

/**
 * No1038. 从二叉搜索树到更大和树
 * 给出二叉 搜索 树的根节点，该二叉树的节点值各不相同，修改二叉树，使每个节点 node的新值等于原树中大于或等于node.val的值之和。

提醒一下，二叉搜索树满足下列约束条件：
* 节点的左子树仅包含键 小于 节点键的节点。
* 节点的右子树仅包含键 大于 节点键的节点。
* 左右子树也必须是二叉搜索树。

例如：
输入: 原始二叉搜索树:
              5
            /   \
           2     13

输出: 转换为累加树:
             18
            /   \
          20     13

 提示：
树中的节点数介于 1 和 100 之间。
每个节点的值介于 0 和 100 之间。
给定的树为二叉搜索树。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 思路2：逆中序递归遍历，在递归返回是累加值
 */
class Solution {
public:
    int sum = 0;
    // 逆中序遍历（右，中，左）
    TreeNode* bstToGst(TreeNode* root) {
        if (root) {
            // 右
            bstToGst(root->right);
            // 中
            root->val += sum;
            sum = root->val;
            // 左
            bstToGst(root->left);
        }
        return root;
    }
};

/**
 * 思路1：中序遍历搜索树，节点存堆栈，再逐一出栈
 */
class Solution1 {
public:
    stack<TreeNode* > stack;
    void midOrder(TreeNode* node) {
        if (node) {
            midOrder(node->left);
            stack.push(node);
            midOrder(node->right);
        }
    }
    TreeNode* bstToGst(TreeNode* root) {
        TreeNode* tmp;
        int sum = 0;
        // 中序遍历，记录值
        midOrder(root);

        while (!stack.empty()) {
            tmp = stack.top();
            sum += tmp->val;
            tmp->val = sum;
            stack.pop();
        }
        return root;
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(13);
    MyTools::printTree(root);
    root = solution.bstToGst(root);
    MyTools::printTree(root);
    return 0;
}
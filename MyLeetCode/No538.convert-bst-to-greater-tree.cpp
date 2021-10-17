#include <iostream>
#include <stack>
#include "myTools.h"
using namespace std;

/**
 * No538. 把二叉搜索树转换为累加树 （逆中序遍历 + 递归）
 * 给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，使得每个节点的值是原来的节点值加上所有大于它的节点值之和。

例如：
输入: 原始二叉搜索树:
              5
            /   \
           2     13

输出: 转换为累加树:
             18
            /   \
          20     13

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/convert-bst-to-greater-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 思路2：逆中序递归遍历，在递归返回是累加值
 */
class Solution {
public:
    int sum = 0;
    // 逆中序遍历（右，中，左）
    TreeNode* convertBST(TreeNode* root) {
        if (root) {
            // 右
            convertBST(root->right);
            // 中
            root->val += sum;
            sum = root->val;
            // 左
            convertBST(root->left);
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
    TreeNode* convertBST(TreeNode* root) {
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
    root = solution.convertBST(root);
    MyTools::printTree(root);
    return 0;
}
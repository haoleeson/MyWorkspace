#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/**
 * No94. 二叉树的中序遍历 （左 根 右）
 * 给定一个二叉树，返回它的中序遍历。

示例:
输入: [1,null,2,3]
   1
    \
     2
    /
   3

输出: [1,3,2]
进阶:递归算法很简单，你可以通过迭代算法完成吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-inorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 解题思路：迭代
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode*> S;
        TreeNode* ptr = root;

        while (ptr || S.size()) {
            // 先遍历左节点，根节点入栈
            while (ptr) {
                S.push(ptr);
                ptr = ptr->left;
            }
            ptr = S.top();
            S.pop();
            // 再遍历根节点
            ans.push_back(ptr->val);
            // 最后遍历右节点
            ptr = ptr->right;
        }
        return ans;
    }
};

class Solution0 {
public:
    vector<int> m_ans;
    void Recursion(TreeNode* root) {
        if (root != nullptr) {
            // 左
            Recursion(root->left);
            // 根
            m_ans.push_back(root->val);
            // 右
            Recursion(root->right);
        }
    }
    vector<int> inorderTraversal(TreeNode* root) {
        Recursion(root);
        return m_ans;
    }
};

template<typename T>
void printVec2D(vector<T> vec) {
    int size = vec.size();
    cout << "[";
    if (size > 0) {
        cout << vec[0];
        for (int i = 1; i < size; ++i) {
            cout << ", " << vec[i];
        }
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    vector<int> result = solution.inorderTraversal(root);
    printVec2D(result);
    return 0;
}

#include<iostream>
#include<vector>
using namespace std;

//给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 个最小元素（从 1 开始计数）。
//
//    1 <= preorder.length <= 3000
//    inorder.length == preorder.length
//    -3000 <= preorder[i], inorder[i] <= 3000
//    preorder 和 inorder 均 无重复 元素
//    inorder 均出现在 preorder
//    preorder 保证 为二叉树的前序遍历序列
//    inorder 保证 为二叉树的中序遍历序列

//示例1：
//输入:
// preorder = [3,9,20,15,7]
// inorder  = [9,3,15,20,7]
//输出: [3,9,20,null,null,15,7]

//示例2：
//输入: preorder = [-1], inorder = [-1]
//输出: [-1]

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        order = 0;
        trace(root, k);
        return res;
    }

private:
    void trace(TreeNode* root, int k) {
        if (root == nullptr) {
            return;
        }

        trace(root->left, k);
        ++order;
        if (order == k) {
            res = root->val;
            return;
        }
        trace(root->right, k);
    }
private:
    int res = INT_MIN;
    int order = 0;
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(3);
    tree1->left = new TreeNode(1);
    tree1->right = new TreeNode(4);
    tree1->left->right = new TreeNode(2);

    TreeNode* tree2 = new TreeNode(5);
    tree2->left = new TreeNode(3);
    tree2->right = new TreeNode(6);
    tree2->left->left = new TreeNode(2);
    tree2->left->right = new TreeNode(4);
    tree2->left->left->left = new TreeNode(1);

    cout << "The 1th smallest element in tree1 is: " << solution.kthSmallest(tree1, 1) << endl;
    cout << "The 3th smallest element in tree2 is: " << solution.kthSmallest(tree2, 3) << endl;

    return 0;
}
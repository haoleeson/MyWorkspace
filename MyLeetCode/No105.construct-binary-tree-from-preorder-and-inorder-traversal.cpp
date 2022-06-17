
#include<iostream>
#include<vector>
using namespace std;

//给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

private:
    TreeNode* build(vector<int>& preorder, int pS, int pE, vector<int>& inorder, int iS, int iE) {
        if (pS > pE) {
            return nullptr;
        }

        int rootVal = preorder[pS];
        int iR = iS;
        while (iR <= iE && inorder[iR] != rootVal) {
            ++iR;
        }
        int len_left = iR - iS;

        TreeNode* leftPtr = build(preorder, pS + 1, pS + len_left, inorder, iS, iR - 1);
        TreeNode* rightPtr = build(preorder, pS + len_left + 1, pE, inorder, iR + 1, iE);

        return new TreeNode(rootVal, leftPtr, rightPtr);
    }
};

int main(void) {
    Solution solution;
    int p[] = {3,9,20,15,7};
    int i[] = {9,3,15,20,7};
    vector<int> preorder = vector<int>(p, p + sizeof(p)/sizeof(int));
    vector<int> inorder = vector<int>(i, i + sizeof(i)/sizeof(int));

    TreeNode* genTree = solution.buildTree(preorder, inorder);

    return 0;
}
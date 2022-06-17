#include<iostream>
#include<vector>
using namespace std;

// 给你一个整数 n ，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同 二叉搜索树 。可以按 任意顺序 返回答案。
//
// 提示：
// 1 <= n <= 8


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
    vector<TreeNode*> generateTrees(int n) {
        if (!n) {
            return {nullptr};
        }

        return traverseGen(1, n);
    }

private:
    vector<TreeNode*> traverseGen(int iS, int iE) {
        if (iS > iE) {
            return {nullptr};
        }

        vector<TreeNode*> allTrees;

        // 枚举可行根节点
        for (int i = iS; i <= iE; ++i) {
            vector<TreeNode*> allLeftNodes = traverseGen(iS, i - 1);
            vector<TreeNode*> allRightNodes = traverseGen(i + 1, iE);

            // 从左右集合中各选一个可行子树，拼接成一个可行解
            for (auto& leftPtr : allLeftNodes) {
                for (auto& rightPtr : allRightNodes) {
                    TreeNode* currNode = new TreeNode(i);
                    currNode->left = leftPtr;
                    currNode->right = rightPtr;
                    allTrees.push_back(currNode);
                }
            }
        }
        return allTrees;
    }
};

int main(void) {
    Solution solution;
    vector<TreeNode*> treeList = solution.generateTrees(3);

    return 0;
}
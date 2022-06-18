//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include<vector>
using namespace std;
// Definition for a binary tree node.
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
    vector<int> rightSideView(TreeNode* root) {
        traverse(root, 1);
        return res;
    }

private:
    void traverse(TreeNode* root, int level) {
        if (!root) {
            return;
        }

        if (res.size() < level) {
            res.push_back(root->val);
        }

        traverse(root->right, level + 1);
        traverse(root->left, level + 1);
    }
    vector<int> res;
};

int main(void) {
    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);
    tree1->left->right = new TreeNode(5);
    tree1->right->right = new TreeNode(4);

    Solution solution1;
    vector<int> res = solution1.rightSideView(tree1);

    TreeNode* tree2 = new TreeNode(1);
    tree2->right = new TreeNode(3);
    Solution solution2;
    vector<int> res2 = solution2.rightSideView(tree2);

    Solution solution3;
    vector<int> res3 = solution3.rightSideView(nullptr);

    return 0;
}

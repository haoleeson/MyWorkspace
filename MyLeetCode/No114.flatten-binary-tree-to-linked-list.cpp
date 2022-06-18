//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
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
    void flatten(TreeNode* root) {
        if (!root) {
            return;
        }

        flatten(root->right);
        flatten(root->left);

        root->left = nullptr;
        root->right = prePtr;
        prePtr = root;
    }

private:
    TreeNode* prePtr = nullptr;
};

int main(void) {
    Solution solution1;
    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(5);
    tree1->left->left = new TreeNode(3);
    tree1->left->right = new TreeNode(4);
    tree1->right->right = new TreeNode(6);
    solution1.flatten(tree1);

    Solution solution2;
    TreeNode* tree2 = nullptr;
    solution2.flatten(tree2);

    Solution solution3;
    TreeNode* tree3 = new TreeNode(0);
    solution3.flatten(tree3);

    return 0;
}

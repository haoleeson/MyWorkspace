//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include "myTools.h"
using namespace std;

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            return new TreeNode(val, root, nullptr);
        }

        traverse(root, val, depth - 1);
        return root;
    }

private:
    void traverse(TreeNode* root, int val, int depth) {
        if (!root) {
            return;
        }

        if (depth == 1) {
            root->left = new TreeNode(val, root->left, nullptr);
            root->right = new TreeNode(val, nullptr, root->right);
        } else if (depth > 1) {
            traverse(root->left, val, depth - 1);
            traverse(root->right, val, depth - 1);
        }
    }
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(4);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(6);
    tree1->left->left = new TreeNode(3);
    tree1->left->right = new TreeNode(1);
    tree1->right->left = new TreeNode(5);
    TreeNode* res1 = solution.addOneRow(tree1, 1, 2);
    MyTools::printTree(res1);

    TreeNode* tree2 = new TreeNode(4);
    tree2->left = new TreeNode(2);
    tree2->left->left = new TreeNode(3);
    tree2->left->right = new TreeNode(1);
    TreeNode* res2 = solution.addOneRow(tree2, 1, 3);
    MyTools::printTree(res2);

    return 0;
}

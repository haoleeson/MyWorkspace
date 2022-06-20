//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include "myTools.h"
using namespace std;

class Solution {
public:
    // 根 左 右
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root) {
            return false;
        }

        // 开始全树判断
        if (root->val == subRoot->val) {
            if (isTheSame(root, subRoot)) {
                return true;
            }
        }

        // 向左右子树寻找
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

private:
    bool isTheSame(TreeNode* tree1, TreeNode* tree2) {
        if (!tree1 && !tree2) {
            return true;
        } else if ((!tree1 && tree2) || (tree1 && !tree2)) {
            return false;
        }

        if (tree1->val != tree2->val) {
            return false;
        }

        return isTheSame(tree1->left, tree2->left) && isTheSame(tree1->right, tree2->right);
    }
};

int main(void) {
    Solution solution1;
    TreeNode* tree1 = new TreeNode(3);
    tree1->left = new TreeNode(4);
    tree1->right = new TreeNode(5);
    tree1->left->left = new TreeNode(1);
    tree1->left->right = new TreeNode(2);

    TreeNode* tree_1 = new TreeNode(4);
    tree_1->left = new TreeNode(1);
    tree_1->right = new TreeNode(2);
    cout << solution1.isSubtree(tree1, tree_1) << endl;

    Solution solution2;
    TreeNode* tree2 = new TreeNode(3);
    tree2->left = new TreeNode(4);
    tree2->right = new TreeNode(5);
    tree2->left->left = new TreeNode(1);
    tree2->left->right = new TreeNode(2);
    tree2->left->right->left = new TreeNode(0);
    cout << solution2.isSubtree(tree2, tree_1) << endl;

    return 0;
}

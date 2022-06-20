//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include "myTools.h"
using namespace std;

class Solution {
public:
    string tree2str(TreeNode* root) {
        if (!root) {
            return "";
        }

        string preStr = to_string(root->val);
        if (!root->left && !root->right) {
            return preStr;
        } else if (!root->left) {
            return preStr + LEFT_BRACKET + RIGHT_BRACKET + LEFT_BRACKET + tree2str(root->right) + RIGHT_BRACKET;
        }

        string leftStr = tree2str(root->left);
        string rightStr = tree2str(root->right);

        if (root->right) {
            return preStr + LEFT_BRACKET + leftStr + RIGHT_BRACKET + LEFT_BRACKET + rightStr + RIGHT_BRACKET;
        }

        return preStr + LEFT_BRACKET + leftStr + RIGHT_BRACKET;
    }

private:
    string LEFT_BRACKET = "(";
    string RIGHT_BRACKET = ")";
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);
    tree1->left->left = new TreeNode(4);
    cout << solution.tree2str(tree1) << endl;

    TreeNode* tree2 = new TreeNode(1);
    tree2->left = new TreeNode(2);
    tree2->right = new TreeNode(3);
    tree2->left->right = new TreeNode(4);
    cout << solution.tree2str(tree2) << endl;

    return 0;
}

//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include "myTools.h"
using namespace std;

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        traverse(root, 1);
        return v[v.size() - 1];
    }

private:
    vector<int> v;
    void traverse(TreeNode* root, int level) {
        if (!root) {
            return;
        }

        if (level > v.size()) {
            v.push_back(root->val);
        }
        traverse(root->left, level + 1);
        traverse(root->right, level + 1);
    }
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(2);
    tree1->left = new TreeNode(1);
    tree1->right = new TreeNode(3);
    cout << solution.findBottomLeftValue(tree1) << endl;

    Solution solution2;
    TreeNode* tree2 = new TreeNode(1);
    tree2->left = new TreeNode(2);
    tree2->right = new TreeNode(3);
    tree2->left->left = new TreeNode(4);
    tree2->right->left = new TreeNode(5);
    tree2->right->right = new TreeNode(6);
    tree2->right->left->left = new TreeNode(7);
    cout << solution2.findBottomLeftValue(tree2) << endl;

    return 0;
}

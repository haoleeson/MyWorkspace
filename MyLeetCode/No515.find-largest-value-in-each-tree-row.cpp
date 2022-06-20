//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
//#include<strstream>
#include<list>
#include "myTools.h"
using namespace std;

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        traverse(root, 1);
        return v;
    }

private:
    vector<int> v;
    void traverse(TreeNode* root, int level) {
        if (!root) {
            return;
        }

        if (level > v.size()) {
            v.push_back(root->val);
        } else if (root->val > v[level - 1]) {
            v[level - 1] = root->val;
        }
        traverse(root->left, level + 1);
        traverse(root->right, level + 1);
    }
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(3);
    tree1->right = new TreeNode(2);
    tree1->left->left = new TreeNode(5);
    tree1->left->right = new TreeNode(3);
    tree1->right->right = new TreeNode(9);
    vector<int> res1 = solution.largestValues(tree1);
    MyTools::printVec(res1);

    Solution solution2;
    TreeNode* tree2 = new TreeNode(1);
    tree2->left = new TreeNode(2);
    tree2->right = new TreeNode(3);
    vector<int> res2 = solution2.largestValues(tree2);
    MyTools::printVec(res2);

    return 0;
}

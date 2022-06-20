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
    int findTilt(TreeNode* root) {
        subTreeSum(root);
        return sumPo;
    }

private:
    long sumPo = 0;
    int subTreeSum(TreeNode* root) {
        if (!root) {
            return 0;
        }

        long leftSubSum = subTreeSum(root->left);
        long rightSubSum = subTreeSum((root->right));

        sumPo += absSub(leftSubSum, rightSubSum);

        return leftSubSum + rightSubSum + root->val;
    }
    long absSub(long a, long b) {
        return a > b ? a - b : b - a;
    }
};

int main(void) {
    Solution solution1;
    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);
    cout << solution1.findTilt(tree1) << endl;

    Solution solution2;
    TreeNode* tree2 = new TreeNode(4);
    tree2->left = new TreeNode(2);
    tree2->right = new TreeNode(9);
    tree2->left->left = new TreeNode(3);
    tree2->left->right = new TreeNode(5);
    tree2->right->right = new TreeNode(7);
    cout << solution2.findTilt(tree2) << endl;

    Solution solution3;
    TreeNode* tree3 = new TreeNode(21);
    tree3->left = new TreeNode(7);
    tree3->right = new TreeNode(14);
    tree3->left->left = new TreeNode(1);
    tree3->left->right = new TreeNode(1);
    tree3->right->left = new TreeNode(2);
    tree3->right->right = new TreeNode(2);
    tree3->left->left->left = new TreeNode(3);
    tree3->left->left->right = new TreeNode(3);
    cout << solution3.findTilt(tree3) << endl;

    return 0;
}

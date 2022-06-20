//
// Created by eisenhao on 2022/6/20.
//

#include<iostream>
#include<queue>
#include "myTools.h"
using namespace std;

class Solution {
    struct withOrNotVal{
        int with = 0;
        int withOut = 0;
    };
public:
    int rob(TreeNode* root) {
        withOrNotVal ans = traverse(root);
        return max(ans.with, ans.withOut);
    }

private:
    withOrNotVal traverse(TreeNode* root) {
        if (!root) {
            return {0, 0};
        }

        withOrNotVal leftVal = traverse(root->left);
        withOrNotVal rightVal = traverse(root->right);

        int withRoot = root->val + leftVal.withOut + rightVal.withOut;
        int withOutRoot = max(leftVal.with, leftVal.withOut) + max(rightVal.with, rightVal.withOut);
        return {withRoot, withOutRoot};
    }
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(3);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);
    tree1->left->right = new TreeNode(3);
    tree1->right->right = new TreeNode(1);
    int res1 = solution.rob(tree1);
    cout << res1 << endl;

    TreeNode* tree2 = new TreeNode(3);
    tree2->left = new TreeNode(4);
    tree2->right = new TreeNode(5);
    tree2->left->left = new TreeNode(1);
    tree2->left->right = new TreeNode(3);
    tree2->right->right = new TreeNode(1);
    int res2 = solution.rob(tree2);
    cout << res2 << endl;



    return 0;
}

#include <iostream>

#include "myTools.h"
using namespace std;

class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (!containOneTraverse(root)) {
            return nullptr;
        }

        return root;
    }

private:
    // 后续遍历（子树是否包含1）
    bool containOneTraverse(TreeNode* root) {
        if (!root) {
            return false;
        }

        bool leftVal = containOneTraverse(root->left);
        bool rightVal = containOneTraverse(root->right);

        // 若左右子树不包含1，则剪枝
        if (!leftVal) {
            root->left = nullptr;
            // delete root->left;
        }
        if (!rightVal) {
            root->right = nullptr;
            // delete root->right;
        }

        return root->val == 1 || leftVal || rightVal;
    }
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(1);
    tree1->right = new TreeNode(0);
    tree1->right->left = new TreeNode(0);
    tree1->right->right = new TreeNode(1);
    TreeNode* res1 = solution.pruneTree(tree1);
    MyTools::printTree(res1);

    TreeNode* tree2 = new TreeNode(1);
    tree2->left = new TreeNode(0);
    tree2->right = new TreeNode(1);
    tree2->left->left = new TreeNode(0);
    tree2->left->right = new TreeNode(0);
    tree2->right->left = new TreeNode(0);
    tree2->right->right = new TreeNode(1);
    TreeNode* res2 = solution.pruneTree(tree2);
    MyTools::printTree(res2);

    TreeNode* tree3 = new TreeNode(1);
    tree3->left = new TreeNode(1);
    tree3->right = new TreeNode(0);
    tree3->left->left = new TreeNode(1);
    tree3->left->right = new TreeNode(1);
    tree3->right->left = new TreeNode(0);
    tree3->right->right = new TreeNode(1);
    tree3->left->left->left = new TreeNode(0);
    TreeNode* res3 = solution.pruneTree(tree3);
    MyTools::printTree(res3);

    return 0;
}

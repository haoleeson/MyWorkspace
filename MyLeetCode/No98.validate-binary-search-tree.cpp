#include<iostream>
#include<vector>
using namespace std;

//给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
//
//有效 二叉搜索树定义如下：
//
//节点的左子树只包含 小于 当前节点的数。
//节点的右子树只包含 大于 当前节点的数。
//所有左子树和右子树自身必须也是二叉搜索树。



//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    long preNum = LONG_MIN;
public:
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return true;
        }

        if (!isValidBST(root->left)) {
            return false;
        }

        if (root->val <= preNum) {
            return false;
        }
        preNum = root->val;

        return isValidBST(root->right);
    }
};


class Solution0 {
public:
    bool isValidBST(TreeNode* root) {
        res = true;
        lastNum = LONG_MIN;
        traverse(root);
        return res;
    }

private:
    void traverse(TreeNode* root) {
        if (!root) {
            return;
        }

        traverse(root->left);
        if (lastNum >= root->val) {
            res = false;
            return;
        }
        lastNum = root->val;
        traverse(root->right);
    }
    long lastNum;
    bool res;
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(2);
    tree1->left = new TreeNode(1);
    tree1->right = new TreeNode(3);

    TreeNode* tree2 = new TreeNode(5);
    tree2->left = new TreeNode(1);
    tree2->right = new TreeNode(4);
    tree2->right->left = new TreeNode(3);
    tree2->right->right = new TreeNode(6);

    cout << solution.isValidBST(tree1) << endl;
    cout << solution.isValidBST(tree2) << endl;

    return 0;
}
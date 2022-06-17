
#include<iostream>
using namespace std;

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
public:
    int diameterOfBinaryTree(TreeNode* root) {
        res = 0;
        maxDeep(root);
        return res - 1;
    }

private:
    int res = INT_MIN;
    int maxDeep(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int leftMax = maxDeep(root->left);
        int rightMax = maxDeep(root->right);

        int val = leftMax + rightMax + 1;
        if (val > res) {
            res = val;
        }

        return max(leftMax, rightMax) + 1;
    }
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);
    tree1->left->left = new TreeNode(4);
    tree1->left->right = new TreeNode(5);


    cout << "diameter of binary of tree1 is: " << solution.diameterOfBinaryTree(tree1) << endl;

    return 0;
}
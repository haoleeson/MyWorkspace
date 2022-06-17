//
// Created by eisenhao on 2022/6/17.
//
#include<iostream>
using namespace std;
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    TreeNode* recordPrePtrArr[2] = {nullptr, nullptr};
    TreeNode* recordCurrArr[2] = {nullptr, nullptr};
    TreeNode* prePtr = nullptr;
    int i = 0;
public:
    void recoverTree(TreeNode* root) {
        traverse(root);
        swapTwoNode();
    }

private:
    void traverse(TreeNode* root) {
        if (!root) {
            return;
        }

        traverse(root->left);
        if (prePtr && prePtr->val > root->val) {
            recordPrePtrArr[i] = prePtr;
            recordCurrArr[i] = root;
            ++i;
        }
        prePtr = root;
        traverse(root->right);
    }

    void swapTwoNode() {
        // 不相邻两节点
        if (recordPrePtrArr[0] && recordPrePtrArr[1]) {
            int tmp = recordPrePtrArr[0]->val;
            recordPrePtrArr[0]->val = recordCurrArr[1]->val;
            recordCurrArr[1]->val = tmp;
        }
        // 相邻两节点
        else if (recordPrePtrArr[0] && !recordPrePtrArr[1]) {
            int tmp = recordPrePtrArr[0]->val;
            recordPrePtrArr[0]->val = recordCurrArr[0]->val;
            recordCurrArr[0]->val = tmp;
        }
    }
};

int main(void) {
    Solution solution;

    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(3);
    tree1->left->right = new TreeNode(2);
    solution.recoverTree(tree1);

    Solution solution2;
    TreeNode* tree2 = new TreeNode(3);
    tree2->left = new TreeNode(1);
    tree2->right = new TreeNode(4);
    tree2->right->left = new TreeNode(2);
    solution2.recoverTree(tree2);

    return 0;
}

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


int maxDeep = 0;
int deep = 0;
void trace(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    ++deep;
    if (deep > maxDeep) {
        maxDeep = deep;
    }
    trace(root->left);
    trace(root->right);
    --deep;
}

int getMaxDeep(TreeNode* root) {
    maxDeep = 0;
    deep = 0;
    trace(root);
    return maxDeep;
}

int getMaxDeep2(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDeep = getMaxDeep2(root->left);
    int rightDeep = getMaxDeep2(root->right);
    return max(leftDeep, rightDeep) + 1;
}

int level = 0;
void printEveryElementLeve(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    ++level;
    cout << level << "l:" << root->val << endl;
    printEveryElementLeve(root->left);
    printEveryElementLeve(root->right);
    --level;
}

void printEveryElementLeve2(TreeNode* root, int level) {
    if (root == nullptr) {
        return;
    }

    cout << level << "l:" << root->val << endl;
    printEveryElementLeve2(root->left, level + 1);
    printEveryElementLeve2(root->right, level + 1);
}

int main(void) {
    TreeNode* tree1 = new TreeNode(3);
    tree1->left = new TreeNode(1);
    tree1->right = new TreeNode(4);
    tree1->left->right = new TreeNode(2);

    TreeNode* tree2 = new TreeNode(5);
    tree2->left = new TreeNode(3);
    tree2->right = new TreeNode(6);
    tree2->left->left = new TreeNode(2);
    tree2->left->right = new TreeNode(4);
    tree2->left->left->left = new TreeNode(1);

    cout << getMaxDeep(tree1) << endl;
    cout << getMaxDeep(tree2) << endl;

    cout << getMaxDeep2(tree1) << endl;
    cout << getMaxDeep2(tree2) << endl;


    return 0;
}
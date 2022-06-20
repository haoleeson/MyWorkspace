//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include<vector>
#include "myTools.h"
using namespace std;

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key)
    {
        if (root == nullptr)    return nullptr;
        if (key > root->val)    root->right = deleteNode(root->right, key);     // 去右子树删除
        else if (key < root->val)    root->left = deleteNode(root->left, key);  // 去左子树删除
        else    // 当前节点就是要删除的节点
        {
            if (!root->left)   return root->right; // 情况1，欲删除节点无左子
            if (!root->right)  return root->left;  // 情况2，欲删除节点无右子
            TreeNode* node = root->right;           // 情况3，欲删除节点左右子都有
            while (node->left)          // 寻找欲删除节点右子树的最左节点
                node = node->left;
            node->left = root->left;    // 将欲删除节点的左子树成为其右子树的最左节点的左子树
            root = root->right;         // 欲删除节点的右子顶替其位置，节点被删除
        }
        return root;
    }
};


// 方式1：递归
class Solution_ERR {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) {
            return root;
        }

        if (key == root->val) {
            if (root->right) {
                // 暂存后续 -> right 遍历的值
                vector<int> v;
                TreeNode* node = root->right;
                while (node) {
                    v.push_back(node->val);
                    node = node->right;
                }

                node = root;
                for (int i = 0; i < v.size() - 1; ++i) {
                    node->val = v[i];
                    node = node->right;
                }
                if (node->right) {
                    node->val = v[v.size() - 1];
                    delete node->right;
                    node->right = nullptr;
                }
            } else if (root->left) {
                // 暂存后续 -> left 遍历的值
                vector<int> v;
                TreeNode* node = root->left;
                while (node) {
                    v.push_back(node->val);
                    node = node->left;
                }

                node = root;
                for (int i = 0; i < v.size() - 1; ++i) {
                    node->val = v[i];
                    node = node->left;
                }
                if (node->left) {
                    node->val = v[v.size() - 1];
                    delete node->left;
                    node->left = nullptr;
                }
            } else {
                delete root;
                root = nullptr;
            }
            return root;
        } else if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else {
            root->right = deleteNode(root->right, key);
        }

        return root;
    }
};

int main(void) {
    Solution solution;
    TreeNode* tree1 = new TreeNode(5);
    tree1->left = new TreeNode(3);
    tree1->right = new TreeNode(6);
    tree1->left->left = new TreeNode(2);
    tree1->left->right = new TreeNode(4);
    tree1->right->right = new TreeNode(7);
    tree1 = solution.deleteNode(tree1, 3);
    MyTools::printTree(tree1);

    TreeNode* tree2 = new TreeNode(0);
    tree2 = solution.deleteNode(tree2, 0);
    MyTools::printTree(tree2);

    return 0;
}

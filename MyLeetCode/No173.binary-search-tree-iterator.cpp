//
// Created by eisenhao on 2022/6/18.
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

class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        flatten(root);

        // Create a not existed head
        TreeNode* head = new TreeNode(-1);
        head->right = node;
        node = head;
        iterator = node;
    }

    int next() {
        iterator = iterator->right;
        return iterator->val;
    }

    bool hasNext() {
        return iterator->right != nullptr;
    }

private:
    TreeNode* prePtr = nullptr;
    TreeNode* node = nullptr;
    TreeNode* iterator = nullptr;

    // 中序：左 根 右
    // 逆中序：右 根 左
    void flatten(TreeNode* root) {
        if (!root) {
            return;
        }

        flatten(root->right);

        node = new TreeNode(root->val);
        node->right = prePtr;
        prePtr = node;

        flatten(root->left);
    }
};

int main(void) {
    TreeNode* tree1 = new TreeNode(7);
    tree1->left = new TreeNode(3);
    tree1->right = new TreeNode(15);
    tree1->right->left = new TreeNode(9);
    tree1->right->right = new TreeNode(20);

    BSTIterator bSTIterator = BSTIterator(tree1);

    cout << bSTIterator.next() << endl;
    cout << bSTIterator.next() << endl;
    cout << bSTIterator.hasNext() << endl;
    cout << bSTIterator.next() << endl;
    cout << bSTIterator.hasNext() << endl;
    cout << bSTIterator.next() << endl;
    cout << bSTIterator.hasNext() << endl;
    cout << bSTIterator.next() << endl;
    cout << bSTIterator.hasNext() << endl;

    return 0;
}

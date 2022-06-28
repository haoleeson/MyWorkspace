#include <iostream>
#include <set>

using namespace std;
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        target = k;
        traverse(root);
        return res;
    }

private:
    set<int> s;
    int target;
    bool res = false;
    bool finish = false;
    void traverse(TreeNode* root) {
        if (!root) {
            return;
        }

        traverse(root->left);

        if (finish) {
            return;
        }

        if (s.count(root->val)) {
            res = true;
            finish = true;
        } else {
            s.insert(target - root->val);
        }

        traverse(root->right);
    }
};

int main(void) {
    Solution solution1;
    TreeNode* tree1 = new TreeNode(5);
    tree1->left = new TreeNode(3);
    tree1->right = new TreeNode(6);
    tree1->left->left = new TreeNode(2);
    tree1->left->right = new TreeNode(4);
    tree1->right->right = new TreeNode(7);
    int k1 = 9;
    bool res1 = solution1.findTarget(tree1, k1);
    cout << res1 << endl;

    int k2 = 28;
    Solution solution2;
    bool res2 = solution2.findTarget(tree1, k2);
    cout << res2 << endl;

    Solution solution3;
    TreeNode* tree3 = new TreeNode(2);
    tree3->left = new TreeNode(0);
    tree3->right = new TreeNode(3);
    tree3->left->left = new TreeNode(-4);
    tree3->left->right = new TreeNode(1);
    int k3 = -1;
    bool res3 = solution3.findTarget(tree3, k3);
    cout << res3 << endl;

    Solution solution4;
    TreeNode* tree4 = new TreeNode(0);
    tree4->left = new TreeNode(-3);
    tree4->right = new TreeNode(2);
    tree4->left->left = new TreeNode(-4);
    tree4->right->left = new TreeNode(1);
    int k4 = 1;
    bool res4 = solution4.findTarget(tree4, k4);
    cout << res4 << endl;

    return 0;
}

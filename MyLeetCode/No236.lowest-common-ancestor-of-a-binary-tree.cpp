//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include<set>
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
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        pVal = p->val;
        qVal = q->val;
        traverse(root);
        return res;
    }

private:
    struct ExistPQ {
        bool hasP = false;
        bool hasQ = false;
    };

    TreeNode* res = nullptr;
    int pVal, qVal;


    ExistPQ traverse(TreeNode* root) {
        if (!root) {
            return {false, false};
        }

        ExistPQ lE = traverse(root->left);
        ExistPQ rE = traverse(root->right);

        // 汇总子树是否包含 {P, Q}
        ExistPQ existPq;
        existPq.hasP = (lE.hasP || rE.hasP || root->val == pVal);
        existPq.hasQ = (lE.hasQ || rE.hasQ || root->val == qVal);

        if (!res) {
            if (existPq.hasP && existPq.hasQ) {
                res = root;
            }
        }

        return existPq;
    }
};


// Over runtime
class Solution0 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        pVal = p->val;
        qVal = q->val;
        traverse(root);
        return res;
    }

private:
    TreeNode* res = nullptr;
    int pVal, qVal;

    set<int> traverse(TreeNode* root) {
        if (!root) {
            return {};
        }

        set<int> lS = traverse(root->left);
        set<int> rS = traverse(root->right);

        // 汇总子树元素
        lS.insert(root->val);
        lS.insert(rS.begin(), rS.end());

        if (!res) {
            if (lS.count(pVal) && lS.count(qVal)) {
                res = root;
            }
        }

        return lS;
    }
};

int main(void) {
    TreeNode* tree1 = new TreeNode(3);
    tree1->left = new TreeNode(5);
    tree1->right = new TreeNode(1);
    tree1->left->left = new TreeNode(6);
    tree1->left->right = new TreeNode(2);
    tree1->right->left = new TreeNode(0);
    tree1->right->right = new TreeNode(8);
    tree1->left->right->left = new TreeNode(7);
    tree1->left->right->right = new TreeNode(4);

    Solution solution1;
    cout << solution1.lowestCommonAncestor(tree1, tree1->left, tree1->right)->val << endl;


    Solution solution2;
    cout << solution2.lowestCommonAncestor(tree1, tree1->left, tree1->left->right->right)->val << endl;

    TreeNode* tree3 = new TreeNode(1);
    tree3->left = new TreeNode(2);
    Solution solution3;
    cout << solution3.lowestCommonAncestor(tree3, tree3, tree3->left)->val << endl;

    return 0;
}

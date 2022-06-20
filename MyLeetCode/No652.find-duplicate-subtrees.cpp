//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include<unordered_map>
#include<set>
#include "myTools.h"
using namespace std;

// 后序 + 前缀和
class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        traverse(root);
        vector<TreeNode*> res(s.begin(), s.end());
        return res;
    }

private:
    set<TreeNode*> s;
    set<string> pathRec;
    string DIMMER = ",";
    string NULL_STR = "X";

    unordered_map<string, TreeNode*> m;
    string traverse(TreeNode* root) {
        if (!root) {
            return NULL_STR;
        }

        string leftStr = traverse(root->left);
        string rightStr = traverse(root->right);

        string nodeStr = leftStr + DIMMER + rightStr + DIMMER + to_string(root->val);

        if (m.count(nodeStr) && !pathRec.count(nodeStr)) {
            s.insert(root);
            pathRec.insert(nodeStr);
        } else {
            m[nodeStr] = root;
        }

        return nodeStr;
    }
};

int main(void) {

    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(3);
    tree1->left->left = new TreeNode(4);
    tree1->right->left = new TreeNode(2);
    tree1->right->right = new TreeNode(4);
    tree1->right->left->left = new TreeNode(4);
    Solution solution1;
    vector<TreeNode*> res1 = solution1.findDuplicateSubtrees(tree1);
    cout << "res1( " << res1.size() << " ):" << endl;
    for (auto& t : res1) {
        MyTools::printTree(t);
    }


    TreeNode* tree2 = new TreeNode(2);
    tree2->left = new TreeNode(1);
    tree2->right = new TreeNode(1);
    Solution solution2;
    vector<TreeNode*> res2 = solution2.findDuplicateSubtrees(tree2);
    cout << "res2( " << res2.size() << " ):" << endl;
    for (auto& t : res2) {
        MyTools::printTree(t);
    }

    return 0;
}

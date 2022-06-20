//
// Created by eisenhao on 2022/6/20.
//

#include<iostream>
#include<vector>
#include<unordered_map>
#include "myTools.h"
using namespace std;

class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> res;

        traverse(root);

        // 遍历找最大出现次数的子树元素和集合
//        unordered_map<int, int>::iterator it;
//        for (it = m.begin(); it != m.end(); it++) {
//            if (it->second == maxTimes) {
//                res.push_back(it->first);
//            }
//        }
        // c++17
        for (auto &[s, c]: m) {
            if (c == maxTimes) {
                res.push_back(s);
            }
        }

        return res;
    }

private:
    unordered_map<int, int> m;
    int maxTimes = INT_MIN;

    int traverse(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int subTreeSum = traverse(root->left) + traverse(root->right) + root->val;

        ++m[subTreeSum];
        if (m[subTreeSum] > maxTimes) {
            maxTimes = m[subTreeSum];
        }

        return subTreeSum;
    }
};

int main(void) {
    TreeNode* tree1 = new TreeNode(5);
    tree1->left = new TreeNode(2);
    tree1->right = new TreeNode(-3);
    Solution solution1;
    vector<int> res = solution1.findFrequentTreeSum(tree1);
    MyTools::printVec(res);

    TreeNode* tree2 = new TreeNode(5);
    tree2->left = new TreeNode(2);
    tree2->right = new TreeNode(-5);
    Solution solution2;
    vector<int> res2 = solution2.findFrequentTreeSum(tree2);
    MyTools::printVec(res2);


    return 0;
}

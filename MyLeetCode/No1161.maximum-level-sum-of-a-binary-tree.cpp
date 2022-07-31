#include <iostream>

#include "myTools.h"

using namespace std;

// 思路：层序遍历
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        int recMaxSumLevel = 0, recMaxSum = INT_MIN, level = 1;

        vector<TreeNode*> nodes;
        int thisLevelCnt = 0, nextLevelCnt = 0;

        // 初始：插入首层根节点
        nodes.push_back(root);
        thisLevelCnt = 1;

        // 逐层遍历
        while (thisLevelCnt) {
            int tmpSum = 0;
            nextLevelCnt = 0;

            // 遍历此层各节点
            for (int i = 0; i < thisLevelCnt; ++i) {
                tmpSum += nodes[i]->val;

                // 顺序添加下一层节点
                if (nodes[i]->left) {
                    nodes.push_back(nodes[i]->left);
                    ++nextLevelCnt;
                }
                if (nodes[i]->right) {
                    nodes.push_back(nodes[i]->right);
                    ++nextLevelCnt;
                }
            }

            // 判断本层元素和是否最大
            if (tmpSum > recMaxSum) {
                recMaxSumLevel = level;
                recMaxSum = tmpSum;
            }

            // 删除这一层
            nodes.erase(nodes.begin(), nodes.begin() + thisLevelCnt);
            // 赋值下一层节点数
            thisLevelCnt = nextLevelCnt;
            // 层数自增
            ++level;
        }

        return recMaxSumLevel;
    }
};

int main(void) {
    Solution solution;

    TreeNode* tree1 = new TreeNode(1);
    tree1->left = new TreeNode(7);
    tree1->right = new TreeNode(0);
    tree1->left->left = new TreeNode(7);
    tree1->left->right = new TreeNode(-8);
    int res1 = solution.maxLevelSum(tree1);
    cout << res1 << endl;

    TreeNode* tree2 = new TreeNode(989);
    tree2->right = new TreeNode(10250);
    tree2->right->left = new TreeNode(98693);
    tree2->right->right = new TreeNode(-89388);
    tree2->right->right->right = new TreeNode(-32127);
    int res2 = solution.maxLevelSum(tree2);
    cout << res2 << endl;

    return 0;
}
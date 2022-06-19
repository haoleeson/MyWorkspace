//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include<unordered_map>
#include "myTools.h"
using namespace std;

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        // key是前缀和, value是大小为key的前缀和出现的次数
        unordered_map<long, int> prefixSumCount;
        // 前缀和为0的一条路径
        prefixSumCount[0] = 1;
        // 前缀和的递归回溯思路
        return recursionPathSum(root, prefixSumCount, targetSum, 0);
    }

    /**
     * 前缀和的递归回溯思路
     * 从当前节点反推到根节点(反推比较好理解，正向其实也只有一条)，有且仅有一条路径，因为这是一棵树
     * 如果此前有和为currSum-target,而当前的和又为currSum,两者的差就肯定为target了
     * 所以前缀和对于当前路径来说是唯一的，当前记录的前缀和，在回溯结束，回到本层时去除，保证其不影响其他分支的结果
     */
private:
    int recursionPathSum(TreeNode* node, unordered_map<long, int>& prefixSumCount, long target, long currSum) {
        // 1.递归终止条件
        if (!node) {
            return 0;
        }

        // 2.本层要做的事情
        int res = 0;
        // 当前路径上的和
        currSum += node->val;

        //---核心代码
        // 看看root到当前节点这条路上是否存在节点前缀和加target为currSum的路径
        // 当前节点->root节点反推，有且仅有一条路径，如果此前有和为currSum-target,而当前的和又为currSum,两者的差就肯定为target了
        // currSum-target相当于找路径的起点，起点的sum+target=currSum，当前点到起点的距离就是target

        if (prefixSumCount.count(currSum - target)) {
            res += prefixSumCount[currSum - target];
        }
        // 更新路径上当前节点前缀和的个数
        prefixSumCount[currSum]++;
        //---核心代码

        // 3.进入下一层
        res += recursionPathSum(node->left, prefixSumCount, target, currSum);
        res += recursionPathSum(node->right, prefixSumCount, target, currSum);

        // 4.回到本层，恢复状态，去除当前节点的前缀和数量
        prefixSumCount[currSum]--;
        return res;
    }
};


class Solution0Err {
public:
    int pathSum(TreeNode* root, int targetSum) {
        originTarget = targetSum;
        traverse(root, targetSum);
        return res;
    }

private:
    int res = 0;
    int originTarget = 0;
    void traverse(TreeNode* root, int targetSum) {
        if (!root) {
            return;
        }

        if (root->val == targetSum) {
            ++res;
        }

        // with root
        traverse(root->left, targetSum - root->val);
        traverse(root->right, targetSum - root->val);

        // without root
        traverse(root->left, originTarget);
        traverse(root->right, originTarget);
    }
};

int main(void) {
    Solution solution1;
    TreeNode* tree1 = new TreeNode(10);
    tree1->left = new TreeNode(5);
    tree1->right = new TreeNode(-3);
    tree1->left->left = new TreeNode(3);
    tree1->left->right = new TreeNode(2);
    tree1->right->right = new TreeNode(11);
    tree1->left->left->left = new TreeNode(3);
    tree1->left->left->right = new TreeNode(-2);
    tree1->left->right->right = new TreeNode(1);
    int res1 = solution1.pathSum(tree1, 8);
    cout << res1 << endl;

    Solution solution2;
    TreeNode* tree2 = new TreeNode(5);
    tree2->left = new TreeNode(4);
    tree2->right = new TreeNode(8);
    tree2->left->left = new TreeNode(11);
    tree2->right->left = new TreeNode(13);
    tree2->right->right = new TreeNode(4);
    tree2->left->left->left = new TreeNode(7);
    tree2->left->left->right = new TreeNode(2);
    tree2->right->right->left = new TreeNode(5);
    tree2->right->right->right = new TreeNode(1);
    int res2 = solution2.pathSum(tree2, 22);
    cout << res2 << endl;



    return 0;
}

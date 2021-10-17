#include <iostream>
#include <vector>
using namespace std;

/**
 * No637. 二叉树的层平均值
 * 给定一个非空二叉树, 返回一个由每层节点平均值组成的数组。

示例 1：
输入：
    3
   / \
  9  20
    /  \
   15   7
输出：[3, 14.5, 11]

解释：
第 0 层的平均值是 3 ,  第1层是 14.5 , 第2层是 11 。因此返回 [3, 14.5, 11] 。

提示：
节点值的范围在32位有符号整数范围内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/average-of-levels-in-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<TreeNode* > nodeQueue;
        vector<TreeNode* > nextNodeQueue;
        vector<double> ans;
        int count, nextCount;
        long sum;
        if (root == nullptr) {
            return ans;
        }

        nodeQueue.push_back(root);
        count = 1;

        // 逐层计算
        while (count) {
            sum = 0;
            nextCount = 0;
            for (int i = 0; i < count; ++i) {
                sum += nodeQueue[i]->val;
                if (nodeQueue[i]->left != nullptr) {
                    nextNodeQueue.push_back(nodeQueue[i]->left);
                    ++nextCount;
                }
                if (nodeQueue[i]->right != nullptr) {
                    nextNodeQueue.push_back(nodeQueue[i]->right);
                    ++nextCount;
                }
            }

            ans.push_back((double)sum / (double)count);
            nodeQueue.clear();
            vector<TreeNode* > ().swap(nodeQueue);
            nodeQueue.swap(nextNodeQueue);
            count = nextCount;
        }

        return ans;
    }
};

template<typename T>
void printVec2D(vector<T> vec) {
    int size = vec.size();
    cout << "[";
    if (size > 0) {
        cout << vec[0];
        for (int i = 1; i < size; ++i) {
            cout << ", " << vec[i];
        }
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<double> result = solution.averageOfLevels(root);
    printVec2D(result);
    return 0;
}
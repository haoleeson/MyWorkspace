
#include<iostream>
using namespace std;

//路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
//路径和 是路径中各节点值的总和。
//给你一个二叉树的根节点 root ，返回其 最大路径和 。

//树中节点数目范围是 [1, 3 * 104]
//-1000 <= Node.val <= 1000

//示例1：
//输入：root = [1,2,3]
//输出：6
//解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6

//示例2：
//输入：root = [-10,9,20,null,null,15,7]
//输出：42
//解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42

//Definition for a binary tree node.
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
    int maxPathSum(TreeNode* root) {
        countMaxPathSum(root);
        return res;
    }

private:
    int res = INT_MIN;
    int countMaxPathSum(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftVal = max(0, countMaxPathSum(root->left));
        int rightVal = max(0, countMaxPathSum(root->right));
        res = max(res, leftVal + rightVal + root->val);
        return root->val + max(leftVal, rightVal);
    }
};



int main(void) {
    Solution solution;

    TreeNode* tree1L = new TreeNode(2);
    TreeNode* tree1R = new TreeNode(3);
    TreeNode* tree1 = new TreeNode(1, tree1L, tree1R);
    
    TreeNode* tree2RL = new TreeNode(15);
    TreeNode* tree2RR = new TreeNode(7);
    TreeNode* tree2R = new TreeNode(20, tree2RL, tree2RR);
    TreeNode* tree2L = new TreeNode(9);
    TreeNode* tree2 = new TreeNode(-10, tree2L, tree2R);
    

    cout << endl << "tree1:" << endl;
    cout << solution.maxPathSum(tree1) << endl;



    cout << endl << "tree2:" << endl;
    cout << solution.maxPathSum(tree2) << endl;

    return 0;
}
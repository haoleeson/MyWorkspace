/** 题目描述：
 * 108. 将有序数组转换为二叉搜索树
 * 将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:

给定有序数组: [-10,-3,0,5,9],

一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190314
 * */
#include <iostream>
#include <vector>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        //特殊之判断，数组位0
        if (nums.size() == 0){
            return NULL;
        }
        TreeNode* root = new TreeNode(nums[0]);
        root = sortedSubArray(nums, 0, nums.size()-1);
        return root;
    }

    //分治
    TreeNode* sortedSubArray(vector<int>& nums, int left, int right) {
        if( right - left < 0) {
            return NULL;
        } else if (right - left == 0) {
            return new TreeNode(nums[left]);
        }
        int mid = left + (right - left) / 2; //计算中间节下标
        TreeNode* tmpNode = new TreeNode(nums[mid]);//新建中间节点
        tmpNode->left = sortedSubArray(nums, left, mid-1);//分治1
        tmpNode->right = sortedSubArray(nums, mid+1, right);//分治2
        return tmpNode;
    }

};



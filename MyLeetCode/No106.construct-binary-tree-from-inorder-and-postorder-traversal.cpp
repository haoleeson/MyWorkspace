#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No106. 从中序与后序遍历序列构造二叉树 （分治）
 * 根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出
中序遍历 inorder =[9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 解题思路：分治（找根后分左右子树）
 * 中序 inorder ： 左 根 右
 * 后序 postorder ： 左 右 根
 */
class Solution {
public:
    TreeNode* dc(vector<int>& inorder, vector<int>& postorder, int indexIl, int indexIr, int indexPl, int indexPr) {
        if (indexPr <= indexPl) {
            return indexPr == indexPl ? new TreeNode(postorder[indexPl]) : nullptr;
        }
        // 在后序中找根，即遍历的最后一个元素为根
        int rootVal = postorder[indexPr];
        // 在中序中找根所在下标
        int findIIndex = indexIl;
        while (findIIndex <= indexIr && inorder[findIIndex] != rootVal) {
            ++findIIndex;
        }
        int leftNums = findIIndex - indexIl;
        TreeNode* root = new TreeNode(rootVal);
        root->left = dc(inorder, postorder, indexIl, findIIndex - 1, indexPl, indexPl + leftNums - 1);
        root->right = dc(inorder, postorder, findIIndex + 1, indexIr, indexPl + leftNums, indexPr - 1);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int iSize = inorder.size(), pSize = postorder.size();
        return dc(inorder, postorder, 0, iSize - 1, 0, pSize - 1);
    }
};

int main() {
    Solution solution;
    int arr1[] = {9,3,15,20,7};
    int arr2[] = {9,15,7,20,3};
    vector<int> inorder(arr1, arr1 + sizeof(arr1) / sizeof(int));
    vector<int> postorder(arr2, arr2 + sizeof(arr2) / sizeof(int));
    TreeNode* root = solution.buildTree(inorder, postorder);
    MyTools::printTree(root);
    return 0;
}
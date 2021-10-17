#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No235. 二叉搜索树的最近公共祖先
 * 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉搜索树: root =[6,2,8,0,4,7,9,null,null,3,5]

           6
        /      \
     2           8
  /    \      /     \
 0      4    7       9
       / \
      3   5
      
示例 1:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。
示例 2:

输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。


说明:

所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉搜索树中。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class Solution {
public:
    /**
     * 查找从根节点到 targetNode 的唯一路径
     * @param path
     * @param node
     * @param targetNode
     * @return
     */
    bool dfs(vector<TreeNode*>& path, TreeNode* node,  TreeNode* targetNode) {
        if (node) {
            if (node == targetNode) {
                path.insert(path.begin(), node);
                return true;
            }
            if (dfs(path, node->left, targetNode)) {
                path.insert(path.begin(), node);
                return true;
            }
            if (dfs(path, node->right, targetNode)) {
                path.insert(path.begin(), node);
                return true;
            }
        }
        return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> pathP;
        dfs(pathP, root, p);
        vector<TreeNode*> pathQ;
        dfs(pathQ, root, q);

        int i = 0, lenP = pathP.size(), lenQ = pathQ.size();
        while (i < lenP && i < lenQ && pathP[i] == pathQ[i]) {
            ++i;
        }
        return pathP[--i];
    }
};

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);

    TreeNode* p = root->left;
    TreeNode* q = root->right;

    TreeNode* result = solution.lowestCommonAncestor(root, p, q);
    cout << result->val << endl;
    return 0;
}
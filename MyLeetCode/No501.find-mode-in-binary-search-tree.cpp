#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No501. 二叉搜索树中的众数 （中序遍历）
 * 给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素）。
 * 假定 BST 有如下定义：
 * 结点左子树中所含结点的值小于等于当前结点的值
 * 结点右子树中所含结点的值大于等于当前结点的值
 * 左子树和右子树都是二叉搜索树

例如：
给定 BST [1,null,2,2],
   1
    \
     2
    /
   2
返回[2].

提示：如果众数超过1个，不需考虑输出顺序

进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-mode-in-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class Solution {
public:
    vector<int> m_ans;
    int m_curTimes = 0, m_maxTimes = 0;
    int* preVal = nullptr;

    /**
     * 中序遍历
     * @param root
     * @return
     */
    void midOrder(TreeNode* root) {
        if (!root) {
            return;
        }
        // 左
        midOrder(root->left);

        // 中
        m_curTimes = (preVal && *preVal == root->val) ? m_curTimes + 1 : 1;
        if (m_curTimes > m_maxTimes) {
            m_maxTimes = m_curTimes;
            m_ans.clear();
            m_ans.push_back(root->val);
        } else if (m_curTimes == m_maxTimes) {
            m_ans.push_back(root->val);
        }
        preVal = &root->val;

        // 右
        midOrder(root->right);
    }

    vector<int> findMode(TreeNode* root) {
        midOrder(root);
        return m_ans;
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
    root->left->right->left = new TreeNode(2);
    root->left->right->right = new TreeNode(6);
    vector<int> result = solution.findMode(root);
    MyTools::printVec(result);
    return 0;
}
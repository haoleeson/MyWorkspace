#include <iostream>
#include <vector>
using namespace std;

/**
 * No257. 二叉树的所有路径（dfs）
 * 给定一个二叉树，返回所有从根节点到叶子节点的路径。
 * 说明：叶子节点是指没有子节点的节点。

示例
输入:
   1
 /   \
2     3
 \
  5
输出: ["1->2->5", "1->3"]
解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<string> m_ans;
    void dfs(TreeNode* node, string preStr) {
        if (node == nullptr) {
            return;
        }
        preStr += to_string(node->val);
        if (node->left == nullptr && node->right == nullptr) {
            m_ans.push_back(preStr);
        } else {
            preStr += "->";
            dfs(node->left, preStr);
            dfs(node->right, preStr);
        }
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        dfs(root, "");
        return m_ans;
    }
};

void printVec(vector<string> vec) {
    int size = vec.size();
    cout << "[";
    if (size > 0) {
        cout << "\"" << vec[0] << "\"";
        for (int i = 1; i < size; ++i) {
            cout << ", \"" << vec[i] << "\"";
        }
    }
    cout << "]" << endl;
    return;
}

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    vector<string> ans = solution.binaryTreePaths(root);
    printVec(ans);
    return 0;
}

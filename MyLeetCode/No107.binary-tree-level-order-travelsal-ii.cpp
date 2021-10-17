#include <iostream>
#include <vector>
using namespace std;

/**
 * No107. 二叉树的层次遍历 II
 * 给定一个二叉树，返回其节点值自底向上的层次遍历。
 * （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

例如：
给定二叉树 [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其自底向上的层次遍历为：

[
  [15,7],
  [9,20],
  [3]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        vector<TreeNode*> nodes;
        int count = 0, countNext = 0;

        if (root == nullptr) {
            return ans;
        }
        nodes.push_back(root);
        count = 1;

        // 逐层遍历
        while (count) {
            countNext = 0;
            vector<int> tmp;
            for (int i = 0; i < count; ++i) {
                tmp.push_back(nodes[i]->val);
                if (nodes[i]->left != nullptr) {
                    nodes.push_back(nodes[i]->left);
                    ++countNext;
                }
                if (nodes[i]->right != nullptr) {
                    nodes.push_back(nodes[i]->right);
                    ++countNext;
                }
            }
            // 删除这一层
            nodes.erase(nodes.begin(), nodes.begin() + count);
            // 逆序插入结果vector中
            ans.insert(ans.begin(), tmp);
            // 清空tmp
            vector<int> ().swap(tmp);
            count = countNext;
        }
        return ans;
    }
};

class SolutionOld {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result; //存返回结果
        if (root==NULL) {
            return result;
        }
        vector<vector<TreeNode*>> P;//正序存每一层节点指针
        vector<TreeNode*> head;
        int level_iterator = 0;//当前层数
        head.push_back(root); // 第一层存根节点指针
        P.push_back(head);
        //顺序遍历二叉树的每一层
        while (true) {
            vector<TreeNode*> tmp; //用于存放当前层节点的容器
            //遍历当前层所有节点的子节点，并存于tmp
            for (int j=0; j<P[level_iterator].size(); j++) {
                if (P[level_iterator][j]->left != NULL) {
                    tmp.push_back(P[level_iterator][j]->left);
                }
                if (P[level_iterator][j]->right != NULL) {
                    tmp.push_back(P[level_iterator][j]->right);
                }
            }
            if (tmp.size() == 0) {
                break;
            }
            P.push_back(tmp);//将下一层的节点附加到P
            level_iterator++;
        }
        //逆序遍历上衣步存的节点
        for (int i=P.size()-1; i>-1; i--) {
            vector<int> tmp;//用于存放当前层节点的值的容器
            for (int j=0; j<P[i].size(); j++) {
                tmp.push_back(P[i][j]->val);
            }
            result.push_back(tmp);
        }
        return result;
    }
};


template <typename T>
void printVec2D(vector<vector<T>>& vec2D) {
    int size = vec2D.size();
    cout << "[" << endl;
    for (int i = 0; i < size - 1; ++i) {
        cout << "    [";
        for (int j = 0; j < vec2D[i].size() - 1; ++j) {
            cout << vec2D[i][j] << ",";
        }
        cout << vec2D[i][vec2D[i].size() - 1] << "]," << endl;
    }
    cout << "    [";
    for (int j = 0; j < vec2D[size - 1].size() - 1; ++j) {
        cout << vec2D[size - 1][j] << ",";
    }
    cout << vec2D[size - 1][vec2D[size - 1].size() - 1] << "]" << endl;
    cout << "]" << endl;
}

int main() {
    Solution solution;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    vector<vector<int>> result = solution.levelOrderBottom(root);
    printVec2D(result);
    return 0;
}
#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No117. 填充每个节点的下一个右侧节点指针 II (层序遍历)
 * 给定一个二叉树

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
初始状态下，所有next 指针都被设置为 NULL。


进阶：
你只能使用常量级额外空间。
使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。

示例：
输入：root = [1,2,3,4,5,null,7]
输出：[1,#,2,3,#,4,5,7,#]
解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。


提示：
树中的节点数小于 6000
-100<= node.val <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        int count = 0, nextCount = 0;
        vector<Node* > vec;
        vector<Node* > nextVec;
        if (root) {
            vec.push_back(root);
            count = 1;
        }

        // 层序遍历（每层从右至左）
        while (count) {
            for (int i = 0; i < count; ++i) {
                if (vec[i]->right) {
                    if (nextCount) {
                        vec[i]->right->next = nextVec[nextCount - 1];
                    }
                    nextVec.push_back(vec[i]->right);
                    ++nextCount;
                }
                if (vec[i]->left) {
                    if (nextCount) {
                        vec[i]->left->next = nextVec[nextCount - 1];
                    }
                    nextVec.push_back(vec[i]->left);
                    ++nextCount;
                }
            }
            vec.clear();
            vec.swap(nextVec);
            nextVec.clear();
            count = nextCount;
            nextCount = 0;
        }
        return root;
    }
};

int main() {
    Solution solution;
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(7);

    Node* result = solution.connect(root);
    return 0;
}
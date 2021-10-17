/**
 * No116. 填充每个节点的下一个右侧节点指针 (层序遍历)
 * 给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。
初始状态下，所有next 指针都被设置为 NULL。



示例：
输入：{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":{"$id":"6","left":null,"next":null,"right":null,"val":6},"next":null,"right":{"$id":"7","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}
输出：{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":{"$id":"5","left":null,"next":{"$id":"6","left":null,"next":null,"right":null,"val":7},"right":null,"val":6},"right":null,"val":5},"right":null,"val":4},"next":{"$id":"7","left":{"$ref":"5"},"next":null,"right":{"$ref":"6"},"val":3},"right":{"$ref":"4"},"val":2},"next":null,"right":{"$ref":"7"},"val":1}

解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include "myTools.h"
using namespace std;

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
        if (!root) {
            return root;
        }
        int thisCnt = 1, nextCnt = 0;
        vector<Node* > thisLevel(1, root);
        vector<Node* > nextLevel(2, nullptr);
        // 层序遍历（从右至左）
        while (thisCnt > 0) {
            for (int i = 0; i < thisCnt; ++i) {
                if (thisLevel[i]->right) {
                    // next指针指向前一个指针（若存在前一个指针）
                    if (nextCnt > 0) {
                        thisLevel[i]->right->next = nextLevel[nextCnt - 1];
                    }
                    nextLevel[nextCnt] = thisLevel[i]->right;
                    ++nextCnt;
                }
                if (thisLevel[i]->left) {
                    // next指针指向前一个指针（若存在前一个指针）
                    if (nextCnt > 0) {
                        thisLevel[i]->left->next = nextLevel[nextCnt - 1];
                    }
                    nextLevel[nextCnt] = thisLevel[i]->left;
                    ++nextCnt;
                }
            }

            thisCnt = nextCnt;
            // 交换thisLevel与nextLevel，及初始化nextLevel
            if (nextCnt > 0) {
                thisLevel.swap(nextLevel);
                nextLevel.resize(2 * nextCnt);
            }
            nextCnt = 0;
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
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root = solution.connect(root);
    return 0;
}

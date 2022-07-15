#include <iostream>
#include <unordered_map>

#include "myTools.h"

using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

// 思路：递归 + 分治
// 链接：https://leetcode.cn/problems/logical-or-of-two-binary-grids-represented-as-quad-trees/solution/si-cha-shu-jiao-ji-by-leetcode-solution-wy1u/
class Solution {
public:
    Node* intersect(Node* quadTree1, Node* quadTree2) {
        // quadTree1 为叶子节点
        if (quadTree1->isLeaf) {
            // 若值为 true，或结果为 true
            if (quadTree1->val) {
                return new Node(true, true);
            }
            // 否则为 quadTree2 值
            return new Node(quadTree2->val, quadTree2->isLeaf, quadTree2->topLeft, quadTree2->topRight,
                            quadTree2->bottomLeft, quadTree2->bottomRight);
        }

        // quadTree1 为中间节点，quadTree2 为叶子节点
        if (quadTree2->isLeaf) {
            return intersect(quadTree2, quadTree1);
        }

        // 均为中间节点，四个子节点方向 递归（“分”）
        Node* o1 = intersect(quadTree1->topLeft, quadTree2->topLeft);
        Node* o2 = intersect(quadTree1->topRight, quadTree2->topRight);
        Node* o3 = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
        Node* o4 = intersect(quadTree1->bottomRight, quadTree2->bottomRight);
        // “治”：值相同
        if (o1->isLeaf && o2->isLeaf && o3->isLeaf && o4->isLeaf && o1->val == o2->val && o1->val == o3->val &&
            o1->val == o4->val) {
            return new Node(o1->val, true);
        }
        // “治”：值不同
        return new Node(false, false, o1, o2, o3, o4);
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;
    Node* quadTree1 =
        new Node(true, false, new Node(true, true), new Node(true, true), new Node(false, true), new Node(false, true));

    Node* quadTree2_topRight = new Node(true, false, new Node(false, true), new Node(false, true), new Node(true, true),
                                        new Node(false, true));
    Node* quadTree2 =
        new Node(true, false, new Node(true, true), quadTree2_topRight, new Node(true, true), new Node(false, true));

    Node* res = solution.intersect(quadTree1, quadTree2);

    return 0;
}

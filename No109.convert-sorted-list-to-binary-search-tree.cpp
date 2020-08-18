#include <iostream>
using namespace std;
/**
 * No109. 有序链表转换二叉搜索树
 * 给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
 * 本题中，一个高度平衡二叉树是指一个二叉树每个节点的左右两个子树的高度差的绝对值不超过 1。

示例:
给定的有序链表： [-10, -3, 0, 5, 9],
一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：
      0
     / \
   -3   9
   /   /
 -10  5

*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 解题思路：中位数作为根节点(快慢指针) + 分治
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return buildBstTree(head, nullptr);
    }

private:
    /**
     * 找到有序链表的中位数作为根节点（快慢指针）
     * @param startNode
     * @param endNode
     * @return
     */
    ListNode* getMiddleNode(ListNode* startNode, ListNode* endNode) {
        ListNode* slowPtr = startNode;
        ListNode* fastPtr = startNode;

        while (fastPtr != endNode && fastPtr->next != endNode) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }
        return slowPtr;
    }

    /**
     * 分治法构造二叉搜索树
     * @param head
     * @param leftNode
     * @param rightNode
     * @return
     */
    TreeNode* buildBstTree(ListNode* leftNode, ListNode* rightNode) {
        if (leftNode == rightNode) {
            return nullptr;
        }
        ListNode* middleNode = getMiddleNode(leftNode, rightNode);
        TreeNode* root = new TreeNode(middleNode->val);
        root->left = buildBstTree(leftNode, middleNode);
        root->right = buildBstTree(middleNode->next, rightNode);
        return root;
    }
};

/**
 * 官方题解思路： 分治 + 中序遍历
 * 原理：构造出的二叉搜索树的中序遍历结果就是链表本身
 * 方法：利用分治法构造中序遍历
 */
class Solution2 {
public:
    // 取链表长度
    int getLength(ListNode* head) {
        int ret = 0;
        for (; head != nullptr; ++ret, head = head->next);
        return ret;
    }

    /**
     * 利用分治法构造中序遍历（填充值）
     * @param head
     * @param left
     * @param right
     * @return
     */
    TreeNode* buildTree(ListNode*& head, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int mid = (left + right + 1) / 2;
        TreeNode* root = new TreeNode(); // 先建树后填值

        // 构造中序遍历（执行时会依次将有序链表的值按中序遍历填充到）
        // 1. 先遍历左子树
        root->left = buildTree(head, left, mid - 1);

        // 2. 再遍历根节点
        root->val = head->val;
        head = head->next;

        // 3. 最后遍历右子树
        root->right = buildTree(head, mid + 1, right);
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        int length = getLength(head);
        return buildTree(head, 0, length - 1);
    }
};


int main() {
    Solution solution;
    ListNode* head = nullptr;
    int array[] = {-10, -3, 0, 5, 9};

    head = new ListNode(array[0]);
    ListNode* listPtr = head;
    for (int i = 1; i < 5; ++i) {
        listPtr->next = new ListNode(array[i]);
        listPtr = listPtr->next;
    }

    TreeNode* bstTree = solution.sortedListToBST(head);

    return 0;
}

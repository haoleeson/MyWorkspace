/**
 * No19. 删除链表的倒数第N个节点 (迭代、递归)
 * 给定一个链表，删除链表的倒数第n个节点，并且返回链表的头结点。

示例：
给定一个链表: 1->2->3->4->5, 和 n = 2.
当删除了倒数第二个节点后，链表变为 1->2->3->5.

说明：
给定的 n 保证是有效的。
进阶：
你能尝试使用一趟扫描实现吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include "myTools.h"
using namespace std;

/**
 * 解法2：递归1趟
 */
class Solution {
private:
    ListNode* m_head;
    bool deleteLastNNode(ListNode* node, int& n) {
        if (!node) {
            return true;
        }
        // 找到链表尾
        if (deleteLastNNode(node->next, n)) {
            if (n == 0 || node == m_head) {
                ListNode *delPtr;
                if (n == 0) {
                    delPtr = node->next;
                    node->next = node->next->next;
                } else {
                    // 删除头节点
                    delPtr = m_head;
                    m_head = m_head->next;
                }
                delete delPtr;
                return false;
            }
            --n;
            return true;
        }
        return false;
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        m_head = head;
        deleteLastNNode(head, n);
        return m_head;
    }
};

/**
 * 解法1：迭代两趟
 */
class Solution1 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) {
            return head;
        }
        ListNode *ptr = head, *delPtr;
        int length = 0;
        while (ptr) {
            ++length;
            ptr = ptr->next;
        }
        // 转换为删除正数第 length - n + 1 个节点 [1, n]
        n = length - n + 1;
        if (n == 1) {
            delPtr = head;
            head = head->next;
        } else {
            // 找到正数第 length - n + 1 个节点 的前一个节点
            ptr = head;
            for (int i = 1; i < n - 1; ++i) {
                ptr = ptr->next;
            }
            delPtr = ptr->next;
            ptr->next = ptr->next->next;
        }
        delete delPtr;
        return head;
    }
};

int main() {
    Solution solution;
    int n = 2;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head = solution.removeNthFromEnd(head, n);
    MyTools::printList(head);
    return 0;
}

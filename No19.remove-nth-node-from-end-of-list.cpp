#include <iostream>
using namespace std;

/**
 * No19. 删除链表的倒数第N个节点
 * 给定一个链表，删除链表的倒数第n个节点，并且返回链表的头结点。

示例：
给定一个链表: 1->2->3->4->5, 和 n = 2.
当删除了倒数第二个节点后，链表变为 1->2->3->5.

说明：
给定的 n保证是有效的。

进阶：
你能尝试使用一趟扫描实现吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // 思路1：统计链表总数size，转换倒数第 n 为正数第 size - n + 1
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int size = 0;
        ListNode* ptr = head;
        while (ptr != nullptr) {
            ++size;
            ptr = ptr->next;
        }
        n = size - n + 1;// 转换成删除正向的第 n 个节点
        ptr = head;
        // 删除首节点
        if (n == 1) {
            head = head->next;
            delete ptr;
        } else {
            n -= 1;
            // 找到待删除节点的前一节点
            while (--n) {
                ptr = ptr->next;
            }
            ListNode* tmp = ptr->next;
            ptr->next = tmp->next;
            delete tmp;
        }
        return head;
    }


    // 思路2：递归找到链表尾节点，在返回时删除倒数第n个节点
    ListNode* removeNthFromEnd2(ListNode* head, int n) {
        delLeftNNode(head, n);
        // 未找到倒数第n+1个节点，表明删除的是头结点
        if (m_leftN == n) {
            ListNode* ptr = head;
            head = head->next;
            delete ptr;
        }
        return head;
    }
    // 删除倒数第 n 个节点
    int m_leftN = 0;
    bool delLeftNNode(ListNode* ptr, int n) {
        // 向下递归直到尾巴节点
        if (ptr == nullptr) {
            return true;
        }
        if (delLeftNNode(ptr->next, n)) {
            // 从尾节点返回到倒数第n+1个节点
            ++m_leftN;
            // 删除倒数第n个节点
            if (m_leftN == n + 1) {
                ListNode* tmp = ptr->next;
                ptr->next = tmp->next;
                delete tmp;
                return false;
            }
            return true;
        }
        return false;
    }
};

void printList(ListNode* head) {
    ListNode* ptr = head;
    while (ptr ->next != nullptr) {
        cout << ptr->val << "->";
        ptr = ptr->next;
    }
    cout << ptr->val << endl;
}

int main() {
    Solution solution;
    int n = 2;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    printList(head);
    head = solution.removeNthFromEnd(head, n);
    printList(head);
    return 0;
}

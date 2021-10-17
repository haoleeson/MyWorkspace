/**
 * No143. 重排链表 (递归 回溯)
 * 给定一个单链表L：L0→L1→…→Ln-1→Ln ，将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例1:
给定链表 1->2->3->4, 重新排列为 1->4->2->3.

示例 2:
给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reorder-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include "myTools.h"
using namespace std;

class Solution {
    bool flag = false;
    ListNode* startPtr;
    bool revert(ListNode* node) {
        if (!node) {
            return true;
        }
        // 末尾第一个节点
        if (revert(node->next)) {
            // 尾部节点插入首部对应位置 （跳到最后一个节点的前一个节点）
            if (flag) {
                node->next->next = startPtr->next;
                startPtr->next = node->next;
                node->next = nullptr;
                startPtr = startPtr->next->next;
            } else {
                flag = true;
            }
            return startPtr != node && startPtr->next != node;
        }
        return false;
    }
public:
    void reorderList(ListNode* head) {
        startPtr = head;
        revert(head);
    }
};

int main() {
    Solution solution;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    MyTools::printList(head);
    solution.reorderList(head);
    MyTools::printList(head);
    return 0;
}

/**
 * No24. 两两交换链表中的节点
 * 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例:
给定 1->2->3->4, 你应该返回 2->1->4->3.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include "myTools.h"
using namespace std;

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // 临时创建一个头节点
        ListNode *tmpHead = new ListNode(0);
        tmpHead->next = head;
        ListNode *ptr1, *ptr2, *prePtr = tmpHead;
        // 两两节点交换
        while ((ptr1 = prePtr->next) != nullptr && (ptr2 = prePtr->next->next) != nullptr) {
            ptr1->next = ptr2->next;
            ptr2->next = ptr1;
            prePtr->next = ptr2;
            prePtr = ptr1;
        }
        // 删除临时头节点
        head = tmpHead->next;
        tmpHead->next = nullptr;
        delete tmpHead;
        return head;
    }
};

int main() {
    Solution solution;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head = solution.swapPairs(head);
    MyTools::printList(head);
    return 0;
}

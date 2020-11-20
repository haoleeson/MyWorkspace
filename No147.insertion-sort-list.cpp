/**
 * No147. 对链表进行插入排序
 * 对链表进行插入排序。
 * 插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
 * 每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。
 * 插入排序算法：
 * 插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
 * 每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
 * 重复直到所有输入数据插入完为止。


示例 1：
输入: 4->2->1->3
输出: 1->2->3->4

示例2：
输入: -1->5->3->4->0
输出: -1->0->3->4->5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insertion-sort-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head) {
            return head;
        }
        ListNode *tmpHead = new ListNode(-1), *preCurNode = head, *curNode = head->next;
        tmpHead->next = head;

        while (curNode) {
            head = tmpHead;
            // 找到小于curNode的节点
            while (head->next != curNode && head->next->val <= curNode->val) {
                head = head->next;
            }
            // 在head、head->next 之间插入 curNode
            if (head->next != curNode) {
                preCurNode->next = curNode->next;
                curNode->next = head->next;
                head->next = curNode;
            } else {
                // 已正序，未交换
                preCurNode = curNode;
            }
            curNode = preCurNode->next;
        }
        head = tmpHead->next;
        delete tmpHead;
        return head;
    }
};

int main() {
    Solution solution;
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);
    head = solution.insertionSortList(head);
    MyTools::printList(head);
    return 0;
}

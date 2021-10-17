#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No61. 旋转链表
 * 给定一个链表，旋转链表，将链表每个节点向右移动k个位置，其中k是非负数。

示例1:
输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL

示例2:
输入: 0->1->2->NULL, k = 4
输出: 2->0->1->NULL
解释:
向右旋转 1 步: 2->0->1->NULL
向右旋转 2 步: 1->2->0->NULL
向右旋转 3 步:0->1->2->NULL
向右旋转 4 步:2->0->1->NULL

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int len = 0;
        ListNode* ptr = head;
        ListNode* tail;// 记录尾节点
        while (ptr) {
            ++len;
            tail = ptr;
            ptr = ptr->next;
        }

        if (len > 1 && (k %= len) != 0) {
            // 找到第 len - k 个节点 [1,2,...]
            ptr = head;
            for (int i = 1; i < len - k; ++i) {
                ptr = ptr->next;
            }
            // 断开第 len - k 节点之后的部分，并接到头部
            tail->next = head;
            head = ptr->next;
            ptr->next = nullptr;
        }
        return head;
    }
};

int main() {
    Solution solution;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    int k = 2;

    ListNode* result = solution.rotateRight(nullptr, 0);
    MyTools::printList(result);
    return 0;
}
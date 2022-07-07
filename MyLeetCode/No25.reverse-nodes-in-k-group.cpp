#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;

        ListNode* preHead = new ListNode(-1);
        preHead->next = head;

        ListNode* prePtr = preHead;
        ListNode* curPtr = nullptr;
        ListNode* curNextPtr = nullptr;
        ListNode* lastPtr = nullptr;

        while (true) {
            // “第1个”节点
            curPtr = prePtr->next;

            // 尝试向后找到“第k个”节点
            lastPtr = prePtr;
            int i = k;
            while (lastPtr->next && i--) {
                lastPtr = lastPtr->next;
            }
            // 尾部不足 k 节点，返回 head
            if (i > 0) {
                return preHead->next;
            }

            // 链表局部 k 个节点反转
            // [prePtr] -> {curPtr -> curNext -> ... -> lastPtr}
            while (prePtr->next != lastPtr) {
                // 始终更新 curNext 为 “第1个”节点指向的 next 节点
                curNextPtr = curPtr->next;

                // 将 curNext 插入 pre 后（以实现倒序）
                // [prePtr] -> {curNext -> ... -> curPtr -> ... -> lastPtr}
                curPtr->next = curNextPtr->next;
                curNextPtr->next = prePtr->next;
                prePtr->next = curNextPtr;
            }

            // 更新 prePtr
            prePtr = curPtr;
        }
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    int arr1[] = {1, 2, 3, 4, 5};
    int k1 = 2;
    ListNode* head1 = MyTools::genListByArr(arr1, sizeof(arr1) / sizeof(int));
    ListNode* res1 = solution.reverseKGroup(head1, k1);
    MyTools::printList(res1);

    int arr2[] = {1, 2, 3, 4, 5};
    int k2 = 3;
    ListNode* head2 = MyTools::genListByArr(arr2, sizeof(arr2) / sizeof(int));
    ListNode* res2 = solution.reverseKGroup(head2, k2);
    MyTools::printList(res2);
}

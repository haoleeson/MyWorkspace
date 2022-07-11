#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* preHead = new ListNode(-1, head);
        ListNode *preCur = preHead, *curPtr, *curNext;
        int index = 0;

        // 找到序号为 left - 1 的节点
        while (preCur->next && index < left - 1) {
            ++index;
            preCur = preCur->next;
        }
        curPtr = preCur->next;
        ++index;

        // 逐一将 curPtr 后节点插入 preCur 之后 (preCur -> curPtr -> curNext -> ...)
        while (curPtr->next && index < right) {
            curNext = curPtr->next;
            curPtr->next = curNext->next;
            curNext->next = preCur->next;
            preCur->next = curNext;
            ++index;
        }

        return preHead->next;
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    int arr1[] = {1, 2, 3, 4, 5};
    int left1 = 2;
    int right1 = 4;
    ListNode* head1 = MyTools::genListByArr(arr1, sizeof(arr1) / sizeof(int));
    ListNode* res1 = solution.reverseBetween(head1, left1, right1);
    MyTools::printList(res1);

    int arr2[] = {5};
    int left2 = 1;
    int right2 = 1;
    ListNode* head2 = MyTools::genListByArr(arr2, sizeof(arr2) / sizeof(int));
    ListNode* res2 = solution.reverseBetween(head2, left2, right2);
    MyTools::printList(res2);

    return 0;
}

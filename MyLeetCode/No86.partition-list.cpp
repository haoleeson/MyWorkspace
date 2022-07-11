#include <iostream>

#include "myTools.h"

using namespace std;

// 思路：双指针
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* preHead = new ListNode(-1, head);

        ListNode* smallerPtr = preHead; // 小于 x 的节点
        ListNode* preCur = preHead;     // 遍历节点
        ListNode* tmp;

        while (preCur->next) {
            if (preCur->next->val >= x) {
                preCur = preCur->next;
                continue;
            } else if (preCur == smallerPtr) {
                preCur = preCur->next;
                smallerPtr = smallerPtr->next;
                continue;
            }

            // 将后方 小于 x 的节点移动到 smallerPtr 后方
            tmp = preCur->next;
            preCur->next = tmp->next;
            tmp->next = smallerPtr->next;
            smallerPtr->next = tmp;
            smallerPtr = smallerPtr->next;
        }

        return preHead->next;
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    int arr1[] = {1, 4, 3, 2, 5, 2};
    int x1 = 3;
    ListNode* head1 = MyTools::genListByArr(arr1, sizeof(arr1) / sizeof(int));
    ListNode* res1 = solution.partition(head1, x1);
    MyTools::printList(res1);

    int arr2[] = {2, 1};
    int x2 = 2;
    ListNode* head2 = MyTools::genListByArr(arr2, sizeof(arr2) / sizeof(int));
    ListNode* res2 = solution.partition(head2, x2);
    MyTools::printList(res2);

    return 0;
}

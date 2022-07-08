#include <algorithm>
#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* preHeadRes = new ListNode(-1);
        ListNode* ptr = preHeadRes;

        int tmp = 0;
        while (l1 || l2 || tmp) {
            if (l1) {
                tmp += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                tmp += l2->val;
                l2 = l2->next;
            }

            // 添加到结果链表
            ptr->next = new ListNode(tmp % 10);
            ptr = ptr->next;
            tmp /= 10;
        }

        return preHeadRes->next;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {7, 1, 6};
    int arr2[] = {5, 9, 2};
    ListNode* l1 = MyTools::genListByArr(arr1, 3);
    ListNode* l2 = MyTools::genListByArr(arr2, 3);
    ListNode* res1 = solution.addTwoNumbers(l1, l2);
    MyTools::printList(res1);

    return 0;
}

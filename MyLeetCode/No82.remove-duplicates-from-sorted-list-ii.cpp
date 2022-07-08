#include <algorithm>
#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* preHead = new ListNode(-1, head);
        ListNode* ptr = preHead;

        ListNode* tmp;
        while (ptr->next) {
            // 查找重复节点
            tmp = ptr->next->next;
            while (tmp && tmp->val == ptr->next->val) {
                tmp = tmp->next;
            }

            // 若有重复节点，删除重复节点
            if (tmp != ptr->next->next) {
                // TODO: 释放被删除节点内存
                //                for (ListNode *i = ptr->next, *nextPtr; i != tmp; i = nextPtr) {
                //                    nextPtr = i->next;
                //                    delete i;
                //                    i = nullptr;
                //                }

                ptr->next = tmp;
            } else {
                ptr = ptr->next;
            }
        }

        return preHead->next;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {1, 2, 3, 3, 4, 4, 5};
    ListNode* head1 = MyTools::genListByArr(arr1, sizeof(arr1) / sizeof(int));
    ListNode* res1 = solution.deleteDuplicates(head1);
    MyTools::printList(res1);

    int arr2[] = {1, 1, 1, 2, 3};
    ListNode* head2 = MyTools::genListByArr(arr2, sizeof(arr2) / sizeof(int));
    ListNode* res2 = solution.deleteDuplicates(head2);
    MyTools::printList(res2);

    return 0;
}

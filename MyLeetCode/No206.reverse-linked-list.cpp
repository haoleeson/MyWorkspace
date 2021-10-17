#include <iostream>
#include <vector>

using namespace std;

/**
 * 206. 反转链表
 * 反转一个单链表。

示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL

进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-linked-list
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
    /**
     * 方法1：迭代
     * 执行用时：12 ms
     * 内存消耗：8.4 MB
     * @param head
     * @return
     */
    ListNode* reverseList(ListNode* head) {
        if (head != nullptr) {
            ListNode* ptr = head;
            ListNode* ptrNext = head->next;
            while (ptrNext != nullptr) {
                ptr->next = ptrNext->next;
                ptrNext->next = head;
                head = ptrNext;
                ptrNext = ptr->next;
            }
        }
        return head;
    }

    //
    /**
     * 方法2：递归
     * 执行用时：12 ms
     * 内存消耗：8.4 MB
     * @param head
     * @return
     */
    ListNode* reverseList2(ListNode* head) {
        return reverseListRecursion(head, nullptr);
    }
    ListNode* reverseListRecursion(ListNode* head, ListNode* newList) {
        if (head == nullptr) {
            return newList;
        }
        ListNode* headNext = head->next;
        head->next = newList;
        newList = head;
        printList(newList);
        return reverseListRecursion(headNext, newList);
    }

    void printList(ListNode(* head)) {
        ListNode* ptr = head;
        while (ptr != nullptr) {
            cout << ptr->val << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
};



int main() {
    Solution solution;

    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    ListNode* result = solution.reverseList2(head);

    solution.printList(result);

    cout << endl;

    return 0;
}

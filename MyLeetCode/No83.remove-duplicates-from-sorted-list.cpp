/** 题目描述：
 * 83. 删除排序链表中的重复元素
 * 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

示例 1:

输入: 1->1->2
输出: 1->2
示例 2:

输入: 1->1->2->3->3
输出: 1->2->3

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190303
 * */
#include <iostream>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        //错误输入检测
        if (head == NULL) {
           return NULL;
        }
        ListNode* Ptr = head;
        ListNode* New_List = head;
        while (Ptr != NULL) {
            if (Ptr->val != New_List->val) {
                New_List->next = Ptr;
                New_List = New_List->next;
            }
            Ptr = Ptr->next;//向后遍历
        }
        New_List->next = NULL;
        return head;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    ListNode* Input = new ListNode(1);
    ListNode* p = Input;
    p->next = new ListNode(1);
    p = p->next;
    p->next = new ListNode(2);
    p = p->next;
    p->next = new ListNode(3);
    p = p->next;
    p->next = new ListNode(3);

    cout << "Input = ";
    p = Input;
    while(p->next != NULL) {
        cout << p->val << "->";
        p = p->next;
    }
    cout << p->val << endl;

    ListNode *Output = solution.deleteDuplicates(Input);

    cout << "Output = ";
    p = Output;
    while(p->next != NULL) {
        cout << p->val << "->";
        p = p->next;
    }
    cout << p->val << endl;

}

#include <iostream>
#include <vector>
using namespace std;

/**
 * No23. 合并K个升序链表
 * 给你一个链表数组，每个链表都已经按升序排列。
 * 请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

示例 2：
输入：lists = []
输出：[]

示例 3：
输入：lists = [[]]
输出：[]

提示：
k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-k-sorted-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int minVal, minIndex, size = lists.size();
        ListNode* ansHead = new ListNode(0);
        ListNode* ansEndPtr = ansHead;
        bool allNullptr;
        if (size < 2) {
            return size == 1 ? lists[0] : nullptr;
        }

        ListNode** ptrArray = new ListNode*[size];
        for (int i = 0; i < size; ++i) {
            ptrArray[i] = lists[i];
        }

        while (true) {
            minVal = 10001;
            allNullptr = true;
            // 找到最小节点
            for (int i = 0; i < size; ++i) {
                if (ptrArray[i] == nullptr) {
                    continue;
                }
                if (allNullptr) {
                    allNullptr = false;
                }
                if (ptrArray[i]->val < minVal) {
                    minVal = ptrArray[i]->val;
                    minIndex = i;
                }
            }

            if (allNullptr) {
                break;
            }
            // 取最小节点到输出链表
            ansEndPtr->next = ptrArray[minIndex];
            ptrArray[minIndex] = ptrArray[minIndex]->next;
            ansEndPtr = ansEndPtr->next;
        }

        ansEndPtr = ansHead;
        ansHead = ansHead->next;
        delete ansEndPtr;
        delete []ptrArray;
        return ansHead;
    }
};

void printList(const ListNode* head) {
    if (head == nullptr) {
        return;
    }
    const ListNode* ptr = head;
    while (ptr->next != nullptr) {
        cout << ptr->val << "->";
        ptr = ptr->next;
    }
    cout << ptr->val << endl;
}

int main() {
    Solution solution;
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(5);

    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    ListNode* list3 = new ListNode(2);
    list3->next = new ListNode(6);

    vector<ListNode*> lists;
    lists.push_back(list1);
    lists.push_back(list2);
    lists.push_back(list3);

    printList(list1);
    printList(list2);
    printList(list3);
    ListNode* result = solution.mergeKLists(lists);
    printList(result);

    return 0;
}

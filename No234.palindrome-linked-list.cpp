/**
 * No234. 回文链表
 * 请判断一个链表是否为回文链表。

示例 1:
输入: 1->2
输出: false

示例 2:
输入: 1->2->2->1
输出: true

示例 3:
输入: null
输出: true

进阶：
你能否用O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include "myTools.h"
using namespace std;

class Solution {
    ListNode* m_node = nullptr;
    bool m_continue = true;
    bool revert(ListNode* node) {
        if (!node) {
            return true;
        }
        // 找到最后一个节点
        if (revert(node->next)) {
            if (m_continue) {
                if (node->val != m_node->val) {
                    return false;
                }
                m_node = m_node->next;
                m_continue = m_node != node && m_node->next != node;
            }
            return true;
        }
        return false;
    }
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;
        }
        m_node = head;
        return revert(head);
    }
};

/**
 * 力扣官方有意思解法之二：将链表的后半部分反转（修改链表结构），然后将前半部分和后半部分进行比较。比较完成后我们应该将链表恢复原样。虽然不需要恢复也能通过测试用例，因为使用该函数的人不希望链表结构被更改。
 * 步骤：
 * 找到前半部分链表的尾节点。
 * 反转后半部分链表。
 * 判断是否为回文。
 * 恢复链表。
 * 返回结果。
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
class Solution2 {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) return true;

        // 找到中间节点，之后将后半链表反转
        ListNode* firstHalfEnd = endOfFirstHalf(head);
        ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

        // 两指针分别从头和中间节点 开始向后比较
        ListNode* p1 = head;
        ListNode* p2 = secondHalfStart;
        bool result = true;
        while (result && p2 != nullptr) {
            if (p1->val != p2->val) result = false;
            p1 = p1->next;
            p2 = p2->next;
        }

        // 再将后半链表反转（恢复）
        firstHalfEnd->next = reverseList(secondHalfStart);
        return result;
    }

private:
    /**
     * 反转后半部分链表（迭代）
     * @param head
     * @return
     */
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }

    /**
     * 找到中间节点（快慢指针）
     * @param head
     * @return
     */
    ListNode* endOfFirstHalf(ListNode* head) {
        ListNode* fastPtr = head;
        ListNode* slowPtr = head;
        while (fastPtr->next != nullptr && fastPtr->next->next != nullptr) {
            fastPtr = fastPtr->next->next;
            slowPtr = slowPtr->next;
        }
        return slowPtr;
    }
};

int main() {
    Solution solution;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);
    cout << solution.isPalindrome(head) << endl;
    return 0;
}

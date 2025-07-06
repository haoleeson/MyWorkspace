/*
*
No148. 排序链表（快慢指针、归并排序）
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

进阶：
你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？

示例 1：
输入：head = [4,2,1,3]
输出：[1,2,3,4]

示例 2：
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

示例 3：
输入：head = []
输出：[]

提示：
链表中节点的数目在范围 [0, 5 * 104] 内
-105 <= Node.val <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
package LeetCode

func sortList(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}

	// find middle node
	slow, fast := head, head.Next
	for fast != nil && fast.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
	}

	// split two list
	secondHead := slow.Next
	slow.Next = nil

	// sort two list
	pLeft := sortList(head)
	pRight := sortList(secondHead)

	// merge two list
	preHead := &ListNode{}
	p := preHead
	for pLeft != nil && pRight != nil {
		if pRight.Val < pLeft.Val {
			p.Next = pRight
			p = p.Next
			pRight = pRight.Next
		} else {
			p.Next = pLeft
			p = p.Next
			pLeft = pLeft.Next
		}
	}
	if pLeft != nil {
		p.Next = pLeft
	} else {
		p.Next = pRight
	}

	return preHead.Next
}

func sortList1(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	// 快慢指针
	var fast, slow = head.Next, head
	for fast != nil && fast.Next != nil {
		slow = slow.Next
		fast = fast.Next.Next
	}
	// 记录后半段的起始节点
	var secondHead = slow.Next
	slow.Next = nil
	// 递归调用
	var left = sortList(head)
	var right = sortList(secondHead)
	// 合并左、右链表
	var ptr = new(ListNode)
	var ans = ptr
	for left != nil && right != nil {
		if left.Val < right.Val {
			ptr.Next = left
			left = left.Next
		} else {
			ptr.Next = right
			right = right.Next
		}
		ptr = ptr.Next
	}
	if left == nil {
		ptr.Next = right
	} else {
		ptr.Next = left
	}
	return ans.Next
}

// No206.reverse-linked-list
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reverseList0(head *ListNode) *ListNode {
	if head == nil {
		return head
	}
	preHead := &ListNode{Next: head}
	p := head

	for p.Next != nil {
		pNext := p.Next

		p.Next = pNext.Next
		pNext.Next = preHead.Next
		preHead.Next = pNext
	}

	return preHead.Next
}

// recode on 2025-11-25
func reverseList(head *ListNode) *ListNode {
	if head == nil {
		return head
	}
	// preHead -> ... -> head -> ptr -> ...
	preHead := &ListNode{Next: head}
	for ptr := head.Next; ptr != nil; ptr = head.Next {
		head.Next = ptr.Next
		ptr.Next = preHead.Next
		preHead.Next = ptr
	}
	return preHead.Next
}
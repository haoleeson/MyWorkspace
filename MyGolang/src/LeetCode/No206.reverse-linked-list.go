// No206.reverse-linked-list
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reverseList(head *ListNode) *ListNode {
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
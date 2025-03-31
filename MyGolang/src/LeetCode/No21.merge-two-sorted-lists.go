/*
No21.merge-two-sorted-lists
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
	preHead := &ListNode{}
	p, p1, p2 := preHead, list1, list2

	for p1 != nil && p2 != nil {
		if p2.Val < p1.Val {
			p.Next = p2
			p = p.Next
			p2 = p2.Next
		} else {
			p.Next = p1
			p = p.Next
			p1 = p1.Next
		}
	}

	// p1 tail
	for p1 != nil {
		p.Next = p1
		p = p.Next
		p1 = p1.Next
	}

	// p2 tail
	for p2 != nil {
		p.Next = p2
		p = p.Next
		p2 = p2.Next
	}
	return preHead.Next
}
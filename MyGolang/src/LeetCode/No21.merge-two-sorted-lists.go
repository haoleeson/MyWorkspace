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
// 2025-11-29 recoding
func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
	preHead := &ListNode{}
	var ptr, ptr1, ptr2 *ListNode = preHead, list1, list2

	for ptr1 != nil && ptr2 != nil {
		if ptr2.Val < ptr1.Val {
			ptr.Next = ptr2
			ptr = ptr.Next
			ptr2 = ptr2.Next
		} else {
			ptr.Next = ptr1
			ptr = ptr.Next
			ptr1 = ptr1.Next
		}
	}

	for ptr1 != nil {
		ptr.Next = ptr1
		ptr = ptr.Next
		ptr1 = ptr1.Next
	}

	for ptr2 != nil {
		ptr.Next = ptr2
		ptr = ptr.Next
		ptr2 = ptr2.Next
	}

	return preHead.Next
}

func mergeTwoLists0(list1 *ListNode, list2 *ListNode) *ListNode {
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
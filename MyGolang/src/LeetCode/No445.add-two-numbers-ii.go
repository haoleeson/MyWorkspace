/*
No445.add-two-numbers-ii
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	var reserveLink func(*ListNode) *ListNode
	reserveLink = func(head *ListNode) *ListNode {
		if head == nil {
			return head
		}
		preHead := &ListNode{Next: head}
		cur := head.Next
		for cur != nil {
			head.Next = cur.Next
			cur.Next = preHead.Next
			preHead.Next = cur

			cur = head.Next
		}
		return preHead.Next
	}

	l1 = reserveLink(l1)
	l2 = reserveLink(l2)
	retPreHead := &ListNode{}
	p3 := retPreHead
	p1, p2 := l1, l2
	var tmp, jin int = 0, 0

	for p1 != nil && p2 != nil {
		tmp = p1.Val + p2.Val + jin
		if tmp > 9 {
			tmp -= 10
			jin = 1
		} else {
			jin = 0
		}
		p3.Next = &ListNode{Val: tmp}
		p3 = p3.Next
		p1 = p1.Next
		p2 = p2.Next
	}

	for p1 != nil {
		tmp = p1.Val + jin
		if tmp > 9 {
			tmp -= 10
			jin = 1
		} else {
			jin = 0
		}
		p3.Next = &ListNode{Val: tmp}
		p3 = p3.Next
		p1 = p1.Next
	}

	for p2 != nil {
		tmp = p2.Val + jin
		if tmp > 9 {
			tmp -= 10
			jin = 1
		} else {
			jin = 0
		}
		p3.Next = &ListNode{Val: tmp}
		p3 = p3.Next
		p2 = p2.Next
	}

	if jin > 0 {
		p3.Next = &ListNode{Val: 1}
	}

	return reserveLink(retPreHead.Next)
}

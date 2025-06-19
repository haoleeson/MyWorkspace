/*
No143.reorder-list
*/

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func reorderList(head *ListNode) {
	// find midNode and preMidNode
	midNode, preMidNode := findMidNode(head)

	if preMidNode == nil {
		return
	}
	// split list
	preMidNode.Next = nil

	// reserve behand list
	leftPart := reserveList(midNode)

	// merge two list
	mergeTwoListOneByOne(head, leftPart)
}

func findMidNode(head *ListNode) (*ListNode, *ListNode) {
	fast, slow := head, head
	var preSlow *ListNode = nil
	for slow != nil && fast != nil && fast.Next != nil {
		preSlow = slow
		slow = slow.Next
		fast = fast.Next.Next
	}
	return slow, preSlow
}

func reserveList(head *ListNode) *ListNode {
	if head == nil {
		return head
	}

	preHead := &ListNode{Next: head}
	p := head
	pNext := p.Next
	// preHead -> [...] -> p -> pNext -> []
	for pNext != nil {
		p.Next = pNext.Next
		pNext.Next = preHead.Next
		preHead.Next = pNext
		pNext = p.Next
	}
	return preHead.Next
}

func mergeTwoListOneByOne(one, another *ListNode) {
	preHead := &ListNode{}
	p := preHead
	pOne := one
	pAnother := another

	for pOne != nil || pAnother != nil {
		if pOne != nil {
			p.Next = pOne
			p = p.Next
			pOne = pOne.Next
		}
		if pAnother != nil {
			p.Next = pAnother
			p = p.Next
			pAnother = pAnother.Next
		}
	}
}